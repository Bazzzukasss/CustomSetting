#include <QCoreApplication>
#include <QDebug>

#include "CustomSetting.h"
#include "CustomSettingConfigurator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CustomSettingsConfiguratorXML configurator;

    CustomSettingSimple root("",{"","",""});

    CustomSettingSimple main("root",{"idValue","captionValue","descriptionValue"});
        CustomSettingExt<int>       ParamInt("paramInt",        {"idVal","capVal","desVal"}, {1,2,3});
        CustomSettingExt<double>    ParamDouble("paramDouble",  {"idVal","capVal","desVal"}, {1.1,2.2,3.3});
        CustomSettingExt<bool>      ParamBool("paramBool",      {"idVal","capVal","desVal"}, {true,false,true});

    main.addSetting(&ParamInt);
    main.addSetting(&ParamDouble);
    main.addSetting(&ParamBool);

    root.addSetting(&main);
    std::cout << root;

    configurator.save("test.xml",&root);
    return a.exec();
}
