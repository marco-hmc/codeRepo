* QAction 干嘛用的？怎么用？
    可以这样理解，QAction 是对信号槽机制的一个高级封装，它不仅仅是一个信号槽函数，还添加了更多的功能，如快捷键、图标、状态提示等。
    所以就是一个信号槽，但是有快捷键，图标、状态提示等能力。

* ActionPool 干嘛用的？
    管理Action的，其实更多是一个manager的



qt的QGraphicsScene什么概念
QPainter什么概念？

如果
```c++
QPainter painter;
painter.begin(device);
scene()->render(&painter);
painter.end();
```

在调用`scene()->render(&painter);`的时候出现了QGLContext::current == nullptr的错误，是什么原因导致的？