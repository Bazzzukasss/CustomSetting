#include <QCoreApplication>
#include <QDebug>

#include "CustomSetting.h"
#include "CustomSettingConfigurator.h"
#include "UserSettings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CustomSettingsConfiguratorXML configurator;
    UserSettings root;

    std::cout << root;
    configurator.save("test.xml",&root);

    return a.exec();
}
