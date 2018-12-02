#include <QCoreApplication>
#include <QDebug>

#include "CustomSetting.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CustomSetting root("root",{"idValue","captionValue","descriptionValue"});
        CustomSettingExt<int>       ParamInt("paramInt",        {"idVal","capVal","desVal"}, {1,2,3});
        CustomSettingExt<double>    ParamDouble("paramDouble",  {"idVal","capVal","desVal"}, {1.1,2.2,3.3});
        CustomSettingExt<bool>      ParamBool("paramBool",      {"idVal","capVal","desVal"}, {true,false,true});

    root.addSetting(&ParamInt);
    ParamInt.addSetting(&ParamDouble);
    root.addSetting(&ParamBool);

    std::cout << root;
    return a.exec();
}
