#ifndef CUSTOMSETTINGCOMMON_H
#define CUSTOMSETTINGCOMMON_H

#include <QString>
#include <QXmlStreamAttributes>

extern void fromString(const QString& aStringValue, QVector<double>& aValue);
extern void fromString(const QString& aStringValue, int& aValue);
extern void fromString(const QString& aStringValue, double& aValue);
extern void fromString(const QString& aStringValue, bool& aValue);
extern void fromString(const QString& aStringValue, QString& aValue);

extern QString toString(const QString& aValue);
extern QString toString(const QVector<double> &aValue);
extern QString toString(int aValue);
extern QString toString(double aValue);
extern QString toString(bool aValue);
extern QString toString(const QXmlStreamAttributes& aAttributes);



#endif // CUSTOMSETTINGCOMMON_H
