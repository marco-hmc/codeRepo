# 让虚函数再次伟大！

许多设计模式都与虚函数息息相关，今天我们来学习一些常用的。

- 策略模式
- 迭代器模式
- 适配器模式
- 工厂模式
- 超级工厂模式
- 享元模式
- 代理模式

## 跨接口的适配器

适配器模式还可以使原本由于接口不兼容而不能一起工作的那些类可以一起工作，例如一个第三方库提供了类似于我们 Inputer 的输入流接口，也是基于虚函数的。但是他的接口显然不能直接传入我们的 reduce 函数，我们的 reduce 函数只接受我们自己的 Inputer 接口。这时就可以用适配器，把接口翻译成我们的 reducer 能够理解的。

以下是一个自称 “Poost” 的第三方库提供的接口：

```cpp
struct PoostInputer {
    virtual bool hasNext() = 0;
    virtual int getNext() = 0;
};
```

他们要求的用法是先判断 hasNext()，然后才能调用 getNext 读取出真正的值。小彭老师设计了一个 Poost 适配器，把 PoostInputer 翻译成我们的 Inputer：

```cpp
struct PoostInputerAdapter {
    PoostInputer *poostIn;
    optional<int> next;

    PoostInputerAdapter(PoostInputer *poostIn)
        : poostIn(poostIn)
    {}

    optional<int> fetch() override {
        if (next.has_value()) {
            auto res = next;
            next = nullopt;
            return res;
        }

        if (poostIn.hasNext()) {
            return poostIn.getNext();
        } else {
            return nullopt;
        }
    }
};
```

当我们得到一个 PoostInputer 时，如果想要调用我们自己的 reducer，就可以用这个 PoostInputerAdapter 套一层：

```cpp
auto poostStdIn = poost::getStandardInput();
reduce(new PoostInputerAdapter(poostStdIn), new SumReducer());
```

这样就可以无缝地把 PoostInputer 作为 reduce 的参数了。

# 工厂模式

现在你是一个游戏开发者，你的玩家可以装备武器，不同的武器可以发出不同的子弹！

你使用小彭老师教的**策略模式**，把不同的子弹类型作为不同的策略传入 player 函数，造成不同类型的伤害。

```cpp
struct Bullet {
    virtual void explode() = 0;
};

struct AK47Bullet : Bullet {
    void explode() override {
        puts("物理伤害");
    }
};

struct MagicBullet : Bullet {
    void explode() override {
        puts("魔法伤害");
    }
};

void player(Bullet *bullet) {
    bullet->explode();
}

player(new AK47Bullet());
player(new MagicBullet());
```

但是这样就相当于每个玩家只有一发子弹，听个响就没了…

如何允许玩家源源不断地创造新子弹出来？我们可以把“创建子弹”这一过程抽象出来，放在一个“枪”类里。

```cpp
struct Gun {
    virtual Bullet *shoot() = 0;
};

struct AK47Gun : Gun {
    Bullet *shoot() override {
        return new AK47Bullet();
    }
};

struct MagicGun : Gun {
    Bullet *shoot() override {
        return new MagicBullet();
    }
};

void player(Gun *gun) {
    for (int i = 0; i < 100; i++) {
        Bullet *bullet = gun->shoot();
        bullet->explode();
    }
}

player(new AK47Gun());
player(new MagicGun());
```

现在，你的玩家可以直接选择不同的枪了！

这就是所谓的**工厂模式**：“枪”就是“子弹”对象的工厂。
传给玩家的是子弹的工厂——枪，而不是子弹本身。
只要调用工厂的 shoot 函数，玩家可以源源不断地创建新子弹出来。
正所谓授人以鱼不如授人以渔，你的玩家不再是被动接受子弹，而是可以自己创造子弹了！

工厂还可以具有一定的参数，例如我们需要模拟 AK47 可能“受潮”，导致产生的子弹威力降低。
就可以给枪加一个 isWet 参数，给子弹加一个 damage 参数，让 AK47 生成子弹的时候，根据 isWet 为子弹构造函数设置不同的 damage。

```cpp
struct AK47Bullet {
    int damage;

    AK47Bullet(int damage) : damage(damage) {}

    void explode() {
        printf("造成 %d 点物理伤害\n", damage);
    }
};

struct AK47Gun : Gun {
    bool isWet;

    AK47Gun(bool isWet) : isWet(isWet) {}

    Bullet *shoot() override {
        if (isWet)
            return new AK47Bullet(5);  // 受潮了，伤害降低为 5
        else
            return new AK47Bullet(10); // 正常情况下伤害为 10
    }
};
```

