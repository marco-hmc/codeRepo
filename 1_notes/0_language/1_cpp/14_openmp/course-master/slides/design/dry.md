## 设计模式的前世今生

所有眼花缭乱的设计模式，不是为了什么“高雅”、“可读性”、“讨好面试官”

只为一件事：适应变化！

软件和画画等领域有个显著不同：

画画通常是一次性完成的，但软件的开发是持续性的。

需求经常临时变化，在好几年的跨度中不断地修改和更新，以适应变化的需求，停止更新的软件等于死亡。

比如 B 站以前只支持传视频，但是后来产生了直播、专栏、互动视频等多种需求，最近还引入了充电视频、充电动态等私有制特色功能，这都需要程序员加班加点去更新。

调查显示，程序员 90% 的时间都花在改程序上！设计模式的目的，就是让软件更容易适应变化，牺牲一点写程序的时间，让以后改程序能更轻松。

## 什么情况下不需要设计模式？

**设计模式是为了增援未来！如果你都没有未来...**

鼓捣设计模式的代价是第一次写的时候会辛苦一点，但是后续更新起来就方便了。

就好比你来到一间宿舍，如果你只打算住一天，那么你可以只管拉答辩，而不抽马桶！破罐子破摔！
但现实情况往往是，这个宿舍你需要用很久，那就得注意卫生，及时抽掉马桶，不要给明天的自己添乱。

> 不建议现实中这样做，因为会有人被迫接手你的宿舍（项目）替你擦屁股。

如果你的代码是一次性的，比如 ACM 算法竞赛提交完代码就走人，**不需要后续更新**。那就可以不用设计模式，随地答小辩，反正自己不用负责收场。

**设计模式是为了先苦后甜！结果你后面还是苦？**

如果你为了“优雅强迫症”，用了一堆花里胡哨的设计模式，整个代码已经复杂得牵一发而动全身。
第一次写的时候为了设计模式弄得很辛苦，最后发现后续改起来还是辛苦！
那说明你可能**用错了设计模式**，最终并没有起到缓解未来压力的效果，违背了设计模式的初衷！还不如一开始就不要设计模式。

使用了错误的设计模式就好比你拉完答辩，但是你却去擦镜子，擦了半天辛苦死了，但是第二天依然臭气扑鼻，因为你没根据可能的变化，用对设计模式。

## 来看案例吧！

你做了一个名叫 Alice 的项目，为了输出日志，你是这样写的：

```cpp
log("爱丽丝计划正在启动！", "Alice");
log("发生了寒武纪大爆发！", "Alice");
log("这是一条提示信息！",   "Alice");
```

这里面 title 是每条日志的标题，打印在终端上时会变成这样：

```
14:58:01 [Alice] 爱丽丝计划项目正在启动！
14:58:15 [Alice] 发生了 xxx 事件！
14:58:20 [Alice] 这是一条提示信息！
```

这就出现了讨厌的重复。

### 面向过程

为了避免重复，你封装了一个函数：

```cpp
void mylog(string msg) {
    log(msg, "Alice");
}
```

```cpp
mylog("爱丽丝计划正在启动！");
mylog("发生了寒武纪大爆发！");
mylog("这是一条提示信息！");
```

再也不用重复指定一模一样的 title 参数啦！
运行效果相同，写起来却更轻松，看起来也更简洁明了。

这就是**面向过程**的设计模式，用函数把相似的操作封装起来。

实际上你用 log 本身已经在用别人的封装了，如果你把 log 内部的层层调用全部展开，变成原始的一行行系统调用...

```cpp
char buf[1024];
size_t top;
if (top < 1024) buf[top++] = "爱"; else write(1, buf, top), top = 0;
if (top < 1024) buf[top++] = "丽"; else write(1, buf, top), top = 0;
if (top < 1024) buf[top++] = "丽"; else write(1, buf, top), top = 0;
if (top < 1024) buf[top++] = "丝"; else write(1, buf, top), top = 0;
if (top < 1024) buf[top++] = "计"; else write(1, buf, top), top = 0;
if (top < 1024) buf[top++] = "划"; else write(1, buf, top), top = 0;
...
```

