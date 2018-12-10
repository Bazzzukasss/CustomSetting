#include "CustomSettingConfigurator.h"
#include <QFile>
#include "CustomSetting.h"
#include <QDebug>

bool CustomSettingsConfiguratorXML::load(const QString &filename, CustomSetting *apSetting)
{
    if(!apSetting)
        return false;

    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
       return false;

    load(doc.documentElement(),apSetting);
    return true;
}

bool CustomSettingsConfiguratorXML::save(const QString &filename, CustomSetting *apSetting)
{
    if(!apSetting)
        return false;

    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QXmlStreamWriter writer(&file);

        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        save(writer,apSetting);
        writer.writeEndDocument();

        if (writer.hasError())
            return false;

        return true;
    }
    return false;
}

bool CustomSettingsConfiguratorXML::load(const QDomNode& aNode, CustomSetting *apSetting)
{
    if(aNode.isNull())
        return false;

    QDomElement element = aNode.toElement();
    if(element.isNull())
        return false;

    //std::cout << apSetting->getTag().toStdString() << std::endl;
    if(apSetting->getTag() == element.tagName())
    {
        QXmlStreamAttributes attributes = toXMLAttributes(aNode.attributes());
        QString value = aNode.toElement().text();
        //std::cout << toString( attributes ).toStdString() << value.toStdString() << std::endl;

        apSetting->setXMLAttributes(attributes);
        apSetting->setStringValue(value);

        QDomNode node = element.firstChild();
        for(auto& pSetting : apSetting->getSettings())
        {
            if(load(node,pSetting))
                node = node.nextSibling();
        }
        return true;
    }

    return false;
}

bool CustomSettingsConfiguratorXML::save(QXmlStreamWriter &writer, CustomSetting *apSetting)
{
    writer.writeStartElement(apSetting->getTag());
    writer.writeAttributes(apSetting->getXMLAttributes());
    if(!apSetting->getStringValue().isEmpty())
        writer.writeCharacters(apSetting->getStringValue());

    for (auto& pSetting : apSetting->getSettings())
        save(writer,pSetting);

    writer.writeEndElement();

    return true;
}

QXmlStreamAttributes CustomSettingsConfiguratorXML::toXMLAttributes(const QDomNamedNodeMap &aMap)
{
    QXmlStreamAttributes attributes;

    for (int i = 0; i < aMap.length(); ++i)
    {
        auto attr = aMap.item(i).toAttr();
        attributes.append(attr.name(), attr.value());
    }
    return attributes;
}
