#include <QCoreApplication>
#include <QDebug>
#include <QVariant>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  // 存储整数类型
  QVariant intVariant = 42;
  qDebug() << "Integer Variant:" << intVariant.toInt();

  // 存储字符串类型
  QVariant stringVariant = "Hello, QVariant!";
  qDebug() << "String Variant:" << stringVariant.toString();

  // 存储浮点数类型
  QVariant doubleVariant = 3.14;
  qDebug() << "Double Variant:" << doubleVariant.toDouble();

  // 存储自定义类型
  QStringList stringList;
  stringList << "One"
             << "Two"
             << "Three";
  QVariant customVariant = QVariant::fromValue(stringList);
  qDebug() << "Custom Variant:" << customVariant.toStringList();

  return a.exec();
}