可以毫不夸张的说，一切程序，都是在消除重复！
C 编译器通过代码转译消除了汇编的重复，C 标准库通过封装函数消除了常用操作的重复，浏览器通过 HTML/CSS/JS 消除了 UI 开发的重复。

### 为什么复制粘贴不是个好习惯？

你会说，我复制粘贴不就好了？先复制一大堆：

然后选中前面的 `"爱丽丝计划正在启动！"` 逐个修改为不同的信息。

```cpp
log("爱丽丝计划正在启动！", "Alice");
log("发生了寒武纪大爆发！", "Alice");
log("这是一条提示信息！",   "Alice");
```

---

然而避免重复并不是为了少打代码！

假如你需要给项目改个名字，不叫 Alice 了，叫 AlanWalker 了，如果不用设计模式，那你需要手忙脚乱地连改三个地方：

```cpp
log("爱丽丝计划正在启动！", "AlanWalker");
log("发生了寒武纪大爆发！", "AlanWalker");
log("这是一条提示信息！",   "AlanWalker");
```

而且万一其中一个拼错了，然后这个拼错的地方还是一个小概率分支，那么很有可能测试时没有发现就上线了，埋下定时炸弹：

```cpp
log("爱丽丝计划正在启动！", "AlanWalker");

if (random() < 0.0001) { // 模拟小概率事件
    log("发生了寒武纪大爆发！", "AlanWalkor"); // 名字写错了！
    // 由于这一行代码很少执行到，平时测试时你根本没发现
    // 或者干脆间歇性崩溃，你半天找不到原因所在，开始抓狂
}

log("这是一条提示信息！",   "AlanWalker");
```

面向过程设计模式允许我们把相同的东西抽离出来，相似的东西集中到一块，使你只需要修改一个地方即可：

```cpp
void mylog(string msg) {
    log(msg, "AlanWalker");  // 只需这里一处修改，处处生效！
}

mylog("爱丽丝计划正在启动！");
mylog("发生了寒武纪大爆发！");
mylog("这是一条提示信息！");
```

而且相关的事物集中起来后，方便你检查，如果写错了更容易发现，不用一个个去大范围查找所有的 AlanWalker 看看是不是都写对了。

### 面向过程的困境

现在 Alice 需要和他的一个老朋友 Bob 合作：

```cpp
void alice() {
    log("A 项目正在启动！",     "Alice");
    log("发生了寒武纪大爆发！", "Alice");
    log("这是一条提示信息！",   "Alice");
    log("发生了私聊事件！",     "Alice");
}

void bob() {
    log("B 项目正在启动！",     "Bob");
    log("这是一条好友请求！",   "Bob");
    log("结交了新朋友！",       "Bob");
}
```

如果还是只有一个 mylog 函数的话，要么 Alice 能够方便，但 Bob 就用不了：

```cpp
void mylog(string msg) {
    log(msg, "Alice");
}

void alice() {
    mylog("A 项目正在启动！");
    mylog("发生了寒武纪大爆发！");
    mylog("这是一条提示信息！");
    mylog("发生了私聊事件！");
}

void bob() {
    // Bob: 你方便了，我呢？
    log("B 项目正在启动！",     "Bob");
    log("这是一条好友请求！",   "Bob");
    log("结交了新朋友！",       "Bob");
}
```

这时如果 Bob 要改名，还是需要手忙脚乱！

---

如果分成两个函数：

```cpp
void alicelog(string msg) {
    log(msg, "Alice");
}

void boblog(string msg) {
    log(msg, "Bob");
}

void alice() {
    alicelog("A 项目正在启动！");
    alicelog("发生了寒武纪大爆发！");
    alicelog("这是一条提示信息！");
    alicelog("发生了私聊事件！");
}

void bob() {
    boblog("B 项目正在启动！");
    boblog("这是一条好友请求");
    boblog("结交了新朋友！");
}
```

且不说这样依然是把两人的名字嵌入了函数名 alicelog 里，要改 "Alice" 时依然需要改 alicelog 的名字。
要是来了个新同学，叫 Carbon，又需要专门为他定义个 carbonlog 函数！根本没起到减少重复的初衷啊！

