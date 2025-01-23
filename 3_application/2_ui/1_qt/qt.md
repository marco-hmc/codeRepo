## qt

* **qt是什么？**
qt是一个跨平台的C++应用程序开发框架，不能简单理解为gui开发库。
一个开发框架一般会对程序流程强调控制权，并屏蔽这些逻辑的实现，减少开发心智负担。比如说开发qt程序的时候，不需要关心事件是如何传递的，信号是如何传递的；屏蔽了这些逻辑，只关注在对事件和信号的响应上。因此，应该把qt看成是一个c++应用程序开发框架。

* **qt核心模块**
* QtCore
    * 核心的非gui功能，如事件循环、信号和槽机制、文件目录操作、时间日期操作、多线程等
    * QObject, QTimer, QThread, QDir, QDataTime, QVariant, ...
* QtWidgets
    * 桌面应用控件，如按钮，文本框等
    * QWidget, QPushButton, QLabel, QLineEdit, QTextEdit, QComboBox, ...
* QtGui
    * gui相关功能，如绘图、图像处理、字体等
    * QPainter, QImage, QPixmap, QFont, QColor, ...
* QtNetwork
    * 网络编程相关功能
    * QTcpSocket, QTcpServer, ...
* QtSql
    * 数据库编程相关功能，不直接提供数据库功能，是作为中间层，提供访问不同数据库的统一api的。
    * QSqlQuery, QSqlDatabase
* QtMultimedia
    * 多媒体播放功能，新版本的qt6是用ffmpeg作为后端处理逻辑的。
    * QMediaPlayer
* QWebEngine
    * 网页
* QtQuick
    * QtWidget的新开发方式

### 1. QtCore

#### 1.1 QObject和信号槽

##### 1.1.1 QObject的基本功能
* **对象树和父子关系**
* **对象名称和类型**
* **动态属性**

##### 1.1.2 信号和槽机制
* **信号与槽的基本概念**
* **信号与槽的原理**

* QAction 干嘛用的？怎么用？
    可以这样理解，QAction 是对信号槽机制的一个高级封装，它不仅仅是一个信号槽函数，还添加了更多的功能，如快捷键、图标、状态提示等。
    所以就是一个信号槽，但是有快捷键，图标、状态提示等能力。

* ActionPool 干嘛用的？
    管理Action的，其实更多是一个manager的

##### 1.1.3 内存管理
* **QObject的内存管理机制**
* **父子关系**

##### 1.1.4 元对象系统
* **元对象系统的基本概念**
* **QMetaObject**
* **QMetaMethod**
* **动态属性和动态信号与槽**
* **使用元对象系统进行反射**

#### 1.2 QTimer和事件循环
* **事件的基本概念** 
* **事件循环** 
* **事件类型** 
* **自定义事件和事件过滤器** 

### 2. QtWidgets

#### 2.1 QtWidgets
#### 2.2 layout
#### 2.3 常用控件

### 3. QtGui
qt的QGraphicsScene什么概念
QPainter什么概念？

#### 3.1 QPainter



