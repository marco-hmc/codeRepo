### 中级面向对象 - 多态

```cpp
void file_log(string msg) {     // 输出到文件
    FILE *file = fopen("/tmp/a.txt");
    fputs(file, msg);
}

void console_log(string msg) {  // 输出到终端
    puts(msg);
}
```


```cpp
void alice() {
    file_log("A 项目正在启动！");
    file_log("发生了寒武纪大爆发！");
    file_log("这是一条提示信息！");
    file_log("发生了私聊事件！");
}

void bob() {
    console_log("B 项目正在启动！");
    console_log("这是一条好友请求！");
    console_log("结交了新朋友！");
}
```

我们很容易想到，可以把 file_log 和 console_log 保存为函数指针，保存在 alice 和 bob 的函数栈上：

```cpp
typedef void (*log_func_t)(string);

void alice() {
    log_func_t log = file_log;
    log("A 项目正在启动！");
    log("发生了寒武纪大爆发！");
    log("这是一条提示信息！");
    log("发生了私聊事件！");
}

void bob() {
    log_func_t log = console_log;
    log("B 项目正在启动！");
    log("这是一条好友请求！");
    log("结交了新朋友！");
}
```
---

但是我们现在需要引入另一个操作，input 函数了：

```cpp
typedef void (*log_func_t)(string);
typedef void (*input_func_t)(string &);

void alice() {
    log_func_t log = file_log;
    input_func_t input = file_input;
    log("A 项目正在启动！");
    log("发生了寒武纪大爆发！");
    log("这是一条提示信息！");
    input("私聊信息> ");
    log("发生了私聊事件！");
}

void bob() {
    log_func_t log = console_log;
    input_func_t input = console_input;
    log("B 项目正在启动！");
    log("这是一条好友请求！");
    input("私聊信息> ");
    log("结交了新朋友！");
}
```

这样如果 Bob 想要改为输入输出走文件，我们只需要修改前两行的函数指针分别指向 file_log 和 file_input 就可以了。

如果我们的 Logger 类想要引入一千个操作呢？

<del>我们只需要修改前两一千行的函数指针分别指向 file_op1、file_op2、file_op3...</del>

如果还是用函数指针，就无法保存 file 参数！比如你 file_log 用得到 file 指针，但是 console_log 用不到，总不能逼着所有人都和你统一参数吧？这就违背了解耦的初衷。

我们决定，定义一个通用的基类，然后让 FileLogger 和 ConsoleLogger 继承它，继承后的结构体可以添加新的成员变量 file 和 socket，来保存各自用到的参数。
因为每个不同子类需要保存状态的不同，所以每个子类的大小会不一样，而栈上的变量必须具有确定的大小，堆上的变量就不需要，所以这种多态的类必须以始终指针的形式传递。

```cpp
struct Logger {
    log_func_t log;
    input_func_t input;
};

struct FileLogger : Logger {
    void log(string msg) {
        fputs(file, msg);
    }

    void input(string &buf) {
        fgets(file, buf);
    }

    FILE *file;
    // 未来如果出现其他 FileLogger 需要的参数，也很容易在这里添加
};

struct ConsoleLogger : Logger {
    void log(string msg, FILE *file) {
        puts(msg);
    }
    
    void input(string &buf) {
        gets(buf);
    }
};

struct NetLogger : Logger {
    void log(string msg, SOCKET *socket) {
        sockputs(socket, msg);
    }
    
    void input(string &buf, SOCKET *socket) {
        sockgets(socket, buf);
    }

    SOCKET *socket;
};

Logger *make_file_logger(FILE *file) {
    return new FileLogger{
        .log = FileLogger::log,
        .input = FileLogger::input,
        .file = file,
    };
}

Logger *make_console_logger() {
    return new ConsoleLogger{
        .log = ConsoleLogger::log,
        .input = ConsoleLogger::input,
    };
}

Logger *make_net_logger(SOCKET *socket) {
    return new NetLogger{
        .log = NetLogger::log,
        .input = NetLogger::input,
        .socket = socket,
    };
}

void alice() {
    Logger *logger = make_file_logger(fopen("/tmp/a.txt"));
    logger->log("A 项目正在启动！");
    logger->log("发生了寒武纪大爆发！");
    logger->log("这是一条提示信息！");
    logger->input("私聊信息> ");
    logger->log("发生了私聊事件！");
}

void bob() {
    Logger *logger = make_console_logger();
    logger->log("B 项目正在启动！");
    logger->log("这是一条好友请求！");
    logger->input("私聊信息> ");
    logger->log("结交了新朋友！");
}
```

