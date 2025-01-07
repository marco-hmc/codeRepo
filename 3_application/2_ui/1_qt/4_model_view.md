## model-view 设计模式
在 Qt 框架中，Model-View 设计模式用于分离数据和用户界面。这个模式主要由三个组件组成：Model（模型）、View（视图）和 Delegate（委托）。下面是对 Model 和 View 关系的详细解释：

### 1. Model（模型）

- **职责**：模型负责管理数据。它提供数据的存储、访问和操作方法，但不负责数据的显示。
- **接口**：模型通过标准接口（如 `QAbstractItemModel`）与视图和委托进行交互。常见的模型类包括 `QStandardItemModel`、`QSqlTableModel` 和 `QFileSystemModel`。
- **数据访问**：模型提供方法来访问和修改数据，如 `data()`、`setData()`、`rowCount()` 和 `columnCount()`。

### 2. View（视图）

- **职责**：视图负责数据的显示。它从模型获取数据并将其呈现给用户，但不直接管理数据。
- **接口**：视图通过标准接口（如 `QAbstractItemView`）与模型和委托进行交互。常见的视图类包括 `QListView`、`QTableView` 和 `QTreeView`。
- **数据展示**：视图使用模型提供的数据来填充界面元素，并处理用户交互（如点击、选择）。

#### 2.1 view有哪些常见的操作函数？

### 3. Model 和 View 的关系

1. **分离关注点**：
   - 模型和视图的分离使得数据和显示逻辑独立。模型专注于数据管理，而视图专注于数据展示。
   - 这种分离使得同一个模型可以被多个视图共享，从而实现数据的一致性和代码的重用。

2. **数据流动**：
   - 视图通过模型接口获取数据，并在界面上显示。
   - 当用户在视图中进行操作（如编辑数据），视图会通过模型接口将更改传递给模型。

3. **信号和槽机制**：
   - 模型和视图之间通过信号和槽进行通信。例如，当模型中的数据发生变化时，会发出 `dataChanged` 信号，视图接收到信号后会更新显示。
   - 视图中的用户操作（如选择、编辑）也会通过信号和槽机制通知模型。

### 4. 示例代码

以下是一个简单的示例，展示了如何在 Qt 中使用模型和视图：

```cpp
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 创建模型
    QStandardItemModel model(4, 2); // 4 行 2 列
    model.setHorizontalHeaderLabels({"Name", "Age"});

    // 填充数据
    model.setItem(0, 0, new QStandardItem("Alice"));
    model.setItem(0, 1, new QStandardItem("30"));
    model.setItem(1, 0, new QStandardItem("Bob"));
    model.setItem(1, 1, new QStandardItem("25"));
    model.setItem(2, 0, new QStandardItem("Charlie"));
    model.setItem(2, 1, new QStandardItem("35"));
    model.setItem(3, 0, new QStandardItem("Diana"));
    model.setItem(3, 1, new QStandardItem("28"));

    // 创建视图
    QTableView view;
    view.setModel(&model); // 将模型设置给视图
    view.show();

    return app.exec();
}
```

### 5. 总结

- **模型**：负责数据的存储和管理，通过标准接口与视图和委托交互。
- **视图**：负责数据的显示，从模型获取数据并呈现给用户。
- **关系**：模型和视图通过标准接口和信号槽机制进行通信，实现数据和显示的分离。

### 99. quiz
#### 1. model绑定什么类型信号？view绑定什么类型信号？