而且万一你在 alice 函数中不小心打错了一个名字：

```cpp
void alice() {
    alicelog("A 项目正在启动！");
    boblog("发生了寒武纪大爆发！");  // 不小心打错了！但我没注意
    alicelog("这是一条提示信息！");
    alicelog("发生了私聊事件！");
}
```

编译器不会有任何报错，本属于 Alice 的日志就这样以 Bob 的名字写了出去。

可见，**重复性不但会让更新变得困难，还增加了犯错的概率空间**（再次回顾上一集）。

### 初级面向对象 - 封装

```cpp
void alice() {
    log("A 项目正在启动！",     "Alice");
    log("发生了寒武纪大爆发！", "Alice");
    log("这是一条提示信息！",   "Alice");
    log("发生了私聊事件！",     "Alice");
}

void bob() {
    log("B 项目正在启动！",     "Bob");
    log("这是一条好友请求！",   "Bob");
    log("结交了新朋友！",       "Bob");
}
```

其实我们可以把两人的名字先存为变量：

```cpp
void alice() {
    auto name = "Alice";
    log("A 项目正在启动！",     name);
    log("发生了寒武纪大爆发！", name);
    log("这是一条提示信息！",   name);
    log("发生了私聊事件！",     name);
}

void bob() {
    auto name = "Bob";
    log("B 项目正在启动！",     name);
    log("这是一条好友请求！",   name);
    log("结交了新朋友！",       name);
}
```

这样一样实现了集中的效果，如果遇到改项目名的需求，就不用到处跑了。

---

但是假如 log 引入了新的参数 level 呢？
假设 Alice 想要以 INFO 等级输出，Bob 想要以 DEBUG 等级输出。
我们只好在加个 level 变量，应付未来 level 可能需要改变的可能性：

```cpp
void alice() {
    auto name = "Alice";
    auto level = LogLevel::INFO;
    log("A 项目正在启动！",     name, level);
    log("发生了寒武纪大爆发！", name, level);
    log("这是一条提示信息！",   name, level);
    log("发生了私聊事件！",     name, level);
}

void bob() {
    auto name = "Bob";
    auto level = LogLevel::DEBUG;
    log("B 项目正在启动！",     name, level);
    log("这是一条好友请求！",   name, level);
    log("结交了新朋友！",       name, level);
}
```

现在 log 库又更新了，他们又突然删除了 level 参数，或者说他们给 level 改了个名字，那你又开始手忙脚乱了。

可见，保存 name 变量只解决了 *项目名变更* 的重复问题，而不能解决 *新增参数* 或 *删除参数* 的重复问题。

---

为了让 *新增参数* 或 *删除参数* 时我们也不用手忙脚乱大修改，我们索性把 log 的所有参数封装到一个结构体 LogParams 里：

```cpp
struct LogParams {
    string name;
    LogLevel level;
};

void mylog(string msg, LogParams params) {
    log(msg, params.name, params.level);
}

void alice() {
    LogParams params = {
        .name = "Alice";
        .level = LogLevel::INFO;
    };
    log("A 项目正在启动！",     params);
    log("发生了寒武纪大爆发！", params);
    log("这是一条提示信息！",   params);
    log("发生了私聊事件！",     params);
}

void bob() {
    LogParams params = {
        .name = "Bob";
        .level = LogLevel::DEBUG;
    };
    log("B 项目正在启动！",     params);
    log("这是一条好友请求！",   params);
    log("结交了新朋友！",       params);
}
```

现在假如 log 库的作者突然更新，加了个 file 参数，用于指定输出到哪个文件。

其他使用了 log 库的用户都骂骂咧咧的，说着 “我测你的码”、“*龙门粗口*” 什么的手忙脚乱改代码去了。

而早有先见之明的你，只是轻轻给结构体添加了一个成员：

```cpp
struct LogParams {
    string name;
    LogLevel level;
    string file = "C:/默认路径.txt";
};

void mylog(string msg, LogParams params) {
    log(msg, params.name, params.level, file = params.file);
}
```

如果是你编写 Alice 项目，目前尚且只有 3 处调用，你会不会为他专门封装一个 mylog 函数？还是偷懒复制粘贴爽一时？
等发展到有 100 处调用时突然需要改项目名呢？悔恨吗？

