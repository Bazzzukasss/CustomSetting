#ifndef CUSTOMSETTING_H
#define CUSTOMSETTING_H

#include "CustomSettingData.h"
#include <iostream>

class CustomSetting{
public:
    CustomSetting(){}
    //int getType() or dynamic_cast to CustomSettingExt<T>
    //auto data = CustomSettingExt<T>.getData()
    //data.getValue(T val); or data.setValue(T val);

    virtual QString getTag() const                          { return ""; }
    virtual QXmlStreamAttributes getXMLAttributes() const   { return QXmlStreamAttributes(); }
    virtual QString getValue() const                        { return ""; }

    friend std::ostream& operator<<(std::ostream& s, const CustomSetting& aSetting);

    void addSetting(CustomSetting* aSetting) { mSettings.append(aSetting); }
protected:

    QVector<CustomSetting*> mSettings;
};

class CustomSettingSimple : public CustomSetting
{
public:
    CustomSettingSimple(const QString& aTag, const CustomSetingHeader& aHeader)
        :mTag(aTag),mHeader(aHeader)
    {}

    QString getTag() const override                  { return mTag; }
    QXmlStreamAttributes getXMLAttributes() const override  { return mHeader.toXMLAttributes(); }

protected:
    CustomSetingHeader mHeader;

private:
    QString mTag;
};


template <typename T>
class CustomSettingExt : public CustomSettingSimple
{
public:
    CustomSettingExt(const QString& aTag, const CustomSetingHeader& aHeader, const CustomSettingData<T>& aData)
        :CustomSettingSimple(aTag,aHeader),mData(aData)
    {}

    void setData(const CustomSettingData<T>& aData) { mData = aData; }
    CustomSettingData<T>& getData()                 { return mData; }

    QString getValue() const override               { return mData.getStringValue(); }

    QXmlStreamAttributes getXMLAttributes() const override{
        auto attributes = mHeader.toXMLAttributes();
        for(auto& attr : mData.toXMLAttributes())
            attributes.append( attr );

        return attributes;
    }

private:
    CustomSettingData<T> mData;
};

#endif // CUSTOMSETTING_H
