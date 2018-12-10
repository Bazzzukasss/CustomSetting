#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include "CustomSetting.h"

struct ParamInt : CustomSettingExt<int>
{
    ParamInt() : CustomSettingExt<int>("paramInt", {"idVal","capVal","desVal"}, {1,2,3})
    {}
};
struct ParamDouble : CustomSettingExt<double>
{
    ParamDouble() : CustomSettingExt<double>("paramDouble",  {"idVal","capVal","desVal"}, {1.1,2.2,3.3})
    {}
};
struct ParamBool : CustomSettingExt<bool>
{
    ParamBool() : CustomSettingExt<bool>("paramBool",      {"idVal","capVal","desVal"}, {true,false,true})
    {}
};


struct MainSettings : CustomSettingSimple
{
    MainSettings() : CustomSettingSimple("mainSettings",{"idValue","captionValue","descriptionValue"}){
        addSettings({&mParamInt,&mParamDouble,&mParamBool});
    }
    ParamInt mParamInt;
    ParamDouble mParamDouble;
    ParamBool mParamBool;
};

struct UserSettings : CustomSettingSimple
{
    UserSettings() : CustomSettingSimple("root",{"rootId","rootCaption","rootDescription"}){
        addSetting(&mMainSettings);
    }

    MainSettings mMainSettings;
};

#endif // USERSETTINGS_H
