#ifndef DEVICE_H
#define DEVICE_H
#include <QJsonDocument>
#include <QJsonObject>

class Device{
public:
    QString type;
    int status;

    QJsonObject toJsonObject() const {
        QJsonObject obj;
        obj["type"] = type;
        obj["status"] = status;
        return obj;
    }
};

#endif // DEVICE_H
