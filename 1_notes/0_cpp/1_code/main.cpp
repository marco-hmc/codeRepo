#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushbutton>

class CustomWidget : public QFrame {
    // B: set styleSheet
    explicit CustomWidget(QWidget* parent = nullptr) {
        setObjectName("customObjectName");
        QPushButton* button = new QPushButton(tr("Button"), this);
        button->setObjectName("abc");
    }

public:
    QLabel* label1;
    QLabel* label2;
};

int main() {
    return 0;
}
