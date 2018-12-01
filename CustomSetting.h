#ifndef CUSTOMSETTING_H
#define CUSTOMSETTING_H

#include "CustomSettingData.h"

class ICustomSetting{
public:
    ICustomSetting(){}
    //int getType() or dynamic_cast to CustomSettingExt<T>
    //auto data = CustomSettingExt<T>.getData()
    //data.getValue(T val); or data.setValue(T val);

    virtual const QString& getTag() const = 0;
    virtual QXmlStreamAttributes getXMLAttributes() const = 0;
    virtual const QString getValue() const { return ""; }
};

class CustomSetting : public ICustomSetting
{
public:
    CustomSetting(const QString& aTag, const CustomSetingHeader& aHeader)
        :mTag(aTag),mHeader(aHeader)
    {}

    const QString& getTag() const override                  { return mTag; }
    QXmlStreamAttributes getXMLAttributes() const override  { mHeader.toXMLAttributes(); }

protected:
    void addSetting(CustomSetting* aSetting)                { mSettings.append(aSetting); }

private:
    QString mTag;
    CustomSetingHeader mHeader;
    QVector<ICustomSetting*> mSettings;
};


template <typename T>
class CustomSettingExt : public CustomSetting
{
public:
    CustomSettingExt(const QString& aTag, const CustomSetingHeader& aHeader, const CustomSettingData<T>& aData)
        :CustomSetting(aTag,aHeader),mData(aData)
    {}

    void setData(const CustomSettingData<T>& aData) { mData = aData; }
    CustomSettingData<T>& getData()                 { return mData; }

    const QString getValue() const override         { mData.getStringValue(); }

    QXmlStreamAttributes getXMLAttributes() const override{
        auto attributes = mHeader.toXMLAttributes();
        for(auto& attr : mData.toXMLAttributes())
            attributes.append( attr.name(), attr.value() );

        return attributes;
    }

private:
    CustomSettingData<T> mData;
};

#endif // CUSTOMSETTING_H
