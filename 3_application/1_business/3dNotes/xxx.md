## 《Qt事件循环机制介绍》

### 1.事件循环的基本概念
    在Qt框架中，事件循环（Event Loop）起着中枢的角色，它负责管理和处理应用程序中发生的各种事件。用户可能在界面上点击、输入或进行其他操作，系统可能会产生定时器事件或者状态变化通知。
所有这些事件都需要被程序捕捉并作出相应的响应。事件循环基于队列的机制，用于循环处理事件。当事件队列中有待处理的事件时，事件循环将激活并处理这些事件；如果队列为空，事件循环则会进入阻塞状态，等待新的事件发生。

    通过事件循环，Qt应用能够以非阻塞的方式响应用户的交互，使界面保持响应状态，同时也能处理其他异步事件。这种模型使得程序能够在等待事件发生时保持低功耗状态，只在必要时才唤醒执行相关操作，从而高效地利用系统资源。本文将讲解Qt事件循环的工作原理，相关源码的实现，以及ZW3D对事件循环机制的运用。

### 2 事件循环的执行流程
#### 2.1 事件循环对事件的管理

    Qt的程序运行依赖于事件的执行，事件的执行流程包括事件的创建、排队、循环检查和处理，主要靠事件循环会管理上述过程。以下是一个简化的代码示例：
```c++
#include <QCoreApplication>
#include <QEvent>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QEvent *event = new QEvent(QEvent::User);
    QWidget *widget = new QWidget;
    QApplication::postEvent(widget, event);
    return app.exec();
}

void QWidget::customEvent(QEvent *event) {
    if (event->type() == QEvent::User) {
    }
}
```


#### 2.2 子事件循环的使用

    在ZW3D中，事件处理的接口使用了子事件循环来支撑业务的某些操作，这里指的是除了客户端启动时创建的事件循环外，开发者在函数中自行创建QEventLoop对象来进行操作，允许在不中断主事件循环的情况下处理事件。

    举一个简单的Qt子事件循环示例：
```c++
#include <QCoreApplication>
#include <QEventLoop>

void longRunningOperation() {
    QEventLoop loop;
    QTimer::singleShot(5000, &loop, &QEventLoop::quit);
    loop.exec();
    qDebug() << "长时间操作完成，事件循环结束";
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    longRunningOperation();
    return app.exec();
}
```

    在这个示例中创建了一个QEventLoop对象loop。使用QTimer::singleShot来模拟一个长时间操作的结束，并在操作完成时退出事件循环。通过调用loop.exec()，程序进入子事件循环，在长时间操作进行的同时，依然能够处理其他事件，如用户界面交互。子事件循环的主要使用原因包括：

处理模态对话框：在显示模态对话框时，通常需要暂停当前函数的执行，等待用户输入。子事件循环可以在不阻塞主事件循环的情况下实现这一点。
长时间操作：在执行耗时操作时，为了保持界面的响应性，可以使用子事件循环来处理UI事件。
复杂的事件处理：在某些高级用法中，可能需要在处理某个事件时同时响应其他事件，子事件循环在这种场景下非常有用。

### 3. Qt事件循环的源码分析
#### 3.1 相关组件介绍

    Qt的事件循环机制建立在几个关键的类和组件上，这些类和组件共同构成了事件处理的整体框架。

QEventLoop是Qt事件循环的核心类，位于QtCore模块中。它管理着一个基于事件的循环，用以处理和分发事件。这个类提供了控制事件循环的基本方法，如exec()用于启动循环，exit()用于退出循环，以及processEvents()用于在需要时处理当前的事件。
QCoreApplication和QApplication提供应用级别的管理。QCoreApplication提供了跨平台的应用程序功能，包括事件循环的初始化和事件处理。它是所有Qt应用程序的基础。QApplication继承自QCoreApplication，增加了对GUI应用所特有的支持，如处理窗口系统事件。这两个类在启动时会创建并管理一个QEventLoop实例，负责整个应用程序的事件处理。
Qt中的事件队列是通过QCoreApplication的私有成员实现的，这个队列存储了所有待处理的事件。事件分发是通过QCoreApplication的notify()方法实现的。该方法决定了如何将事件从队列中取出并分发给正确的对象。

#### 3.2 qeventloop类介绍

1. 构造函数和析构函数

QEventLoop(QObject *parent = nullptr): 创建一个事件循环。parent 参数用于指定父对象。
~QEventLoop(): 析构函数。

2. 主要方法：

接口名称

	

作用




