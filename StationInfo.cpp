#include "StationInfo.h"

#include <QJsonArray>
#include <QTextStream>

StationInfo::StationInfo(const QString& name): Name(name)
{
}

QString StationInfo::GetName() const
{
    return Name;
}

QString StationInfo::GetIP() const
{
    return IP;
}

void StationInfo::SetIP(const QString& IP)
{
    this->IP = IP;
}

void StationInfo::Read(const QJsonObject& json)
{
    if (json.contains("name") && json["name"].isString())
        Name = json["name"].toString();

    if (json.contains("IP") && json["IP"].isString())
        IP = json["IP"].toString();
}

void StationInfo::Write(QJsonObject& json) const
{
    json["name"] = Name;
    json["IP"] = IP;
}
