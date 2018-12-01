#ifndef CUSTOMSETTINGDATA_H
#define CUSTOMSETTINGDATA_H

#include <QXmlStreamAttributes>

class ICustomSettingXML
{
public:
    virtual QXmlStreamAttributes toXMLAttributes() const = 0;
    virtual void fromXMLAttributes(const QXmlStreamAttributes& aAttributes) = 0;

protected:
    void fromString(const QStringRef& aStringValue, int& value){ value = aStringValue.toInt(); }
    void fromString(const QStringRef& aStringValue, double& value){ value = aStringValue.toDouble(); }
    void fromString(const QStringRef& aStringValue, bool& value){ value = aStringValue.toInt(); }
    void fromString(const QStringRef& aStringValue, QString& value){ value = aStringValue.toString(); }

    QString toString(int aValue) const { return QString::number(aValue); }
    QString toString(double aValue) const { return QString::number(aValue); }
    QString toString(bool aValue) const { return QString::number(aValue); }
};


class CustomSetingHeader : public ICustomSettingXML
{
public:
    CustomSetingHeader(const QString& aId, const QString& aCaption, const QString& aDescription)
        :mId(aId),mCaption(aCaption),mDescription(aDescription)
    {}

    CustomSetingHeader(const QXmlStreamAttributes& aAttributes){
        fromXMLAttributes(aAttributes);
    }

    void setCaption(const QString& aCaption)            { mCaption = aCaption; }
    void setDescription(const QString& aDescription)    { mDescription = aDescription; }
    void setId(const QString& aId)                      { mId = aId; }

    QString getCaption() const                          { return mCaption; }
    QString getDescription() const                      { return mDescription; }
    QString getId() const                               { return mId; }

    QXmlStreamAttributes toXMLAttributes() const override{
        QXmlStreamAttributes attributes;
        attributes.append( {"id",           mId});
        attributes.append( {"caption",      mCaption});
        attributes.append( {"descriptiont", mDescription});

        return attributes;
    }

    void fromXMLAttributes(const QXmlStreamAttributes& aAttributes) override{
        if(aAttributes.hasAttribute("id"))          fromString(aAttributes.value("id"),mId);
        if(aAttributes.hasAttribute("caption"))     fromString(aAttributes.value("caption"),mCaption);
        if(aAttributes.hasAttribute("description")) fromString(aAttributes.value("description"),mDescription);
    }

private:
    QString mId;
    QString mCaption;
    QString mDescription;
};


template<typename T>
class CustomSettingData : public ICustomSettingXML
{
public:
    CustomSettingData(const T& aValue,const T& aDefaultValue,const T& aResetValue)
        :mValue(aValue),mDefaultValue(aDefaultValue),mResetValue(aResetValue)
    {}
    CustomSettingData(const T& aValue,const T& aDefaultValue)
        :mValue(aValue),mDefaultValue(aDefaultValue),mResetValue(aValue)
    {}
    CustomSettingData(const T& aValue)
        :mValue(aValue),mDefaultValue(aValue),mResetValue(aValue)
    {}
    CustomSettingData(const QXmlStreamAttributes& aAttributes){
        fromXMLAttributes(aAttributes);
    }

    void setValue(const T& value)       { mValue = value; }
    void setDefaultValue(const T& value){ mDefaultValue = value; }
    void setResetValue(const T& value)  { mResetValue = value; }

    const T& getValue() const           { return mValue; }
    const T& getDefaultValue() const    { return mDefaultValue; }
    const T& getResetValue() const      { return mResetValue; }

    void setToDefault()                 { mValue = mDefaultValue; }
    void resetValue()                   { mValue = mResetValue; }

    QXmlStreamAttributes toXMLAttributes() const override{
        QXmlStreamAttributes attributes;
        attributes.append( {"value",   toString(mValue)});
        attributes.append( {"default", toString(mDefaultValue)});
        attributes.append( {"reset",   toString(mResetValue)});
        return attributes;
    }

    void fromXMLAttributes(const QXmlStreamAttributes& aAttributes) override{
        if(aAttributes.hasAttribute("value"))   fromString( aAttributes.value("value"), mValue);
        if(aAttributes.hasAttribute("default")) fromString( aAttributes.value("default"), mDefaultValue);
        if(aAttributes.hasAttribute("reset"))   fromString( aAttributes.value("reset"), mResetValue );
    }

protected:
    T mValue;
    T mDefaultValue;
    T mResetValue;
};