如果是你，看到只有一个 title 参数的 log 函数，会不会富有远见地专门为他定义一个尚且只有一个成员的 LogParams 结构体并受到短视人的嘲笑？
等到有 100 处调用时 log 突然需要加个新参数时呢？还笑得出来不？

可能你有 100 处代码提前准备好用了设计模式，即使其中只有 10 个后来确实需要修改，但如果你一开始没用，那这 10 个改起来可能比直接写 1000 个还吃力。

---

后面的发展我们都知道了，业界大量采用上述做法后，发现经常出现一个结构体封装一堆“参数”的情况。

为了方便，人们魔改 C 语言发明 C++ 引入“成员函数”的语法糖来简化书写。然后结构体也别叫 LogParams 了，直接就叫 Logger 了，“日志记录者”，听起来就像是个活人一样！

```cpp
struct Logger {
    string name;
    LogLevel level;

    void mylog(string msg) {
        log(msg, this->name, this->level);
    }
};

void alice() {
    Logger logger = {
        .name = "Alice";
        .level = LogLevel::INFO;
    };
    logger.mylog("A 项目正在启动！");
    logger.mylog("发生了寒武纪大爆发！");
    logger.mylog("这是一条提示信息！");
    logger.mylog("发生了私聊事件！");
}

void bob() {
    Logger logger = {
        .name = "Bob";
        .level = LogLevel::INFO;
    };
    logger.mylog("B 项目正在启动！");
    logger.mylog("这是一条好友请求！");
    logger.mylog("结交了新朋友！");
}
```

这就是后来风靡一时的面向对象设计模式之雏形，如今绝大多数软件都是基于面向对象开发的。
即使是 C 语言的软件，例如 Linux 内核，也会大量使用这种结构体做参数的方式模拟面向对象，他们甚至还会用函数指针模拟虚函数。
没有面向对象设计模式，任何大型项目都将寸步难行！

而某些象牙塔里眷养着的大学生，毕业设计典中典之图书增删改查系统，经常是图书和学生分别弄四个增删改查函数，完全不复用代码，完全考虑未来增加新实体的可能性。
他们可能用了 Java 语言，思想却是完全面向过程的，和 Linus 用着 C 语言却高度面向对象相比，谁才是真正的面向对象技术的拥护者呢？

他们确实不用考虑未来的维护，毕竟这种应付老师的一次性产品根本不会投入使用！根本不用更新！写完论文直接丢在一旁了！
这就是为什么小彭老师在面试时会发现学历越高越菜的现象，他们大学里只学了**写程序**，而我们的主要工作却是**改程序**！

同理 ACM 我建议你少刷，里面的纯数学算法大多很少直接用到，用到了也都是调用现成的库。反而因为 ACM 不用持久维护的特性，如果你写惯了这种随地答辩写法，你回到自己家里也习惯性地答小辩失禁就尴尬了。

只是三分钟小猫钓鱼地写个一次性毕业设计或刷 ACM 算法完全只是练写代码，练不到最重要的改代码，想要真正精进编程技术的建议去自己长久地维护一个开源项目。

比如小彭老师开发 co_async 就不仅为了教育目的，也起到练手的目的：

- 前期写代码时，练的是如何设计得当，为将来可能的改代码服务。
- 后期改代码时，是在品尝自己之前留下的答辩，然后反思之前写代码时考虑不足的错误，吸取经验。

> 上一期课程中传授的很多经验都是在 co_async 中犯错才得到的，小彭老师并不是先天圣体

如果你是改别人现有的开源项目，那就只能学到后者了，你只能学到别人的错误，只知道别人错在哪里，甚至很多时候你只是去抱怨别人写的不好，自己却不吸取经验，果然还是自己品自己答辩的印象最深刻。

如果你只是“看”别人的开源项目，那更糟！什么都学不到了！你只是看，怎么掌握最重要的改代码技能？

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

假如我们的日志库想要通用化，允许输出到文件，或直接输出到终端。

现在爱丽丝想要输出到文件，Bob 想要输出到终端，应该怎么做？

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

