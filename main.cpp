#include <QCoreApplication>
#include <QDebug>

#include "CustomSetting.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CustomSetting root("root",CustomSetingHeader("idValue","captionValue","descriptionValue"));
        CustomSettingExt<int> ParamInt("paramInt",CustomSetingHeader("idVal","capVal","desVal"),CustomSettingData<int>(1,2,3));
        CustomSettingExt<double> ParamDouble("paramDouble",CustomSetingHeader("idVal","capVal","desVal"),CustomSettingData<double>(1.1,2.2,3.3));
        CustomSettingExt<bool> ParamBool("paramBool",CustomSetingHeader("idVal","capVal","desVal"),CustomSettingData<bool>(true,false,true));

    root.addSetting(&ParamInt);
    root.addSetting(&ParamDouble);
    root.addSetting(&ParamBool);

    std::cout << root;
    return a.exec();
}
