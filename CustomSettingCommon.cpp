#include "CustomSettingCommon.h"

void fromString(const QString& aStringValue, int& aValue)       { aValue = aStringValue.toInt(); }
void fromString(const QString& aStringValue, double& aValue)    { aValue = aStringValue.toDouble(); }
void fromString(const QString& aStringValue, bool& aValue)      { aValue = aStringValue.toInt(); }
void fromString(const QString& aStringValue, QString& aValue)   { aValue = aStringValue; }

QString toString(int aValue)    { return QString::number(aValue); }
QString toString(double aValue) { return QString::number(aValue); }
QString toString(bool aValue)   { return QString::number(aValue); }

QString toString(const QXmlStreamAttributes &aAttributes)
{
    QString str;
    for(auto& attr : aAttributes)
        str = QString("%1 %2=\"%3\"").arg(str).arg(attr.name().toString()).arg(attr.value().toString());
    return str;
}