我们还可以利用模板自动为不同的子弹类型批量定义工厂：

```cpp
template <class B>
struct GunWithBullet : Gun {
    static_assert(is_base_of<Bullet, B>::value, "B 必须是 Bullet 的子类");

    Bullet *shoot() override {
        return new B();
    }
};

void player(Gun *gun) {
    for (int i = 0; i < 100; i++) {
        Bullet *bullet = gun->shoot();
        bullet->explode();
    }
}

player(new GunWithBullet<AK47Bullet>());
player(new GunWithBullet<MagicBullet>());
};
```

这样就不必每次添加新子弹类型时，都得新建一个相应的枪类型了，进一步避免了代码重复。可见模板元编程完全可与传统面向对象强强联手。

## 超级工厂模式

```cpp
Gun *getGun(string name) {
    if (name == "AK47") {
        return new GunWithBullet<AK47Bullet>();
    } else if (name == "Magic") {
        return new GunWithBullet<MagicBullet>();
    } else {
        throw runtime_error("没有这种枪");
    }
}

player(getGun("AK47"));
player(getGun("Magic"));
```

## RAII 自动管理内存

```cpp
template <class B>
struct GunWithBullet : Gun {
    static_assert(is_base_of<Bullet, B>::value, "B 必须是 Bullet 的子类");

    Bullet *shoot() override {
        return new B();
    }
};

void player(Gun *gun) {
    for (int i = 0; i < 100; i++) {
        Bullet *bullet = gun->shoot();
        bullet->explode();
        delete bullet;  // 刚才没有 delete！会产生内存泄漏！
    }
}

player(new GunWithBullet<AK47Bullet>());
player(new GunWithBullet<MagicBullet>());
```

现在的工厂一般都会返回智能指针就没有这个问题。

具体来说就是用 `unique_ptr<T>` 代替 `T *`，用 `make_unique<T>(xxx)` 代替 `new T(xxx)`。

```cpp
template <class B>
struct GunWithBullet : Gun {
    static_assert(is_base_of<Bullet, B>::value, "B 必须是 Bullet 的子类");

    unique_ptr<Bullet> shoot() override {
        return make_unique<B>();
    }
};

void player(Gun *gun) {
    for (int i = 0; i < 100; i++) {
        auto bullet = gun->shoot();
        bullet->explode();
        // unique_ptr 在退出当前 {} 时会自动释放，不用你惦记着了
    }
}

player(make_unique<GunWithBullet<AK47Bullet>>().get());
player(make_unique<GunWithBullet<MagicBullet>>().get());
```

> 这里 C++ 标准保证了 unique_ptr 的生命周期是这一整行（; 结束前），整个 player 执行期间都活着，不会提前释放
> 正如 `func(string().c_str())` 不会有任何问题，string 要到 func 返回后才释放呢！

只要把所有 `make_unique<T>` 看作 `new T`，把所有的 `unique_ptr<T>` 看作 `T *`，用法几乎一样，但没有内存泄漏，无需手动 delete。

## 工厂模式实战

回到数组求和问题。

```cpp
int sum(vector<int> v) {
    int res = 0;
    for (int i = 0; i < v.size(); i++) {
        res = res + v[i];
    }
    return res;
}

int product(vector<int> v) {
    int res = 1;
    for (int i = 0; i < v.size(); i++) {
        res = res * v[i];
    }
    return res;
}

int average(vector<int> v) {
    int res = 0;
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
        res = res + v[i];
        count = count + 1;
    }
    return res / count;
}
```

我们想要加一个求平均值的函数 average，这该如何与 sum 合起来？

注意因为我们要支持从 CinInputer 读入数据，并不一定像一样 VectorInputer 能够提前得到数组大小，不然也不需要 count 了。

```cpp
int reduce(vector<int> v) {
    int res = ???;              // sum 时这里是 0，product 时这里是 1
    int count? = ???;           // sum 和 product 用不到该变量，只有 average 需要
    for (int i = 0; i < v.size(); i++) {
        res = res ??? v[i];   // sum 时这里是 +，product 时这里是 *
        count? = count? ???;  // average 时这里还需要额外修改 count 变量！
    }
    return res;
}
```

看来我们需要允许 Reducer 的 init() 返回 “任意数量的状态变量”！
以前的设计让 init() 只能返回单个 int 是个错误的决定。
这时候就可以把 “任意数量的状态变量” 封装成一个新的类。
然后改为由这个类负责提供虚函数 add()。
且只需要提供一个右侧参数了，左侧的 res 变量已经存在 ReducerState 体内了。

