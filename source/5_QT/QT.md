## QT
### 1. concepts
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
