## 设计

### 1. 开发层面的设计
按照我的理解，我会将设计分为以下几种。限于个人自身语文水平，以及语言本身表达能力的匮乏，这些设计的命名上似乎难以完全体现其区分。
为此，我都给出了不同设计的定义，以及示例。

1. **设计模式**：
   - **定义**：设计模式是针对特定问题的通用解决方案，旨在提高系统的灵活性和可扩展性。
   - **作用**：减少重复代码，降低耦合度，提高代码的可维护性和可读性。
   - **示例**：单一职责原则（SRP）、里氏替换原则（LSP）、依赖倒置原则（DIP）等。

2. **架构设计**：
   - **定义**：架构设计是对整个系统的高层次设计，涉及系统的整体结构和各个模块的划分。
   - **作用**：结合业务需求，划分不同的模块，分析哪些模块可能成为性能瓶颈并进行优化。
   - **示例**：一个支付系统的架构设计，包括从客户端发出请求、服务器端处理请求、校验余额、保证安全、存储数据、实现事务性等。

3. **模块设计**：
   - **定义**：模块设计是对系统中具体模块的设计，强调某一个具体功能的抽象。
   - **作用**：设计具体模块或功能的实现方式，提高模块的独立性和可维护性。
   - **示例**：事件队列、命令分发器、undo-redo实现、消息中心等。

4. **实现设计**：
   - **定义**：实现设计是基于具体开发语言的特性，完成性能或可扩展性的提升。
   - **作用**：利用编程语言的特性，优化代码性能，提升系统的可扩展性。
   - **示例**：使用 CRTP（Curiously Recurring Template Pattern）在编译期间实现多态，减少运行时开销。

5. **优化设计**：
   - **定义**：优化设计是基于某些先验假设，做出的优化改进。
   - **作用**：在特定场景下，通过优化设计提升系统性能。
   - **示例**：CAS（Compare-And-Swap）操作，通过无锁方式保证线程安全，解决 ABA 问题。

6. **数据设计**：
   - **定义**：数据设计涉及数据的存储、组织和管理，包括数据库设计、数据模型设计等。
   - **作用**：确保数据的完整性、一致性和高效访问。
   - **示例**：设计一个关系数据库模式，定义表、字段和关系。

7. **开发规范**：
   - **定义**：开发规范是出于安全和避免差错的一些设计原则，不属于设计模式的范畴。
   - **作用**：规范代码编写，提升代码质量，减少错误。
   - **示例**：`Effective C++` 中提到的条款，如避免使用魔法数、使用智能指针管理资源等。

### 2. 其他设计
除了这些开发层面上存在的设计之外，其实还有一些其他层面上的设计。

1. **用户体验设计（User Experience Design, UX Design）**：
   - **角度**：产品角度
   - **定义**：用户体验设计关注用户在使用产品时的整体体验，包括界面设计、交互设计、信息架构等。
   - **作用**：提高产品的可用性和用户满意度。
   - **示例**：设计一个直观的用户界面，使用户能够轻松完成任务。

2. **测试设计（Test Design）**：
   - **角度**：测试角度
   - **定义**：测试设计涉及测试用例的编写、测试策略的制定和测试工具的使用。
   - **作用**：确保软件的质量和可靠性。
   - **示例**：编写单元测试、集成测试和端到端测试用例，使用自动化测试工具进行测试。

3. **持续集成和持续部署设计（CI/CD Design）**：
   - **角度**：运维角度
   - **定义**：CI/CD 设计涉及自动化构建、测试和部署流程的设计。
   - **作用**：提高开发效率，减少手动操作，确保代码的持续交付。
   - **示例**：使用 Jenkins 或 GitHub Actions 设置自动化构建和部署流水线。

4. **安全设计（Security Design）**：
   - **角度**：安全角度，其实本质上也可以认为是开发的角度，但一般开发和安全开发还是有较大生殖隔离，因此独立出来。
   - **定义**：安全设计关注系统的安全性，包括身份验证、授权、数据加密等。
   - **作用**：保护系统和数据免受未经授权的访问和攻击。
   - **示例**：设计一个多因素身份验证系统，确保只有授权用户可以访问系统。

### 3. 总结
这里对各个场景下的设计给出了定义和示例。这些概念更多是个人的经验划分，并不完全是开发者群体的集体共识。
当个人觉得明确了这些不同设计层次的一些本质概念，将更有助于在实践中开发运用。
后面也会接着补充开发层面设计的相关博文。


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

1. https://github.com/karanpratapsingh/system-design
2. https://github.com/checkcheckzz/system-design-interview
3. https://github.com/InterviewReady/system-design-resources
4. https://github.com/ByteByteGoHq/system-design-101?tab=readme-ov-file#how-git-commands-work
5. https://github.com/donnemartin/system-design-primer/blob/master/README-zh-Hans.md#%E7%B3%BB%E7%BB%9F%E8%AE%BE%E8%AE%A1%E4%B8%BB%E9%A2%98%E4%BB%8E%E8%BF%99%E9%87%8C%E5%BC%80%E5%A7%8B
6. mvc

# What is system design?

System design is the process of defining the architecture, interfaces, and data
for a system that satisfies specific requirements. 

System design meets the needs of your business or organization through coherent and efficient systems. It requires
a systematic approach to building and engineering systems. 

A good system design requires us to think about everything, from infrastructure all the way down to the data and how it's stored.

