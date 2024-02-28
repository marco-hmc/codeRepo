#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

int main() {
    // 解析JSON数据
    QString jsonString = "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            QString name = jsonObj["name"].toString();
            int age = jsonObj["age"].toInt();
            QString city = jsonObj["city"].toString();

            // 打印解析结果
            qDebug() << "Name: " << name;
            qDebug() << "Age: " << age;
            qDebug() << "City: " << city;
        }
    }

    // 生成JSON数据
    QJsonObject jsonObj;
    jsonObj["name"] = "John";
    jsonObj["age"] = 30;
    jsonObj["city"] = "New York";

    QJsonDocument jsonDoc2(jsonObj);
    QString jsonString2 = jsonDoc2.toJson();

    // 打印生成的JSON数据
    qDebug() << "Generated JSON: " << jsonString2;

    return 0;
}