#ifndef CUSTOMSETTING_H
#define CUSTOMSETTING_H

#include "CustomData.h"
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

    void addSetting(CustomSetting* aSetting)                { mSettings.append(aSetting); }
    QVector<CustomSetting*>& getSettings()                  {return mSettings; }

    friend std::ostream& operator<<(std::ostream& s, const CustomSetting& aSetting);
protected:
    QVector<CustomSetting*> mSettings;
};

class CustomSettingSimple : public CustomSetting
{
public:
    CustomSettingSimple(const QString& aTag, const CustomHeader& aHeader)
        :mHeader(aHeader),mTag(aTag)
    {}

    QString getTag() const override                         { return mTag; }
    QXmlStreamAttributes getXMLAttributes() const override  { return mHeader.toXMLAttributes(); }

protected:
    CustomHeader mHeader;

private:
    QString mTag;
};


template <typename T>
class CustomSettingExt : public CustomSettingSimple
{
public:
    CustomSettingExt(const QString& aTag, const CustomHeader& aHeader, const CustomDataExt<T>& aData)
        :CustomSettingSimple(aTag,aHeader),mData(aData)
    {}

    void setData(const CustomDataExt<T>& aData)         { mData = aData; }
    CustomDataExt<T>& getData()                         { return mData; }

    QString getValue() const override                   { return mData.getStringValue(); }

    QXmlStreamAttributes getXMLAttributes() const override{
        auto attributes = mHeader.toXMLAttributes();
        for(auto& attr : mData.toXMLAttributes())
            attributes.append( attr );

        return attributes;
    }

private:
    CustomDataExt<T> mData;
};

#endif // CUSTOMSETTING_H
