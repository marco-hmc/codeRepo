## 如何理解 mvc 架构?

### 1. concepts

#### 1.1 什么是 mvc 架构

MVC（Model-View-Controller）是一种软件架构模式，广泛应用于开发用户界面应用程序。它将应用程序分为三个主要部分：模型（Model）、视图（View）和控制器（Controller）。这种分离有助于组织代码，提高可维护性和可扩展性。

- **模型（Model）**
  模型是应用程序的核心部分，负责处理应用程序的数据逻辑。模型直接管理数据、逻辑和规则。它通常与数据库交互，执行数据的创建、读取、更新和删除（CRUD）操作。

主要职责：

- 处理和管理数据。
- 执行业务逻辑。
- 与数据库或其他数据源交互。

* **视图（View）**
  视图是用户界面部分，负责显示数据。视图从模型中获取数据，并将其呈现给用户。视图不包含任何业务逻辑，只负责数据的展示。

主要职责：

- 显示数据。
- 提供用户交互界面。

* **控制器（Controller）**
  控制器是应用程序的中介部分，负责处理用户输入。控制器从视图接收输入，处理这些输入并更新模型或视图。控制器将用户的动作转换为对模型的操作，并决定哪个视图来显示数据。

主要职责：

- 处理用户输入。
- 调用模型更新数据。
- 选择视图来显示数据。

* **MVC 工作流程**

1. 用户通过视图与应用程序交互（例如，点击按钮、输入数据）。
2. 控制器接收用户输入，并调用模型来处理数据。
3. 模型更新数据后，通知视图数据已更新。
4. 视图从模型获取最新数据，并将其呈现给用户。

#### 1.2 mvc 架构有什么好处？

mvc 是实现解耦的一种手段，所以 mvc 的好处就是解耦的好处，如分离关注点，提升可维护性，提升扩展性，提上可测试性等等。

#### 1.3 qt 是怎么体现 mvc 架构的？

#### qt 中的 mvc 分别是通过哪些类来体现的

在 Qt 中,MVC(Model-View-Controller)架构是通过以下几类主要的类来体现的:

1. 模型(Model):Qt 提供了`QAbstractItemModel`类作为所有模型类的基类.你可以通过继承`QAbstractItemModel`或其子类(如`QStandardItemModel`/`QSortFilterProxyModel`等)来创建自己的模型类.

2. 视图(View):Qt 提供了多种视图类,如`QListView`/`QTableView`/`QTreeView`等,它们都继承自`QAbstractItemView`类.这些视图类可以用来显示模型中的数据.

3. 控制器(Controller):在 Qt 中,控制器的功能通常由视图类和模型类共同实现.例如,视图类会处理用户的输入事件,并将这些事件转化为对模型的操作.此外,Qt 还提供了`QItemSelectionModel`类来管理用户在视图中的选择.

以下是一个简单的例子,展示了如何在 Qt 中使用 MVC 架构:

```cpp
// 创建模型
QStandardItemModel *model = new QStandardItemModel(5, 3);
for (int row = 0; row < 5; ++row) {
    for (int column = 0; column < 3; ++column) {
        QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
        model->setItem(row, column, item);
    }
}

// 创建视图
QTableView *view = new QTableView;
view->setModel(model);

// 创建选择模型
QItemSelectionModel *selectionModel = view->selectionModel();
connect(selectionModel, &QItemSelectionModel::selectionChanged,
        this, &MainWindow::updateSelection);

// ...

void MainWindow::updateSelection(const QItemSelection &selected, const QItemSelection &deselected)
{
    // handle selection changes
}
```

在这个例子中,我们首先创建了一个`QStandardItemModel`模型和一个`QTableView`视图,并将模型设置到视图中.然后,我们获取了视图的`QItemSelectionModel`,并连接了其`selectionChanged`信号,以便在用户的选择改变时更新界面.




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

### MVC, MVP, MVVM, MVVM-C, and VIPER
These architecture patterns are among the most commonly used in app development, whether on iOS or Android platforms. Developers have introduced them to overcome the limitations of earlier patterns. So, how do they differ? 

<p>
  <img src="images/client arch patterns.png" style="width: 720px" />
</p>

- MVC, the oldest pattern, dates back almost 50 years 
- Every pattern has a "view" (V) responsible for displaying content and receiving user input 
- Most patterns include a "model" (M) to manage business data 
- "Controller," "presenter," and "view-model" are translators that mediate between the view and the model ("entity" in the VIPER pattern)
