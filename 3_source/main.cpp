
// #include <QtCore/QString>

// QString numericToString(double n, int prec, bool suppressZero) {
//     QString result = QString::number(n, 'f', -prec); // 使用四舍五入模式
//     if (suppressZero) {
//         while (result.endsWith('0')) {
//             result.chop(1);
//         }
//         if (result.endsWith('.')) {
//             result.chop(1);
//         }
//     }
//     return result;
// }

// int main() {
//     double value = 10.500;
//     bool suppress = true;

//     QString result = suppressTrailZero(value, suppress);
//     qDebug() << result;

//     return 0;
// }

#include <QString>
#include <QDebug>
#include <cmath>

int main() {
    double inputValue = 100.005;
    std::cout << inputValue << std::endl;
    // 将数值四舍五入到两位小数
    double roundedValue = round(inputValue * 100) / 100;
    std::cout << roundedValue << std::endl;
    return 0;
}