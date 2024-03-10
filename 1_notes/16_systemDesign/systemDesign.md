将应用程序划分为三种组件,模型 - 视图 - 控制器(MVC)设计定义它们之间的相互作用.[[2\]](https://zh.wikipedia.org/wiki/MVC#cite_note-posa-2)

- **模型(Model)**

  ​	用于封装与应用程序的业务逻辑相关的数据以及对数据的处理方法." Model  "有对数据直接访问的权力,例如对数据库的访问."Model"不依赖"View"和"Controller",也就是说, Model  不关心它会被如何显示或是如何被操作.但是 Model 中数据的变化一般会通过一种刷新机制被公布.为了实现这种机制,那些用于监视此 Model 的 View 必须事先在此 Model 上注册,从而,View 可以了解在数据 Model 上发生的改变.(比如:[观察者模式](https://zh.wikipedia.org/wiki/观察者模式)([软件设计模式](https://zh.wikipedia.org/wiki/软件设计模式)))

- **视图(View)**

  ​	能够实现数据有目的的显示(理论上,这不是必需的).在 View 中一般没有程序上的逻辑.为了实现 View 上的刷新功能,View 需要访问它监视的数据模型(Model),因此应该事先在被它监视的数据那里注册.

- **控制器(Controller)**

  ​	起到不同层面间的组织作用,用于控制应用程序的流程.它处理事件并作出响应."事件"包括用户的行为和数据 Model 上的改变.

MVC模式在概念上强调 Model, View, Controller 的分离,各个模块也遵循着由 Controller  来处理消息,Model 掌管数据源,View 负责数据显示的职责分离原则,因此在实现上,MVC 模式的 Framework 通常会将 MVC  三个部分分离实现:

- Model 负责数据访问,较现代的 Framework 都会建议使用独立的数据对象 (DTO, POCO, POJO 等)  来替代弱类型的集合对象.数据访问的代码会使用 Data Access 的代码或是 ORM-based Framework,也可以进一步使用  Repository Pattern 与 Unit of Works Pattern 来切割数据源的相依性.
- View 负责显示数据,这个部分多为前端应用,而 Controller 会有一个机制将处理的结果 (可能是 Model,  集合或是状态等) 交给 View,然后由 View 来决定怎么显示.例如 Spring Framework 使用 JSP  或相应技术,ASP.NET MVC 则使用 Razor 处理数据的显示.
- Controller 负责处理消息,较高端的 Framework 会有一个默认的实现来作为 Controller 的基础,例如  Spring 的 DispatcherServlet 或是 ASP.NET MVC 的 Controller 等,在职责分离原则的基础上,每个  Controller 负责的部分不同,因此会将各个 Controller 切割成不同的文件以利维护.