又出现了重复，假如 Bob 突然不想输出到终端了，想输出到文件了，我们又得手忙脚乱改好多地方！

为此，我们可以把两者合并成同一个函数，然后增加一个参数，表示是输出到终端还是文件。

```cpp
void log(string msg, bool to_file) {
    if (to_file) { // 为 true 表示输出到文件
        FILE *file = fopen("/tmp/a.txt");
        fputs(file, msg);
    } else { // 为 false 表示输出到终端
        puts(msg);
    }
}

void alice() {
    bool to_file = true;
    log("A 项目正在启动！", to_file);
    log("发生了寒武纪大爆发！", to_file);
    log("这是一条提示信息！", to_file);
    log("发生了私聊事件！", to_file);
}

void bob() {
    bool to_file = false;
    log("B 项目正在启动！", to_file);
    log("这是一条好友请求！", to_file);
    log("结交了新朋友！", to_file);
}
```

但是如果我们又多了一个选择，要把日志结果输出到网络（TCP 套接字）上呢？

很容易出现超过两种情况，bool 只能表示 true/false 两种情况，而且语义不明，不看函数签名就不知道 true 表示的是文件还是终端。最好的办法还是定义一个枚举：

```cpp
enum LogTarget {
    FILE,
    CONSOLE,
    NET,
};

void log(string msg, LogTarget target) {
    if (target == FILE) {
        FILE *file = fopen("/tmp/a.txt");
        fputs(file, msg);
    } else if (target == CONSOLE) {
        puts(msg);
    } else if (target == NET) {
        SOCKET *socket = sockopen("127.0.0.1:8080");
        sockputs(socket, msg);
    } else {
        throw runtime_error("错误的日志目标！");
    }
}

void alice() {
    auto target = FILE;
    log("A 项目正在启动！", target);
    log("发生了寒武纪大爆发！", target);
    log("这是一条提示信息！", target);
    log("发生了私聊事件！", target);
}

void bob() {
    auto target = CONSOLE;
    log("B 项目正在启动！", target);
    log("这是一条好友请求！", target);
    log("结交了新朋友！", target);
}
```

完美的设计，避免了重复，这样不论以后要：

- *Alice 和 Bob 需要改目标*
- *log 加了新的输出目标*

我们都能用很少的修改适应需求变化。

真的完美了吗？假如我的需求是，*增加一个操作* 呢？

目前我们的日志库只有一个 log 操作，假如我要增加一个 input 操作，从相应的目标读取用户输入呢？

```cpp
enum LogTarget {
    FILE,
    CONSOLE,
    NET,
};

void log(string msg, LogTarget target) {
    if (target == FILE) {
        FILE *file = fopen("/tmp/a.txt");
        fputs(file, msg);
    } else if (target == CONSOLE) {
        puts(msg);
    } else if (target == NET) {
        SOCKET *socket = sockopen("127.0.0.1:8080");
        sockputs(socket, msg);
    } else {
        throw runtime_error("错误的日志目标！");
    }
}

void input(string &buf, LogTarget target) {
    if (target == FILE) {
        FILE *file = fopen("/tmp/a.txt");
        fgets(file, buf);
    } else if (target == CONSOLE) {
        gets(buf);
    } else if (target == NET) {
        SOCKET *socket = sockopen("127.0.0.1:8080");
        sockgets(socket, buf);
    } else {
        throw runtime_error("错误的日志目标！");
    }
}
```

糟糕，好像又开始重复了！如果还要加更多操作的话，那每次都要重复写一堆 if-else 判断！而且枚举非法时还需要抛出异常，非常麻烦！

更糟糕的是，操作数量和枚举数量似乎形成了一个讨厌的乘积！

这里糟糕之处在于把文件、终端、网络等不相干的操作实现细节混在了同一个函数里。
而明明相关的 fputs 和 fgets 操作却远远地分隔两地，中间夹杂着和他们毫无关系的控制台、网络等操作。sockgets 和 sockputs 同样被文件、控制台所无情分隔。

就好比把很多不相关的数据强行塞到同一个缓存行，CPU 效率会降低。把很多不相关的东西强行塞到一个函数中，人类大脑同样会混乱！

