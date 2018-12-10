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

    //std::cout << root << std::endl;
    //configurator.save("test.xml",&root);

    configurator.load("test.xml",&root);
    std::cout << root << std::endl;

    return a.exec();
}
