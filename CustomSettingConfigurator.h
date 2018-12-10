#ifndef CUSTOMSETTINGSCONFIGURATOR_H
#define CUSTOMSETTINGSCONFIGURATOR_H

#include "CustomSettingClasses.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QString>
#include <QDomDocument>

class ICustomSettingsConfigurator
{
public:
    virtual bool load(const QString& filename, CustomSetting* apSetting) = 0;
    virtual bool save(const QString& filename, CustomSetting* apSetting) = 0;
};

class CustomSettingsConfiguratorXML : public ICustomSettingsConfigurator
{
public:
    bool load(const QString& filename, CustomSetting* apSetting) override;
    bool save(const QString& filename, CustomSetting* apSetting) override;

private:
    bool load(const QDomNode &aNode, CustomSetting* apSetting);
    bool save(QXmlStreamWriter& writer, CustomSetting *apSetting);
    QXmlStreamAttributes toXMLAttributes(const QDomNamedNodeMap& aMap);
};

#endif // CUSTOMSETTINGSCONFIGURATOR_H