假如我们要删除 NET 的话，就得连跑三个不同的地方：

```cpp
enum LogTarget {
    FILE,
    CONSOLE,
    // NET,
};

void log(string msg, LogTarget target) {
    if (target == FILE) {
        FILE *file = fopen("/tmp/a.txt");
        fputs(file, msg);
    } else if (target == CONSOLE) {
        puts(msg);
    // } else if (target == NET) {
        // SOCKET *socket = sockopen("127.0.0.1:8080");
        // sockputs(socket, msg);
    } else {
        throw runtime_error("错误的日志目标！");
    }
}

void input(string &buf, LogTarget target) {
    if (target == FILE) {
        FILE *file = fopen("/tmp/a.txt");
        fgets(file, buf);
    } else if (target == CONSOLE) {
        gets(buf);
    // } else if (target == NET) {
        // SOCKET *socket = sockopen("127.0.0.1:8080");
        // sockgets(socket, buf);
    } else {
        throw runtime_error("错误的日志目标！");
    }
}
```

不论是增加了新 LogTarget，给 LogTarget 改名，或是删除一个 LogTarget，都需要跳转到每个文件里去改！而且万一漏改一个，就留下了隐患。

最讨厌的是，我们不得不把所有可能性都在每一个操作的函数里罗列出来，对大脑的压力是 $O(n^2)$ 的！对编译器也是！

> 就像乱掉的耳机线团成一团，你的大脑分析这种代码会干烧，编译器编译时也会干烧，然后编译就会慢得要死！你改新需求时也慢的要死！

---

我们回到原来的代码，除了保存一个 bool 变量来避免重复，还可以怎么做？

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

这样如果 Bob 想要改为输出到文件，我们只需要修改第一行的函数指针指向 file_log 就可以了。

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

天哪！一个个初始化也太麻烦了！索性把这些函数指针封装成一个结构体，然后再封装两个“构造”函数创建不同类型这个结构体（实际上是同一个 Logger 类型，只是其中的函数指针不同，导致调用时效果发生不同）。

```cpp
typedef void (*log_func_t)(string);
typedef void (*input_func_t)(string &);

struct Logger {
    log_func_t log;
    input_func_t input;
    // 这里很容易添加其他新的操作函数
    // other_op_t other_op;
};

Logger make_file_logger() {
    return Logger{
        .log = file_log,
        .input = file_input,
    };
}

Logger make_console_logger() {
    return Logger{
        .log = console_log,
        .input = console_input,
    };
}

// 这里同样很容易添加其他新的日志者类型
// Logger make_other_type_logger() { ... }

void alice() {
    Logger logger = make_file_logger();
    logger.log("A 项目正在启动！");
    logger.log("发生了寒武纪大爆发！");
    logger.log("这是一条提示信息！");
    logger.input("私聊信息> ");
    logger.log("发生了私聊事件！");
}

void bob() {
    Logger logger = make_console_logger();
    logger.log("B 项目正在启动！");
    logger.log("这是一条好友请求！");
    logger.input("私聊信息> ");
    logger.log("结交了新朋友！");
}

// 这里同样很容易添加其他新的玩家
// void carbon() {
//     Logger logger = make_console_logger();
//     ...
// }
```

好处是，我们可以把 file_ 类的函数实现写在一块，而且每个都是独立的函数，不像之前 if-else 需要把一堆无关的操作塞在同一个函数里。

---

但是现在我们需求改变，file_log 需要一个额外参数，file，表示输出到文件对象。

```cpp
void file_log(string msg, FILE *file) {   // 输出到文件
    fputs(file, msg);
}

void console_log(string msg) {  // 输出到终端
    puts(msg);
}
```

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

### 功能单一原则

为什么不推荐一个类干很多事：那往往意味着代码出现了重复！

## 初级函数式 - 回调

面向对象允许一个类有很多个成员函数。

但是多数情况下，其实每个类只需要一个函数就够了。

## 中级函数式 - 闭包

## 高级函数式 - 类型擦除

## 究级函数式 - 访问者模式

## 后现代鸭子类型

下一期正式开始逐个详细介绍每一个设计模式，尽情期待～
