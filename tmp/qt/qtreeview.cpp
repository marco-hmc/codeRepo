#include <QApplication>
#include <QStandardItemModel>
#include <QTreeView>
#include <vector>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // 创建TreeView和两个模型
  QTreeView treeView;
  QStandardItemModel model1;
  QStandardItemModel model2;

  // 设置模型1的数据
  QStandardItem *item1 = new QStandardItem("Item 1");
  model1.appendRow(item1);

  // 设置模型2的数据
  QStandardItem *item2 = new QStandardItem("Item 2");
  model2.appendRow(item2);

  // 设置TreeView的模型为模型1
  treeView.setModel(&model1);
  treeView.show();

  // 更改模型1的数据
  item1->setText("Modified Item 1");

  // 切换模型为模型2
  treeView.setModel(&model2);

  // 切换回模型1后,之前的更改不会保留
  treeView.setModel(&model1);

  return app.exec();
}