/*
#include <limits>
#include <QStringList>
#include <QVector>
#include <QMetaType>

template<typename T>
class SIDigits     : public CustomItemType<T>{
public:
    SIDigits(const T& value = 0,const T& min= std::numeric_limits<T>::min(),const T& max = std::numeric_limits<T>::max(),const T& defaultValue = 0,const T& resetValue = 0)
        :CustomItemType<T>(value,defaultValue,resetValue),mMin(min),mMax(max)
    {}
    T getMaximum(){return mMax;}
    T getMinimum(){return mMin;}
protected:
    T mMin;
    T mMax;
};

class SIStringList : public SIDigits<int> {
public:
    SIStringList(const QStringList& list = QStringList(),int index = 0,int defaultIndex = 0, int resetIndex = 0)
        :SIDigits<int>(index,0,list.size(),defaultIndex,resetIndex),mList(list)
    {}
    QStringList getList(){return mList;}
    virtual QString getText() {
        return mList[mValue];
    }
protected:
    QStringList mList;
};

class SIBooleanList : public SIStringList
{
public:
    SIBooleanList(const QString& falseString = "false", const QString& trueString = "true", int index = 0, int defaultIndex = 0, int resetIndex = 0)
        :SIStringList(QStringList(), index,defaultIndex,resetIndex)
    {
        mList << falseString << trueString;
    }
    virtual QString getText() {
        if (mValue == 1)
            return "true";
        else
            return "false";
    }
};
class SIInteger      : public SIDigits<int>{
public:
    SIInteger(int value = 0,int min = std::numeric_limits<int>::min(),int max = std::numeric_limits<int>::max(),int defaultValue = std::numeric_limits<int>::min(), int resetValue = std::numeric_limits<int>::min(), const QString& aSuffix = "")
        :SIDigits<int>(value,min,max,defaultValue,resetValue),mSuffix(aSuffix)
    {}
    QString getSuffix() { return mSuffix; }
private:
    QString mSuffix;
};

class SIDouble      : public SIDigits<double>{
public:
    SIDouble(double value = 0,double min = -std::numeric_limits<double>::max(),double max = std::numeric_limits<double>::max(),double defaultValue = std::numeric_limits<double>::min(), double resetValue = std::numeric_limits<double>::min(),int aPrecision = 4,const QString& aSuffix = "")
        :SIDigits<double>(value,min,max,defaultValue,resetValue),mPrecision(aPrecision),mSuffix(aSuffix)
    {}
    int getPrecision() { return mPrecision; }
    QString getSuffix() { return mSuffix; }
private:
    int mPrecision;
    QString mSuffix;
};

class SIProgress    : public SIDigits<int>{
public:
    SIProgress(int value = 0,int min= std::numeric_limits<int>::min(),int max = std::numeric_limits<int>::max(),const QString& format="%p%")
        :SIDigits<int>(value,min,max),mFormat(format)
    {}
    void setFormat(const QString& format) { mFormat = format; }
    QString getFormat() { return mFormat; }
private:
    QString mFormat;
};

class SILcd         : public CustomItemType<double>{
public:
    enum mode{HEX,DEC,OCT,BIN};
    SILcd(double value = 0,int mode = DEC)
        :CustomItemType<double>(value),mDisplayMode(mode)
    {}
    int getDisplayMode(){return mDisplayMode;}
private:
    int mDisplayMode;
};

class SIImage       : public CustomItemType<QString>{
public:
    SIImage(const QString& value = ""):CustomItemType<QString>(value){}
};

class SIString      : public CustomItemType<QString>{
public:
    SIString(const QString& value = "",const QString& defaultValue = "",const QString& resetValue = "")
        :CustomItemType<QString>(value,defaultValue,resetValue)
    {}
};

class SIText      : public CustomItemType<QString>{
public:
    SIText(const QString& value = "",const QString& defaultValue = "",const QString& resetValue = "")
        :CustomItemType<QString>(value,defaultValue,resetValue)
    {}
};

class SIPlot        : public CustomItemType<QVector<double>>{
public:
    SIPlot(const QVector<double>& value = QVector<double>()):CustomItemType<QVector<double>>(value){}
};

class SIBars        : public SIPlot{
public:
    SIBars(const QVector<double>& value = QVector<double>()):SIPlot(value){}
};

class SIGraph        : public SIPlot{
public:
    SIGraph(const QVector<double>& value = QVector<double>()):SIPlot(value){}
};

class SIBoolean      : public CustomItemType<bool>{
public:
    SIBoolean(bool value = false, bool defaultValue = false, bool resetValue = false)
        :CustomItemType<bool>(value,defaultValue,resetValue)
    {}
};

Q_DECLARE_METATYPE(SIBoolean);
Q_DECLARE_METATYPE(SIInteger);
Q_DECLARE_METATYPE(SIDouble);
Q_DECLARE_METATYPE(SILcd);
Q_DECLARE_METATYPE(SIProgress);
Q_DECLARE_METATYPE(SIString);
Q_DECLARE_METATYPE(SIText);
Q_DECLARE_METATYPE(SIBars);
Q_DECLARE_METATYPE(SIGraph);
Q_DECLARE_METATYPE(SIImage);
Q_DECLARE_METATYPE(SIStringList);
Q_DECLARE_METATYPE(SIBooleanList);

*/
#endif // CUSTOMSETTINGDATA_H
