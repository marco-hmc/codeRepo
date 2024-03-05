#include <QApplication>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QTableView>


int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // 创建一个表格视图
  QTableView tableView;

  // 创建一个标准项模型
  QStandardItemModel model(4, 4);
  model.setHorizontalHeaderLabels(
      {"Column 1", "Column 2", "Column 3", "Column 4"});

  // 将模型设置给表格视图
  tableView.setModel(&model);

  // 获取选择模型
  QItemSelectionModel *selectionModel = tableView.selectionModel();

  // 设置选择模式为单选
  selectionModel->setSelectionMode(QItemSelectionModel::SingleSelection);

  // 连接选择变化的信号槽
  QObject::connect(
      selectionModel, &QItemSelectionModel::selectionChanged,
      [](const QItemSelection &selected, const QItemSelection &deselected) {
        // 处理选择变化的逻辑
        qDebug() << "Selection changed";
      });

  // 显示表格视图
  tableView.show();

  return app.exec();
}