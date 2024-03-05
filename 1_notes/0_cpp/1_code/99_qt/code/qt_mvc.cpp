// Model
class Model : public QObject {
  Q_OBJECT
public:
  explicit Model(QObject *parent = nullptr) : QObject(parent) {}

  QString getData() const { return m_data; }

  void setData(const QString &data) {
    if (m_data != data) {
      m_data = data;
      emit dataChanged();
    }
  }

signals:
  void dataChanged();

private:
  QString m_data;
};

// View
class View : public QWidget {
  Q_OBJECT
public:
  explicit View(QWidget *parent = nullptr) : QWidget(parent) {
    m_label = new QLabel(this);
    m_button = new QPushButton("Update", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_label);
    layout->addWidget(m_button);

    connect(m_button, &QPushButton::clicked, this, &View::updateClicked);
  }

  void updateData(const QString &data) { m_label->setText(data); }

signals:
  void updateClicked();

private:
  QLabel *m_label;
  QPushButton *m_button;
};

// Controller
class Controller : public QObject {
  Q_OBJECT
public:
  explicit Controller(Model *model, View *view, QObject *parent = nullptr)
      : QObject(parent) {
    m_model = model;
    m_view = view;

    connect(m_view, &View::updateClicked, this, &Controller::updateData);
    connect(m_model, &Model::dataChanged, m_view,
            [this]() { m_view->updateData(m_model->getData()); });
  }

  void updateData() {
    QString newData = "New Data";
    m_model->setData(newData);
  }

private:
  Model *m_model;
  View *m_view;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Model model;
  View view;
  Controller controller(&model, &view);

  view.show();

  return a.exec();
}