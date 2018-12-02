#include <QCoreApplication>
#include <QDebug>

#include "CustomSettingData.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CustomSettingData<int> dataInt(1,2,3);
    QXmlStreamAttributes attributes;
    attributes.append( {"default", QString::number(20.2)});
    attributes.append( {"reset",   QString::number(30.3)});

    dataInt.fromXMLAttributes(attributes);


    CustomSettingData<double> dataDouble(10.1,attributes);
    CustomSetingHeader header("idValue","captionValue","descriptionValue");

    qDebug()<< toString(dataDouble.toXMLAttributes()) << dataDouble.getStringValue();

    return a.exec();
}
