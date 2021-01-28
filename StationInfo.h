#ifndef _STATION_INFO_H_
#define _STATION_INFO_H_

#include <QJsonObject>
#include <QVector>

class StationInfo
{
public:
    StationInfo() = default;
    StationInfo(const QString& name);

    QString GetName() const;

    QString GetIP() const;
    void SetIP(const QString& npcs);

    void Read(const QJsonObject& json);
    void Write(QJsonObject& json) const;

private:
    QString Name;
    QString IP;
};

#endif