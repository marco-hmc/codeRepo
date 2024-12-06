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
