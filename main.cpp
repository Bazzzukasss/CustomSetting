#include <QCoreApplication>
#include <QDebug>

#include "CustomSettingData.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CustomSettingData<int> data(1,2,3);
    QXmlStreamAttributes attributes;


    attributes.append( {"value",   QString::number(10.1)});
    attributes.append( {"default", QString::number(20.2)});
    attributes.append( {"reset",   QString::number(30.3)});

    data.setXMLAttributes(attributes);
    qDebug() << data.getValueAsString();

    CustomSettingData<double> dataAttr(attributes);
    qDebug() << dataAttr.getValueAsString();

    return a.exec();
}