后来在 C++ 中引入了“虚函数”语法糖来实现同样的效果，上面的代码可以更简洁地写成：

```cpp
struct Logger {
    virtual void log(string msg) = 0;     // 定义 log 为虚函数，固定格式 virtual ...() = 0;
    virtual void input(string &buf) = 0;  // 定义 input 为虚函数
};

struct FileLogger : Logger {
    FileLogger(FILE *file_) {
        file = file_;
    }

    void log(string msg) override {      // 子类实现 log 虚函数，固定格式为 ...() override;
        fputs(file, msg);
    }

    void input(string &buf) override {  // 子类实现 input 虚函数
        fgets(file, buf);
    }

    FILE *file;
    // 未来如果出现其他 FileLogger 需要的参数，也很容易在这里添加
};

struct ConsoleLogger : Logger {
    void log(string msg, FILE *file) override {
        puts(msg);
    }
    
    void input(string &buf) override {
        gets(buf);
    }
};

struct NetLogger : Logger {
    NetLogger(SOCKET *socket_) {
        socket = socket_;
    }

    void log(string msg, SOCKET *socket) override {
        sockputs(socket, msg);
    }
    
    void input(string &buf, SOCKET *socket) override {
        sockgets(socket, buf);
    }

    SOCKET *socket;
};
```

可见，虚函数是对“结构体存参数”神教的扩展，本来结构体只能存普通变量，虚函数相当于是存了函数指针，而且这个函数还能访问结构体保存的其他变量。

### 虚函数的应用

很多教材中都会举出这样看起来好像很酷的例子：

```cpp
struct Animal {
    virtual void speak() = 0;
};

struct CatAnimal ：Animal {
    void speak() override {
        puts("喵");
    }
};
struct DogAnimal ：Animal {
    void speak() override {
        puts("汪");
    }
};

int main() {
    Animal *cat = new CatAnimal();
    Animal *dog = new DogAnimal();
    cat->speak();
    dog->speak();  // 不觉得这很酷吗？很符合象牙塔脑瘫脑师对面向对象的想象！
}
```

然而，在这个案例中，虚函数可有可无，并没有发挥任何价值（你要拉答辩，可你却去擦镜子，完全搞错了方向），因为我们完全可以写普通成员函数：

```cpp
struct CatAnimal {
    void speak() {
        puts("喵");
    }
};
struct DogAnimal {
    void speak() {
        puts("汪");
    }
};

int main() {
    CatAnimal *cat = new CatAnimal();
    DogAnimal *dog = new DogAnimal();
    cat->speak();
    dog->speak();
}
```

不是一样可以运行吗？我要这 B 虚函数有什么用？
由于象牙塔思想钢印的广泛种植，这是很多同学对面向对象的第一印象：“原来面向对象就是成员函数，就是换了个语法，第一个参数要写到函数名左边了，然后就没了”。

```cpp
// 同学心里：不就是个只能对第一参数有效的重载嘛！
speak(cat);
speak(dog);
```

虚函数真正的应用场景在于，你需要把 Animal 作为另一个函数的参数时。

如果用重载来实现的话，我们需要手写两次一模一样的 feed 函数，违背了“不要重复”原则。

```cpp
void feed(CatAnimal *cat) {
    puts("小彭老师正在给宠物喂食");
    cat->speak();
}

void feed(DogAnimal *dog) {
    puts("小彭老师正在给宠物喂食");
    dog->speak();
}

int main() {
    CatAnimal *cat = new CatAnimal();
    DogAnimal *dog = new DogAnimal();
    feed(cat);
    feed(dog);
}
```

有的同学提出可以模板实现代码复用：

```cpp
template <class T>
void feed(T *animal) {
    puts("小彭老师正在给宠物喂食");
    animal->speak();
}

int main() {
    CatAnimal *cat = new CatAnimal();
    DogAnimal *dog = new DogAnimal();
    feed(cat);
    feed(dog);
}
```

然而，模板只适用于参数直接在栈上的情况，不能解决参数需要存到其他对象内部，比如 vector 的情况：

