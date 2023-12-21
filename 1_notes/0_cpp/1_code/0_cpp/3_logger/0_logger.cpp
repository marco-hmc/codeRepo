#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>

// 全局变量
int globalVariable = 0;

// 读取输入并改变全局变量的函数
void readInputAndChangeGlobalVariable() {
    // 创建一个对话框
    QWidget dialog;
    QVBoxLayout layout(&dialog);

    // 创建一个标签和一个文本框
    QLabel label("请输入一个整数:", &dialog);
    QLineEdit input(&dialog);

    // 创建一个按钮
    QPushButton button("确定", &dialog);

    // 将按钮的点击事件与改变全局变量的函数关联
    QObject::connect(&button, &QPushButton::clicked, [&input]() {
        globalVariable = input.text().toInt();
    });

    // 将标签/文本框和按钮添加到布局中
    layout.addWidget(&label);
    layout.addWidget(&input);
    layout.addWidget(&button);

    // 显示对话框
    dialog.show();

    // 运行Qt应用程序的事件循环
    QApplication::exec();
}

// 输出消息的函数
void printMessage() {
    // 创建一个对话框
    QWidget dialog;
    QVBoxLayout layout(&dialog);

    // 创建一个标签来显示全局变量的值
    QLabel label("全局变量的值为:", &dialog);
    QLabel value(QString::number(globalVariable), &dialog);

    // 将标签添加到布局中
    layout.addWidget(&label);
    layout.addWidget(&value);

    // 显示对话框
    dialog.show();

    // 运行Qt应用程序的事件循环
    QApplication::exec();
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 读取输入并改变全局变量
    readInputAndChangeGlobalVariable();

    // 输出消息
    printMessage();

    return app.exec();
}
