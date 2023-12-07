## QT
### 1. concepts
* q_property有什么用?
  使用 Q_PROPERTY 宏和直接在 public 部分定义变量有几个主要的区别:

  封装:使用 Q_PROPERTY 宏,你可以提供 getter 和 setter 方法来控制对属性的访问,这提供了更好的封装.你可以在 setter 方法中添加额外的逻辑,例如检查新值的有效性,或者在值改变时发出通知信号.而直接公开变量则无法提供这些功能.

  元对象系统:Q_PROPERTY 定义的属性可以通过 Qt 的元对象系统进行访问.这意味着你可以在运行时动态地获取和设置属性的值,或者查询属性的类型等信息.而直接公开的变量则无法通过元对象系统访问.

  工具支持:Q_PROPERTY 定义的属性可以被 Qt Designer 和其他工具识别和编辑.例如,你可以在 Qt Designer 中直接编辑 QWidget 对象的属性,或者使用 QML 绑定到 QObject 的属性.而直接公开的变量则无法享受这些工具的支持.

  总的来说,虽然 Q_PROPERTY 宏的使用可能会增加一些代码复杂性,但它提供了更强大和灵活的功能.

* 什么是信号槽？
* QT怎么画界面？
* QT布局怎么设定？
* 什么是样式？
* 什么是parent()
* 什么是event和eventFilter
* 信号槽和event()某种程度上，两者可以实现一样的功能。那两者的区别是什么呢？


### 2. grammar
* 1. QT中ui和business logic是如何耦合的？
* 2. QApplication有什么用？
* 3. 什么是ui_foo.h文件？
* 4. 什么是moc_foo.cpp文件？
* 5. 什么是dockWidget,centralWidget?
* 6. 什么是widget?
* 7. 为什么qt要自己弄一套数据结构？
* 8. type= user Type+1是什么用法？node.h::22
* 9. .exec()和.show()有什么用？
* 10. widget中有哪些方法需要注意
  * eventFilter()
  * QEvent
    * QInputEvent
      * contextMenuEvent()
      * hoverEvent()
      * keyEvent()
      * mouseEvent()
      * nativeGestureEvent()
      * tableEvent()
      * touchEvent()
      * wheelEvent()
    * timerEvent()
  * hover