```cpp
struct ReducerState {
    virtual void add(int val) = 0;
    virtual int result() = 0;
};

struct Reducer {
    virtual unique_ptr<ReducerState> init() = 0;
};

struct SumReducerState : ReducerState {
    int res;

    SumReducerState() : res(0) {}

    void add(int val) override {
        res = res + val;
    }

    int result() override {
        return res;
    }
};

struct ProductReducerState : ReducerState {
    int res;

    ProductReducerState() : res(1) {}

    void add(int val) override {
        res = res * val;
    }

    int result() override {
        return res;
    }
};

struct AverageReducerState : ReducerState {
    int res;
    int count;

    AverageReducerState() : res(0), count(0) {}

    void add(int val) override {
        res = res + val;
        count = count + 1;
    }

    int result() override {
        return res / count;
    }
};

struct SumReducer : Reducer {
    unique_ptr<ReducerState> init() override {
        return make_unique<SumReducerState>();
    }
};

struct ProductReducer : Reducer {
    unique_ptr<ReducerState> init() override {
        return make_unique<ProductReducerState>();
    }
};

struct AverageReducer : Reducer {
    unique_ptr<ReducerState> init() override {
        return make_unique<AverageReducerState>();
    }
};
```

这里 Reducer 就成了 ReducerState 的工厂。

```cpp
int reduce(Inputer *inputer, Reducer *reducer) {
    unique_ptr<ReducerState> state = reducer->init();
    while (auto val = inputer->fetch()) {
        state->add(val);
    }
    return state->result();
}

int main() {
    vector<int> v;
    reduce(make_unique<VectorInputer>(v).get(), make_unique<SumReducer>().get());
    reduce(make_unique<VectorInputer>(v).get(), make_unique<ProductReducer>().get());
    reduce(make_unique<VectorInputer>(v).get(), make_unique<AverageReducer>().get());
}
```

---

现在，老板需求改变，他想要**并行**的 sum 和 product 函数！

并行版需要创建很多个任务，每个任务需要有一个自己的中间结果变量，最后的结果计算又需要一个中间变量。
还好你早已提前采用工厂模式，允许函数体内多次创建 ReducerState 对象。

```cpp
int reduce(Inputer *inputer, Reducer *reducer) {
    tbb::task_group g;
    list<unique_ptr<ReducerState>> local_states;
    vector<int> chunk;
    auto enqueue_chunk = [&]() {
        local_chunks.emplace_back();
        g.run([chunk = move(chunk), &back = local_chunks.back()]() {
            auto local_state = reducer->init();
            for (auto &&c: chunk) {
                local_state->add(c);
            }
            back = move(local_state); // list 保证已经插入元素的引用不会失效，所以可以暂存 back 引用
        });
        chunk.clear();
    };
    while (auto tmp = inputer->fetch()) {
        if (chunk.size() < 64) { // 还没填满 64 个
            chunk.push_back(tmp);
        } else { // 填满了 64 个，可以提交成一个单独任务了
            enqueue_chunk();
        }
    }
    if (chunk.size() > 0) {
        enqueue_chunk(); // 提交不足 64 个的残余项
    }
    g.wait();
    auto final_state = reducer->init();
    for (auto &&local_state: local_states) {
        res = final_state->add(local_state->result());
    }
    return final_state->result();
}
```

只需要把 reducer 参数替换为 MinReducer、AverageReducer……就自动适用于不同的计算任务，而不用为他们每个单独编写并行版本的代码。

课后作业：使用模板批量定义所有的 Reducer！例如：

```cpp
using MinReducer = ReducerWithState<MinReducerState>;
...
```

# 享元模式

在二维游戏开发中，常常会提到一种称为 Sprite（精灵贴图）的黑话，实际上就是每个对象自己有一张贴图，贴图跟着物体的位置走。

```cpp
struct Bullet {
    glm::vec3 position;
    glm::vec3 velocity;
    vector<char> texture;

    void draw() {
        glDrawPixels(position, texture);
    }
};
```

texture 里面存储着贴图的 RGB 数据，他直接就是 Bullet 的成员。
这样的话，如果我们的玩家打出了 100 颗子弹，就需要存储 100 个贴图数组。
如果我们的玩家同时打出了 1000 颗子弹，就需要存储 1000 个贴图数组。
这样的话，内存消耗将会非常大。然而所有同类型的 Bullet，其贴图数组其实是完全相同的，完全没必要各自存那么多份拷贝。

