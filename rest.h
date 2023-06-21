#ifndef REST_H
#define REST_H
#include <QJsonDocument>
#include <QJsonObject>

class Rest{
public:
    QString message;
    int status;
    bool success;

    QJsonObject toJsonObject() const {
        QJsonObject obj;
        obj["message"] = message;
        obj["status"] = status;
        obj["success"] = success;
        return obj;
    }

    QString toJson() const {
        QJsonObject obj;
        obj["message"] = message;
        obj["status"] = status;
        obj["success"] = success;
        QJsonDocument doc(obj);
        QString jsonStr(doc.toJson(QJsonDocument::Compact));
        return jsonStr;
    }


};


#endif // REST_H

