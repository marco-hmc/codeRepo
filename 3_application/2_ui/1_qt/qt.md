## qt

- **qt 是什么？**
  qt 是一个跨平台的 C++应用程序开发框架，不能简单理解为 gui 开发库。
  一个开发框架一般会对程序流程强调控制权，并屏蔽这些逻辑的实现，减少开发心智负担。比如说开发 qt 程序的时候，不需要关心事件是如何传递的，信号是如何传递的；屏蔽了这些逻辑，只关注在对事件和信号的响应上。因此，应该把 qt 看成是一个 c++应用程序开发框架。

- **qt 核心模块**
- QtCore
  - 核心的非 gui 功能，如事件循环、信号和槽机制、文件目录操作、时间日期操作、多线程等
  - QObject, QTimer, QThread, QDir, QDataTime, QVariant, ...
- QtWidgets
  - 桌面应用控件，如按钮，文本框等
  - QWidget, QPushButton, QLabel, QLineEdit, QTextEdit, QComboBox, ...
- QtGui
  - gui 相关功能，如绘图、图像处理、字体等
  - QPainter, QImage, QPixmap, QFont, QColor, ...
- QtNetwork
  - 网络编程相关功能
  - QTcpSocket, QTcpServer, ...
- QtSql
  - 数据库编程相关功能，不直接提供数据库功能，是作为中间层，提供访问不同数据库的统一 api 的。
  - QSqlQuery, QSqlDatabase
- QtMultimedia
  - 多媒体播放功能，新版本的 qt6 是用 ffmpeg 作为后端处理逻辑的。
  - QMediaPlayer
- QWebEngine
  - 网页
- QtQuick
  - QtWidget 的新开发方式

### 1. QtCore

#### 1.1 QObject 和信号槽

##### 1.1.1 QObject 的基本功能

- **对象树和父子关系**
  `QObject` 提供了一个对象树结构，用于管理对象之间的父子关系。这种层次结构有助于自动管理对象的生命周期。

  - **父对象和子对象**：
    - 每个 `QObject` 对象可以有一个父对象和多个子对象。
    - 当一个 `QObject` 对象被销毁时，它的所有子对象也会被自动销毁。
    - 通过这种方式，可以避免内存泄漏，并确保对象在不再需要时被正确释放。
    - 代码例子
      ```cpp
          QObject *parent = new QObject();
          QObject *child = new QObject(parent);
          // 或者
          child->setParent(parent);
          QList<QObject*> children = parent->children();
      ```
  - **意义**
    - 提供关系。
    - 子对象的声明周期委托给父对象；当 QObject 是正常栈变量的时候，区别不大；但是 QObject 对象是堆变量的时候，父对象析构就会连带着把子对象析构了。
    - 子对象析构的时候，会发出`destroy`信号到父对象，父对象会移除子对象。

- **对象名称和类型**
  `QObject` 提供了对象名称和类型的功能，用于标识和区分不同的对象。

  ```cpp
      QObject *obj = new QObject();
      obj->setObjectName("myObject");
      QString name = obj->objectName();

      QObject *obj = new QObject();
      const QMetaObject *metaObj = obj->metaObject();
      QString className = metaObj->className();
  ```

- **动态属性**
  `QObject` 提供了动态属性的功能，允许在运行时为对象添加、修改和删除属性。
  - 例如：
    ```cpp
    QObject *obj = new QObject();
    obj->setProperty("dynamicProperty", 123);  // add
    QVariant value = obj->property("dynamicProperty");  // get
    obj->setProperty("dynamicProperty", QVariant());  // delete
    QList<QByteArray> properties = obj->dynamicPropertyNames(); // list
    ```

##### 1.1.2 信号和槽机制