```cpp
template <class T>
void feed(T *animal) {
    puts("小彭老师正在给宠物喂食");
    animal->speak();
}

int main() {
    vector<???> animals;  // 该用何种基类来存储他们？
    animals.push_back(new CatAnimal());
    animals.push_back(new DogAnimal());
    for (auto &&animal: animals) {
        feed(animal);  // ???
    }
}
```

> 模板函数实现多态的解决方案是有的，那就是 std::variant + std::visit，但那是更后来出现的函数式设计模式了，今天我们先把面向对象学明白了再说。

看来我们不得不弄个基类 Animal 了，得益于“子类指针可以自动转换为基类指针”的特性，我们可以把所有动物放在一个 `vector<Animal *>` 里：

```cpp
struct Animal {
    int hungry = 100;
};

struct CatAnimal : Animal {
};

struct DogAnimal : Animal {
};

void feed(Animal *animal) {  // 不用是模板函数了！也加快了编译的速度
    puts("小彭老师正在给宠物喂食");
    animal->hungry = animal->hungry - 1;  // 但这样只能访问到 Animal 的成员
}

int main() {
    vector<Animal *> animals;  // 用基类指针来存储
    animals.push_back(new CatAnimal());  // CatAnimal * 可以自动转换为 Animal *，因为 CatAnimal 是 Animal 的子类
    animals.push_back(new DogAnimal());
    for (auto &&animal: animals) {
        feed(animal);
    }
}
```

如果是普通成员函数，是没用的！

```cpp
struct Animal {
    void speak() {  // 并不是虚函数...
        puts("通用动物 speak 函数");
    }
};

struct CatAnimal : Animal {
    void speak() {  // 并不会替换掉基类的 speak
        // 只有当以 CatAnimal * 调用时才能调用到这里
        // 以 Animal * 调用时就来不到这里
        puts("喵");
    }
};

struct DogAnimal : Animal {
    void speak() {
        puts("汪");
    }
};

void feed(Animal *animal) {
    puts("小彭老师正在给宠物喂食");
    animal->speak();  // 因为 speak 是实函数，这里只能调用到 Animal 的通用 speak 函数！
};

int main() {
    vector<Animal *> animals;
    animals.push_back(new CatAnimal());
    animals.push_back(new DogAnimal());
    for (auto &&animal: animals) {
        feed(animal);
    }
}
```

会得到：

```
小彭老师正在给宠物喂食
通用动物 speak 函数
小彭老师正在给宠物喂食
通用动物 speak 函数
```

---

把 speak 定义为了虚函数之后，才可以实现真正的多态！

```cpp
struct Animal {
    virtual void speak() = 0;  // 这里的 = 0 表示这是一个纯虚函数，没有默认实现，需要继承 Animal 的各个子类来实现
};

struct CatAnimal : Animal {
    void speak() override {  // 子类实现虚函数
        // 不论以 CatAnimal * 还是以 Animal * 调用时都到这里
        puts("喵");
    }
};

struct DogAnimal : Animal {
    void speak() override {
        puts("汪");
    }
};

void feed(Animal *animal) {
    puts("小彭老师正在给宠物喂食");
    animal->speak();
};

int main() {
    vector<Animal *> animals;
    animals.push_back(new CatAnimal());
    animals.push_back(new DogAnimal());
    for (auto &&animal: animals) {
        feed(animal);
    }
}
```

会得到：

```
小彭老师正在给宠物喂食
喵
小彭老师正在给宠物喂食
汪
```

注意：有任何一个纯虚函数的类都无法直接创建，只能创建他那些实现了全部纯虚函数的子类。

```cpp
Animal a;  // 编译器会报错：Animal 是个纯虚类，无法直接创建！
CatAnimal c;  // 编译通过，因为 CatAnimal 实现了父类的全部纯虚函数 (目前只有一个 speak)
Animal *a = new CatAnimal;  // 编译通过，CatAnimal 可以创建，然后由于 C++ 允许子类指针转换为父类指针，CatAnimal * 又可以在赋值中转换为 Animal *
```

也就是说 Animal 不能直接出现在栈上，但是可以指针或引用的形式传递或返回。

```cpp
void feed(Animal a);         // ✘
void feed(Animal *a);        // ✔
void feed(const Animal &a);  // ✔

Animal create();             // ✘
Animal *create();            // ✔
unique_ptr<Animal> create(); // ✔

vector<Animal> animals;             // ✘
vector<Animal *> animals;           // ✔
vector<unique_ptr<Animal>> animals; // ✔
```

---
