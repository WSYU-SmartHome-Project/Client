#ifndef REST_H
#define REST_H
#include <QJsonDocument>
#include <QJsonObject>

class Rest{
public:
    QString message;
    int command;
    bool success;
    int type = 0;

    QJsonObject toJsonObject() const {
        QJsonObject obj;
        obj["message"] = message;
        obj["command"] = command;
        obj["success"] = success;
        obj["type"] = type;
        return obj;
    }

    //将对象转为Json
    QString toJson() const {
        QJsonObject obj;
        obj["message"] = message;
        obj["command"] = command;
        obj["success"] = success;
        obj["type"] = type;
        QJsonDocument doc(obj);
        QString jsonStr(doc.toJson(QJsonDocument::Compact));
        return jsonStr;
    }


};


#endif // REST_H