- **信号与槽的基本概念**
  信号与槽（Signals and Slots）是 Qt 框架中用于对象间通信的机制。它允许对象之间进行松耦合的通信，是事件驱动编程的核心。

  ```cpp
  class MyObject : public QObject {
      Q_OBJECT
  public:
      signals:
          void mySignal(int value);

      slots:
          void mySlot(int value) {
              qDebug() << "Slot called with value:" << value;
          }
  };

  void doSomething(){
      connect(sender, SIGNAL(signalName(parameters)), receiver, SLOT(slotName(parameters))); // 信号绑定
  }
  ```

- **信号与槽的原理**
  信号与槽的实现依赖于 Qt 的元对象系统。简单来说，Qt 的元对象编译器（moc）是一个预处理工具，它会解析包含 Q_OBJECT 宏的类，并生成相应的元对象代码。这是因为 c++本身不支持一些反射相关的机制，因此 qt 通过模板元的方式生成代码去做了一些原来 c++机制很难直接做到的事情。

  调用 connect 的时候，就会把信号和槽的关系存储在元对象系统中。而调用了 emit 发射信号的时候，背后自动生成的代码就会找到对应的槽函数完成触发。

- **QAction 干嘛用的？怎么用？**
  可以这样理解，QAction 是对信号槽机制的一个高级封装，它不仅仅是一个信号槽函数，还添加了更多的功能，如快捷键、图标、状态提示等。
  所以就是一个信号槽，但是有快捷键，图标、状态提示等能力。

##### 1.1.3 元对象系统

- **元对象系统的基本概念**
  Qt 的元对象系统（Meta-Object System）是 Qt 框架的核心部分之一，它提供了对类的元信息（如类名、属性、信号和槽等）的支持。元对象系统使得 Qt 能够实现信号与槽机制、动态属性、反射等高级功能。

  1. **信号与槽机制**：支持对象之间的松耦合通信。
  2. **动态属性**：允许在运行时为对象添加、修改和删除属性。
  3. **反射**：允许在运行时访问和操作对象的元信息。

- **QMetaObject**

  1. **类名**：获取类的名称。
  2. **属性**：获取类的属性信息。
  3. **信号与槽**：获取类的信号与槽信息。
  4. **方法**：获取类的方法信息。

- **QMetaMethod**

  1. **方法名称**：获取方法的名称。
  2. **参数类型**：获取方法的参数类型。
  3. **调用方法**：在运行时调用方法。

- **使用元对象系统进行反射**
  反射是指在运行时检查和调用对象的属性和方法的能力。Qt 的元对象系统提供了反射功能，允许在运行时访问和操作对象的元信息。

  1. **获取类名**：使用 `className` 方法获取类名。
  2. **获取属性**：使用 `property` 方法获取属性。
  3. **调用方法**：使用 `invoke` 方法调用方法。

  ```cpp
      #include <QObject>
      #include <QDebug>
      #include <QMetaProperty>

      class MyObject : public QObject {
          Q_OBJECT
          Q_PROPERTY(int value READ value WRITE setValue)
      public:
          MyObject(QObject *parent = nullptr) : QObject(parent), m_value(0) {}

          int value() const { return m_value; }
          void setValue(int value) { m_value = value; }

      private:
          int m_value;
      };

      int main() {
          MyObject obj;
          const QMetaObject *metaObj = obj.metaObject();

          qDebug() << "Class name:" << metaObj->className();

          QMetaProperty prop = metaObj->property(metaObj->indexOfProperty("value"));
          qDebug() << "Property name:" << prop.name();
          qDebug() << "Property value:" << prop.read(&obj).toInt();

          prop.write(&obj, 42);
          qDebug() << "New property value:" << prop.read(&obj).toInt();

          return 0;
      }
  ```

#### 1.2 QTimer 和事件循环

- **事件的基本概念**
- **事件循环**
- **事件类型**
- **自定义事件和事件过滤器**

### 2. QtWidgets

#### 2.1 QtWidgets

#### 2.2 layout

#### 2.3 常用控件

### 3. QtGui

qt 的 QGraphicsScene 什么概念
QPainter 什么概念？

#### 3.1 QPainter

### 99. quiz

#### 1. 关闭控件的时候，是如何析构的？
