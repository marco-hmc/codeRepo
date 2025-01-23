#include <QApplication>
#include <QFileSystemModel>
#include <QFont>
#include <QFontDatabase>
#include <QTextCodec>
#include <QTextStream>
#include <QTreeView>

// 函数：检查并替换不可显示的字符
QString replaceUnprintableCharacters(const QString &text) {
    QString result;
    for (QChar ch : text) {
        if (ch.isPrint()) {
            result.append(ch);
        } else {
            result.append(' ');  // 替换为空白字符
        }
        //        result.append(ch);
    }
    return result;
}

class CustomFileSystemModel : public QFileSystemModel {
  public:
    CustomFileSystemModel(QObject *parent = nullptr)
        : QFileSystemModel(parent) {}

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override {
        QVariant value = QFileSystemModel::data(index, role);
        if (role == Qt::DisplayRole && value.type() == QVariant::String) {
            QString text = value.toString();
            QString replacedText = replaceUnprintableCharacters(text);
            return replacedText;
        }
        return value;
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 设置应用程序的编码格式为系统的本地编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    // 设置默认字体
    QFont defaultFont = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
    app.setFont(defaultFont);

    // 创建一个 CustomFileSystemModel 实例
    CustomFileSystemModel *model = new CustomFileSystemModel;
    // 设置根路径，开始加载文件系统信息
    QModelIndex rootIndex =
        model->setRootPath("C:/Users/Administrator/Downloads/ZW3D-41902");

    // 创建一个 QTreeView 实例
    QTreeView *treeView = new QTreeView;
    // 将 CustomFileSystemModel 与 QTreeView 关联
    treeView->setModel(model);
    // 设置显示的根目录，可以是任意路径，这里设置为根目录
    treeView->setRootIndex(rootIndex);

    // 显示窗口
    treeView->show();

    return app.exec();
}
