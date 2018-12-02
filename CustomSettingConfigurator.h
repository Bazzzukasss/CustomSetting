#ifndef CUSTOMSETTINGSCONFIGURATOR_H
#define CUSTOMSETTINGSCONFIGURATOR_H

#include "CustomSettingClasses.h"
#include <QString>

class ICustomSettingsConfigurator
{
public:
    virtual bool load(CustomSetting* apSetting, const QString& filename) = 0;
    virtual bool save(CustomSetting* apSetting, const QString& filename) = 0;
};

class CustomSettingsConfiguratorXML
{
public:
    bool load(CustomSetting* apSetting, const QString& filename);
    bool save(CustomSetting* apSetting, const QString& filename);
};

#endif // CUSTOMSETTINGSCONFIGURATOR_H
