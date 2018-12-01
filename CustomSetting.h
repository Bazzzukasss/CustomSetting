#ifndef CUSTOMSETTING_H
#define CUSTOMSETTING_H

#include "CustomSettingData.h"

class CustomSetting
{
public:
    CustomSetting(const QString& aTag, const CustomSetingHeader& aHeader)
        :mTag(aTag),mHeader(aHeader)
    {}
    void addSetting(CustomSetting* aSetting)            { mSettings.append(aSetting); }

    void setTag(const QString& aTag)                    { mTag = aTag; }
    QString getTag() const                              { return mTag; }

    void setHeader(const CustomSetingHeader& aHeader)   { mHeader = aHeader; }
    const CustomSetingHeader& getHeader() const         { return  mHeader; }



private:
    QString mTag;
    CustomSetingHeader mHeader;
    QVector<CustomSetting*> mSettings;
};


template <typename T>
class CustomSettingExt : public CustomSetting
{
public:
    CustomSettingExt(const QString& aTag, const CustomSetingHeader& aHeader, const CustomSettingData<T>& aData)
        :CustomSetting(aTag,aHeader),mData(aData)
    {}

    void setData(const CustomSettingData<T>& aData) { mData = aData; }
    const CustomSettingData<T>& getData() const     { return mData; }

private:
    CustomSettingData<T> mData;
};

#endif // CUSTOMSETTING_H
