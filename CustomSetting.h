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
    virtual QString getStringValue() const                  { return ""; }
    virtual void setStringValue(const QString&)             {}

    virtual void setXMLAttributes(const QXmlStreamAttributes& aAttributes){}

    void addSetting(CustomSetting* aSetting)                { mSettings.append(aSetting); }
    void addSettings(QVector<CustomSetting*> aSettings)     { mSettings.append(aSettings); }
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

    QString getTag() const override                                         { return mTag; }
    QXmlStreamAttributes getXMLAttributes() const override                  { return mHeader.toXMLAttributes(); }
    void setXMLAttributes(const QXmlStreamAttributes& aAttributes) override { mHeader.fromXMLAttributes(aAttributes); }

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

    QString getStringValue() const override             { return mData.getStringValue(); }
    void setStringValue(const QString& aValue)          { mData.setStringValue(aValue); }

    const T& getValue() const                           { return mData.getValue(); }
    void setValue(T aValue)                             { mData.setValue(aValue); }

    QXmlStreamAttributes getXMLAttributes() const override{
        auto attributes = mHeader.toXMLAttributes();
        for(auto& attr : mData.toXMLAttributes())
            attributes.append( attr );

        return attributes;
    }

    void setXMLAttributes(const QXmlStreamAttributes& aAttributes) override {
        mHeader.fromXMLAttributes(aAttributes);
        mData.fromXMLAttributes(aAttributes);
    }
private:
    CustomDataExt<T> mData;
};

#endif // CUSTOMSETTING_H
