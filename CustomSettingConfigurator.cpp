#include "CustomSettingConfigurator.h"
#include <QFile>
#include "CustomSetting.h"

bool CustomSettingsConfiguratorXML::load(const QString &filename, CustomSetting *apSetting)
{
    if(!apSetting)
        return false;

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader reader(&file);
        reader.isStartDocument();
        load(reader,apSetting);

        if (reader.hasError())
            return false;

        return true;
    }
    return false;
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

bool CustomSettingsConfiguratorXML::load(QXmlStreamReader &reader, CustomSetting *apSetting)
{
    if(!apSetting)
        return false;

    return true;
}

bool CustomSettingsConfiguratorXML::save(QXmlStreamWriter &writer, CustomSetting *apSetting)
{
    if(!apSetting)
        return false;
    for (auto& pSetting : apSetting->getSettings())
    {
        writer.writeStartElement(pSetting->getTag());
        writer.writeAttributes(pSetting->getXMLAttributes());
        if(!pSetting->getValue().isEmpty())
            writer.writeCharacters(pSetting->getValue());
        save(writer,pSetting);
        writer.writeEndElement();
    }

    return true;
}
/*
bool XMLProcessor::load(QXmlStreamReader &reader, TreeItem *item)
{
    std::vector<XMLData> stack;
    XMLData data;
    TreeItem* currentItem=item;
    TreeItem* subItem;
    size_t stackSize = 0;

    while (!reader.atEnd())
    {
        reader.readNext();
        switch (reader.tokenType())
        {
            case QXmlStreamReader::StartElement:

                data.setAttributes(reader.attributes());
                data.setName(reader.name().toString());
                data.setValue(QString());

                subItem = new TreeItem(data.getData(),currentItem);
                currentItem->addItem( subItem );
                currentItem = subItem;

                if (stackSize < stack.size())
                    stack.resize(stackSize);

                stack.emplace_back(data);
                ++stackSize;

                break;
            case QXmlStreamReader::EndElement:
                if (stackSize == stack.size())
                    currentItem->setData(stack.back().getData());
                --stackSize;
                currentItem = currentItem->getParent();
                break;
            case QXmlStreamReader::Characters:
                stack.back().setValue(reader.text().toString());
                break;
            default:
                break;
        }
    }

    return true;
}

bool XMLProcessor::save(QXmlStreamWriter &writer, const TreeItem *item)
{
    for (TreeItem* subItem : item->getItems())
    {
        XMLData data(subItem->getData());
        writer.writeStartElement(data.getName());
        writer.writeAttributes(data.getAttributes());
        if(!data.getValue().isNull())
            writer.writeCharacters(data.getValue());
        save(writer,subItem);
        writer.writeEndElement();
    }

    return true;
}




*/