void exec(QEventLoop::ProcessEventsFlags flags = AllEvents)

	

开始事件循环。flags 参数指定事件循环应该如何处理事件




void exit(int returnCode = 0)

	

使事件循环退出。returnCode 参数指定事件循环返回的值




bool isRunning() const

	

返回事件循环是否正在运行




void processEvents(QEventLoop::ProcessEventsFlags flags = AllEvents)

	

处理所有待处理的事件




void wakeUp()

	

唤醒事件循环，使之能够处理更多事件

3. 信号

void quit(): 当调用此函数时，会导致事件循环退出。

4. 使用示例
这里先给出一些简单的通用示例，后面再给出ZW3D中对这些接口的运用，借助上下文说明他们的使用场景和作用。

exec()接口和quit接口的调用，在这个示例中，当网络请求完成时，finished 信号被触发，导致事件循环退出。
 QEventLoop loop;
 // 配置一些异步操作，如启动一个网络请求
 QNetworkAccessManager manager;
 manager-&gt;get(QNetworkRequest(QUrl(&quot;[http://example.com/file|http://example.com/file]&quot;)));

 QObject::connect(manager, &amp;QNetworkAccessManager::finished, &amp;loop, &amp;QEventLoop::quit);

 loop.exec();  // 启动局部事件循环，等待异步操作完成

isRunning()接口的调用，用来确认事件循环是否激活，以便程序可以据此做出适当的响应。
QEventLoop loop;

// 在其他地方
if (loop.isRunning()) {
    // 如果事件循环正在运行，执行特定操作
    // ...
}





    判断isRunning有以下作用，首先是避免重复启动事件循环：如果试图在一个已经运行的事件循环上调用 exec()，可能会导致程序行为异常或崩溃。其次确保安全退出：在某些情况下可能需要在事件循环完成特定任务后安全地退出。通过使用 isRunning() 检查事件循环的状态，可以确定何时安全地调用 exit() 或 quit()，以避免非预期的退出或资源泄露。在ZW3D中，也封装了isCurrentLoopRunning接口来辅助业务做判断。

processEvents的调用，允许事件循环处理当前待处理的事件，并立即返回。这在需要临时处理事件而不阻塞当前线程的场景中非常有用。

QEventLoop loop;
while (longRunningOperation.isNotFinished()) {
    // 执行长时间运行的操作的一部分
    // ...

    // 临时处理事件
    loop.processEvents();

    // 检查是否应该取消操作
    if (shouldCancelOperation) {
        break;
    }
}
// 长时间运行的操作完成或被取消


    在这段代码中， while 循环长时间运行的操作被分成多个小部分执行，避免一次性占用太长时间无法响应用户界面。在每个小部分操作后，调用 processEvents() 方法。这个方法使得事件循环有机会处理其他事件，比如用户界面的更新、按钮点击等。因此，即使长时间操作正在进行，用户界面仍然保持响应。然后在每次调用 processEvents() 后，代码检查是否存在取消操作的标志（shouldCancelOperation）。如果这个标志被设置（例如，用户点击了取消按钮），则跳出循环，长时间操作被取消。

wakeUp函数在Qt事件循环中用于唤醒一个阻塞中的事件循环。通常情况如果事件队列中没有事件，事件循环会进入阻塞状态，等待新的事件出现。wakeUp()方法的调用会使事件循环从这种等待状态中立即返回，即使队列中没有新事件。在复杂的场景如多线程交互的情况下可能会用到，ZW3D中一直使用continueMessage等方式驱动事件循环的遍历，也不涉及多线程，所以没有对此函数的调用。

#### 3.3 ZW3D中对qeventloop接口的运用
    ZW3D的交互以鼠标在在Qt界面上触发事件，进入内部的指令系统进行处理的，创建指令以及放入指令管道的部分可以阅读指令调度的文章，这里主要介绍ZW3D的指令模块中利用Qt的事件循环来获取发送过来的指令并执行的过程。
在ZW3D的NUI模块中，使用了qeventloop的接口来执行相关业务逻辑，查看项目代码可知，事件循环的部分主要集中在DiDrawingStudio中对内部变量QList<QEventLoop *> _loops的使用上。在事件循环的基础之上，构建了一系列接口，展示如下：

```c++
int start()
int enterLoop(int loopId, const QString &form)
int leaveLoop(int loopId, int data)
int getLoopId(const QString &sForm)
int getCurrentLoopId()
bool isCurrentLoopRunning()
int awake()
int pulse()
```

    在上述代码的定义中，使用了前面介绍的事件循环接口来实现业务，下面进行具体介绍。

start函数是在软件启动时由main函数触发的，和Qt平台的其他客户端一样，ZW3D在start函数中执行了事件过滤器的安装，最终执行exec进入主循环，开始了主事件循环的事件处理。
enterloop函数在InWait函数中被调用，用于进入指定loopId的事件循环，去处理指定的form上的事件。这里会创建子事件循环来执行业务，而不干扰主事件循环，下面分析这个函数的关键部分：

    首先，进行事件循环的创建和配置：
```c++
QEventLoop item(this);
item.setProperty("loop", loop);
item.setProperty("form", form);
item.setProperty("earlyExit", 0xFF);
```

    这里创建了一个QEventLoop对象item。通过setProperty方法，给事件循环设置了几个属性，包括loop、form和earlyExit。这些属性用于在事件循环的不同阶段进行状态记录和一些后续判断。

    使用_loops管理创建的子事件循环：

```c++
// ...
ZS_GUARD([&] { d->_loops.push_back(&item); }, [&] { d->_loops.pop_back(); });
// ...
```

    ZS_GUARD宏确保在作用域开始时将临时的事件循环加入到内部变量_loops管理，并在作用域结束时安全地删除该事件循环，保证资源清理或状态恢复。

    开始处理事件：
```c++
item.processEvents(QEventLoop::EventLoopExec);
...
item.exec()
...
item.processEvents(QEventLoop::EventLoopExec);
```

   processEvents方法被调用来处理当前的事件。这里在执行item.exec()之前和之后都处理一次事件。首先在事件循环正式启动之前处理所有已经在队列中的事件，避免在事件循环开始之前由于未处理的事件导致的不一致状态。在item触发事件循环期间，可能会有新的事件产生并加入到队列中。exec()返回后立即处理这些事件可以确保应用程序状态的及时更新。并通过continueMessage推动事件循环的不断执行。

    接下来执行事件循环：
```c++
int result = 0;
if (item.property("earlyExit").toInt() != 0xFF) {
    result = item.property("earlyExit").toInt();
} else {
    item.setProperty("executing", true);
    result = item.exec();
    item.setProperty("executing", false);
}
```

这部分代码首先检查earlyExit属性，如果它被修改过（不是0xFF），则使用这个值作为函数的返回值。如果没有提前退出，就执行item.exec()进入事件循环，等待事件的发生。

leaveLoop函数在InReturn函数中被调用，来退出指定loopId的事件循环。
```c++
for (int i = d->_loops.size() - 1; i >= 0; i--)
   {
       auto item = d->_loops[i];
       if (item->property("loop").toInt() == loop)
       {
           if (item->isRunning())
           {
               item->exit(data);
           }
           /* If QEventLoop::exit() has been called while QEventLoop::exec() is not return yet. */
           else if (item->property("executing").isValid() && item->property("executing").toBool())
           {
               /* The variable 'interrupt' in EventDispatcher will be set to 'true' as long as QEventLoop::exit() is called.
                  But if we call QEventLoop::processEvents() after that, 'interrupt' will be covered to 'false', which causes
                  our QEventLoop::exec() return not so soon. So we always call interrupt() here. */
               QAbstractEventDispatcher *dispatcher = this->eventDispatcher();
               if (dispatcher)
               {
                   dispatcher->interrupt();
               }
           }
           else
           {
               item->setProperty("earlyExit", data);
           }
           return 0;
       }
   }
 ```
    在这段代码中，leaveLoop对DrawingStudio管理的_loops进行遍历，这里便用到了前面提到的isRunning()，判断为true后对该事件循环执行exit()。如果exit()已经调用，此时isRunning()已经返回false， 但此时可能exec()还并未返回，此时判断事件事件循环的executing字段是否为true，使用事件分发器dispatcher执行interrupt函数打断，可以使事件循环快速退出，而不是自然结束。

#### 3.4 Qt事件循环源码分析

    下面继续介绍Qt事件循环的源码，在事件循环进行遍历处理事件之前，事件会先通过sendEvent或postEvent的形式派发，区别在于调用sendEvent的事件会立刻执行，调用postEvent的事件会先插入事件队列，由事件循环遍历取出执行派发，具体可阅读《Qt事件的分类与派发》。接下来主要介绍当事件循环如何运转去遍历获取队列中的事件并发送出去的过程。

首先，在Qt GUI应用程序的入口点，即main函数中，看到如何启动应用程序并引入事件循环：
```c++
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
```

    QApplication的实例化是必要的步骤，它设置了应用程序的基本环境和参数。然后主窗口被创建并显示。通过调用a.exec()，事件循环被启动,使程序保持运行并响应事件，如鼠标点击或按键。

   1.  进入QCoreApplication::exec函数，
```c++
int QCoreApplication::exec()
{
    ...

    threadData->quitNow = false;
    QEventLoop eventLoop;
    self->d_func()->in_exec = true;
    self->d_func()->aboutToQuitEmitted = false;
    int returnCode = eventLoop.exec();

    ...
}
```

    在这个函数中， QEventLoop对象被创建并启动, 通过调用自己的exec方法来运行事件循环，负责管理事件队列并处理事件。

2. 进入QEventLoop::exec函数，
```c++
int QEventLoop::exec(ProcessEventsFlags flags)
{
    // ...

    while (!d->exit.loadAcquire())
        processEvents(flags | WaitForMoreEvents | EventLoopExec);

    ref.exceptionCaught = false;
    return d->returnCode.loadRelaxed();
}
```

可见，QEventLoop::exec包含了一个循环，这个循环不断调用processEvents方法来处理事件。这里的WaitForMoreEvents标志意味着，在没有新事件时，循环将阻塞以等待事件的到来。

3. 进入QCoreApplication::processEvents函数，
```c++
void QCoreApplication::processEvents(QEventLoop::ProcessEventsFlags flags, int ms)
{
    QThreadData *data = QThreadData::current();
    if (!data->hasEventDispatcher())
        return;
    QElapsedTimer start;
    start.start();
    while (data->eventDispatcher.loadRelaxed()->processEvents(flags & ~QEventLoop::WaitForMoreEvents)) {
        if (start.elapsed() > ms)
            break;
    }
}
```

    在processEvents方法中，Qt框架调用了当前线程的事件调度器QAbstractEventDispatcher。这个抽象基类根据不同的操作系统平台有不同的实现。在 Windows 平台上，Qt 使用 QEventDispatcherWin32 类来实现 QAbstractEventDispatcher。以Windows平台下的QEventDispatcherWin32实现为例分析。

4. QEventDispatcherWin32的事件处理:
```c++
bool QEventDispatcherWin32::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    Q_D(QEventDispatcherWin32);

    ...

    // To prevent livelocks, send posted events once per iteration.
    sendPostedEvents();

    ...
}
```

5. 发送排队的事件：QEventDispatcherWin32::sendPostedEvents
```c++
void QEventDispatcherWin32::sendPostedEvents()
{
    Q_D(QEventDispatcherWin32);

    if (d->sendPostedEventsTimerId != 0)
        KillTimer(d->internalHwnd, d->sendPostedEventsTimerId);
    d->sendPostedEventsTimerId = 0;

    d->wakeUps.storeRelaxed(0);

    QCoreApplicationPrivate::sendPostedEvents(0, 0, d->threadData.loadRelaxed());
}
```

    这部分代码展示了事件调度器如何处理事件队列，并最终调用QCoreApplication的sendPostEvents方法。

6. QCoreApplicationPrivate::sendPostedEvents：事件发送逻辑
```c++
void QCoreApplicationPrivate::sendPostedEvents(QObject *receiver, int event_type,
                                               QThreadData *data)
{
    // ...

    if (receiver && receiver->d_func()->threadData != data) {
        qWarning("QCoreApplication::sendPostedEvents: Cannot send "
                 "posted events for objects in another thread");
        return;
    }

    ...

    while (i < data->postEventList.size()) {
       ...

        QEvent *e = pe.event;
        QObject * r = pe.receiver;

        ...

        QCoreApplication::sendEvent(r, e);

        ...
    }
}
```

    这段代码做了线程检查，确保事件只在它们所属的线程中被发送。之后就会遍历事件列表，为每个事件对象调用sendEvent方法，以便将事件发送到目标对象。

### 4. 总结

    本文主要探讨了Qt框架中事件循环机制的原理，以及在ZW3D中的应用。首先，介绍了事件循环的基本概念，通过事件队列机制解释了事件处理的流程，展示了事件循环如何根据队列的状态来决定事件处理的时机。接着，通过示例代码详细讲解了Qt程序中事件的生成、排队和处理流程，并讲解了子事件循环在特定任务处理中的应用，如模态对话框和长时间操作。接下来，分析了ZW3D项目代码中对Qt事件循环的运用，并对典型的一些接口进行介绍。此外还分析了QEventLoop和QCoreApplication等关键类的代码流程，展示了事件在事件循环中的处理和分发机制。