为解决这个问题，我们可以使用**享元模式**：共享多个对象之间**相同**的部分，节省内存开销。

这里每颗子弹的 position、velocity 显然都是各有不同的，不可能所有子弹都在同一个位置上。
但是很多子弹都会有着相同的贴图，只有不同类型的子弹贴图会不一样。
比如火焰弹和寒冰弹会有不同的贴图，但是当场上出现 100 颗火焰弹时，显然不需要拷贝 100 份完全相同的火焰弹贴图。

```cpp
struct Sprite {  // Sprite 才是真正持有（很大的）贴图数据的
    vector<char> texture;

    void draw(glm::vec3 position) {
        glDrawPixels(position, texture);
    }
};

struct Bullet {
    glm::vec3 position;
    glm::vec3 velocity;
    shared_ptr<Sprite> sprite;  // 允许多个子弹对象共享同一个精灵贴图的所有权

    void draw() {
        sprite->draw(position);  // 转发给 Sprite 让他帮忙在我的位置绘制贴图
    }
};
```

需要绘制子弹时，Bullet 的 draw 只是简单地转发给 Sprite 类的 draw。
只要告诉 Sprite 子弹的位置就行，贴图数据已经存在 Sprite 内部，让他来负责真正绘制。
Bullet 类只需要专注于位置、速度的更新即可，不必去操心着贴图绘制的细节，实现了解耦。

这种函数调用的转发也被称为**代理模式**。

## 代理模式

这样还有一个好处那就是，Sprite 可以设计成一个虚函数接口类：

```cpp
struct Sprite {
    virtual void draw(glm::vec3 position) = 0;
};

struct FireSprite {
    vector<char> fireTexture;

    FireSprite() : fireTexture(loadTexture("fire.jpg")) {}

    void draw(glm::vec3 position) override {
        glDrawPixels(position, fireTexture);
    }
};

struct IceSprite { // 假如寒冰弹需要两张贴图，也没问题！因为虚接口类允许子类有不同的成员，不同的结构体大小
    vector<char> iceTexture1;
    vector<char> iceTexture2;

    IceSprite()
    : iceTexture1(loadTexture("ice1.jpg"))
    , iceTexture2(loadTexture("ice2.jpg"))
    {}

    void draw(glm::vec3 position) override {
        glDrawPixels(position, iceTexture1);
        glDrawPixels(position, iceTexture2);
    }
};
```

```cpp
struct Bullet {
    glm::vec3 position;
    glm::vec3 velocity;
    shared_ptr<Sprite> sprite;  // Sprite 负责含有虚函数

    void draw() {  // Bullet 的 draw 就不用是虚函数了！
        sprite->draw(position);
    }
};
```



# 组件模式

```cpp
```


# 虚函数常见问题辨析

## 返回 bool 的虚函数






## 课后作业

你拿到了一个大学生计算器的大作业：

```cpp
int main() {
    char c;
    cout << "请输入第一个数：";
    cin >> a;
    cout << "请输入第二个数：";
    cin >> b;
    cout << "请输入运算符：";
    cin >> c;
    if (c == '+') {
        cout << a + b;
    } else if (c == '-') {
        cout << a - b;
    } else if (c == '*') {
        cout << a * b;
    } else if (c == '/') {
        cout << a / b;
    } else {
        cout << "不支持的运算符";
    }
}
```

你开始用策略模式改造它：

```cpp
struct Calculator {
    virtual int calculate(int a, int b) = 0;
};

struct AddCalculator : Calculator {
    int calculate(int a, int b) override {
        return a + b;
    }
};

struct SubCalculator : Calculator {
    int calculate(int a, int b) override {
        return a - b;
    }
};

struct MulCalculator : Calculator {
    int calculate(int a, int b) override {
        return a * b;
    }
};

struct DivCalculator : Calculator {
    int calculate(int a, int b) override {
        return a / b;
    }
};

Calculator *getCalculator(char c) {
    if (c == '+') {
        calculator = new AddCalculator();
    } else if (c == '-') {
        calculator = new SubCalculator();
    } else if (c == '*') {
        calculator = new MulCalculator();
    } else if (c == '/') {
        calculator = new DivCalculator();
    } else {
        throw runtime_error("不支持的运算符");
    }
};

int main() {
    char c;
    cout << "请输入第一个数：";
    cin >> a;
    cout << "请输入第二个数：";
    cin >> b;
    cout << "请输入运算符：";
    cin >> c;
    Calculator *calculator = getCalculator(c);
    cout << calculator->calculate(a, b);
}
```
