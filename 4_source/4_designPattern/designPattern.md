## design

### 0. designPrinciples

* 程序开发一般会有七个原则：
  * 开闭原则 (Open-Closed Principle, OCP)
    * 定义：一个软件实体（如类、模块、函数等）应该对扩展开放，对修改关闭。也就是说，你可以通过添加新的功能来扩展一个实体的行为，而不需要修改已有的代码。
    * 例子：使用接口和抽象类来定义通用的行为，然后通过继承或实现来扩展功能。

  * 单一职责原则 (Single Responsibility Principle, SRP)
    * 定义：一个类或模块应该只负责一个单一的功能或任务。换句话说，一个类应该只有一个变化的原因。
    * 例子：一个类负责处理文件输入输出，另一个类负责数据解析。

  * 里氏替换原则 (Liskov Substitution Principle, LSP)
    * 定义：子类型必须能够替换掉它们的基类型，而程序的行为不会受到影响。
    * 例子：如果一个类是某个抽象类的子类，那么它必须能够替代抽象类在任何场景下。

  * 依赖倒转原则 (Dependency Inversion Principle, DIP)
    * 定义：高层模块不应该依赖于低层模块，它们应该都依赖于抽象。同时，抽象不应该依赖于具体细节，具体细节应该依赖于抽象。
    * 例子：通过依赖注入，高层模块可以接收一个抽象的接口，而不是一个具体的实现。

  * 接口隔离原则 (Interface Segregation Principle, ISP)
    * 定义：客户端不应该强制依赖于它们不需要的接口。换句话说，一个类应该只依赖于它需要使用的接口，而不是依赖于一个庞大臃肿的接口列表。
    * 例子：将一个大接口拆分成多个小的，每个类只需要实现它们所需的接口。

  * 最少知道原则 (Law of Demeter, LoD)
    * 定义：一个对象应该对其他对象有最少的了解。也就是说，一个对象不应该了解太多与它无关的对象的内部细节。
    * 例子：如果一个类的方法只调用另一个对象的方法，而不是直接访问它的属性或内部状态，那么它遵守了最少知道原则。

  * 合成复用原则 (Composite Reuse Principle, CRP)
    * 定义：优先使用对象组合（合成）而不是继承来实现代码的复用。也就是说，通过将对象组合在一起创建新的功能，而不是通过继承现有类来实现。
    * 例子：通过将不同的模块组合在一起，来构建具有新功能的复合模块。

* 设计模式可以分为三大类
  * creational
    * 简单来说，就是关注如何创建对象的。
  * structural
    * 关注类和类之间的关系的
    * > 如`composite`模式，就是单纯的组合；
    * > 如`flyweight`模式，就是不同实例共享数据；
  * behavioral
    * 除了关注类和类之间的关系，还关系类和类之间的行为
    * > 如`Observer`模式，Observable对象被改变时，observer需要做出改变；
    * > 如`Memento`模式，用于保存某一类的部分属性，可用于之后回写回去；
    * > 如`command`模式，抽象类和实现类之间，在抽象类保证事务等等。
    * 
### 1. creational

> Creational patterns are focused towards how to instantiate an object or group of related objects.

#### 1.1 simple factory
*** meaning**
  * Simple factory simply generates an instance for client without exposing any instantiation logic to the client
  * more directly, factory is responsible for creating("new" in cpp-lang) the new instance. 

* **when to use**
  * When creating an object is not just a few assignments and involves some logic, it makes sense to put it in a dedicated factory instead of repeating the same code everywhere.

#### 1.2 factory methods
*** meaning**
  * It provides a way to delegate the instantiation logic to child classes.

* **when to use**
  * When creating an object is not just a few assignments and involves some logic, it makes sense to put it in a dedicated factory instead of repeating the same code everywhere.



* Factor
  * 方式：
    * 由一个factory管理product的生命周期，通过
  * 应用场景：
    * 
* AbstractFactory
* Generator
* 

### 2. designParadigm
* RAII
* PIMPL
* MVC

### appendix
1. https://refactoringguru.cn/design-patterns/adapter
2. https://github.com/kamranahmedse/design-patterns-for-humans#-abstract-factory
