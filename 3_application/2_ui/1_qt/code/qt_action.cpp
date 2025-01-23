#include <QAction>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;

    // 创建一个 QAction 对象
    QAction *action = new QAction("Show Message", &mainWindow);
    // 设置快捷键
    action->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    // 设置工具提示
    action->setToolTip("Show a message box");
    // 连接信号和槽
    QObject::connect(action, &QAction::triggered, [&]() {
        QMessageBox::information(&mainWindow, "Message",
                                 "Hello, this is a message from QAction!");
    });

    // 将 QAction 添加到菜单栏
    QMenu *menu = mainWindow.menuBar()->addMenu("Actions");
    menu->addAction(action);

    mainWindow.show();
    return app.exec();
}
