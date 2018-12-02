#ifndef CUSTOMSETTING_H
#define CUSTOMSETTING_H

#include "CustomSettingData.h"
#include <iostream>

class ICustomSetting{
public:
    ICustomSetting(){}
    //int getType() or dynamic_cast to CustomSettingExt<T>
    //auto data = CustomSettingExt<T>.getData()
    //data.getValue(T val); or data.setValue(T val);

    virtual const QString& getTag() const = 0;
    virtual QXmlStreamAttributes getXMLAttributes() const = 0;
    virtual const QString getValue() const { return ""; }

    friend std::ostream& operator<<(std::ostream& s, const ICustomSetting& aSetting);

    void addSetting(ICustomSetting* aSetting) { mSettings.append(aSetting); }
protected:

    QVector<ICustomSetting*> mSettings;
};

class CustomSetting : public ICustomSetting
{
public:
    CustomSetting(const QString& aTag, const CustomSetingHeader& aHeader)
        :mTag(aTag),mHeader(aHeader)
    {}

    const QString& getTag() const override                  { return mTag; }
    QXmlStreamAttributes getXMLAttributes() const override  { return mHeader.toXMLAttributes(); }

protected:
    CustomSetingHeader mHeader;

private:
    QString mTag;
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

    const QString getValue() const override         { return mData.getStringValue(); }

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
