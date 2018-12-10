#ifndef CUSTOMDATA_H
#define CUSTOMDATA_H

#include <limits>
#include <QStringList>
#include <QVector>
#include <QMetaType>


#include <QXmlStreamAttributes>
#include "CustomSettingCommon.h"

static const char* attrDefault = "default";
static const char* attrReset = "reset";
static const char* attrCaption = "caption";
static const char* attrDescription = "description";
static const char* attrId = "id";

class CustomData
{
public:
    virtual QXmlStreamAttributes toXMLAttributes() const                    { return QXmlStreamAttributes(); }
    virtual void fromXMLAttributes(const QXmlStreamAttributes&)             {}
    virtual QString getStringValue() const                                  {return "";}
    virtual void setStringValue(const QString&)                             {}
};


class CustomHeader : public CustomData
{
public:
    CustomHeader(const QString& aId, const QString& aCaption, const QString& aDescription)
        :mId(aId),mCaption(aCaption),mDescription(aDescription)
    {}

    CustomHeader(const QXmlStreamAttributes& aAttributes){
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
        if(aAttributes.hasAttribute("id"))          fromString(aAttributes.value("id").toString(),mId);
        if(aAttributes.hasAttribute("caption"))     fromString(aAttributes.value("caption").toString(),mCaption);
        if(aAttributes.hasAttribute("description")) fromString(aAttributes.value("description").toString(),mDescription);
    }

private:
    QString mId;
    QString mCaption;
    QString mDescription;
};


template<typename T>
class CustomDataExt : public CustomData
{
public:
    CustomDataExt(const T& aValue,const T& aDefaultValue,const T& aResetValue)
        :mValue(aValue),mDefaultValue(aDefaultValue),mResetValue(aResetValue)
    {}
    CustomDataExt(const T& aValue,const T& aDefaultValue)
        :mValue(aValue),mDefaultValue(aDefaultValue),mResetValue(aValue)
    {}
    CustomDataExt(const T& aValue)
        :mValue(aValue),mDefaultValue(aValue),mResetValue(aValue)
    {}
    CustomDataExt(const T& aValue, const QXmlStreamAttributes& aAttributes)
        :mValue(aValue)
    {
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

    QString getStringValue() const override             { return toString(mValue); }
    void setStringValue(const QString& aValue) override { fromString(aValue,mValue); }

    QXmlStreamAttributes toXMLAttributes() const override{
        QXmlStreamAttributes attributes;
        attributes.append( {"default", toString(mDefaultValue)});
        attributes.append( {"reset",   toString(mResetValue)});
        return attributes;
    }

    void fromXMLAttributes(const QXmlStreamAttributes& aAttributes) override{
        if(aAttributes.hasAttribute("default")) fromString( aAttributes.value("default").toString(), mDefaultValue);
        if(aAttributes.hasAttribute("reset"))   fromString( aAttributes.value("reset").toString(), mResetValue );
    }

protected:
    T mValue;
    T mDefaultValue;
    T mResetValue;
};

template<typename T>
class SIDigits     : public CustomDataExt<T>{
public:
    SIDigits(const T& value = 0,const T& min= std::numeric_limits<T>::min(),const T& max = std::numeric_limits<T>::max(),const T& defaultValue = 0,const T& resetValue = 0)
        :CustomDataExt<T>(value,defaultValue,resetValue),mMin(min),mMax(max)
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

class SILcd         : public CustomDataExt<double>{
public:
    enum mode{HEX,DEC,OCT,BIN};
    SILcd(double value = 0,int mode = DEC)
        :CustomDataExt<double>(value),mDisplayMode(mode)
    {}
    int getDisplayMode(){return mDisplayMode;}
private:
    int mDisplayMode;
};

class SIImage       : public CustomDataExt<QString>{
public:
    SIImage(const QString& value = ""):CustomDataExt<QString>(value){}
};

class SIString      : public CustomDataExt<QString>{
public:
    SIString(const QString& value = "",const QString& defaultValue = "",const QString& resetValue = "")
        :CustomDataExt<QString>(value,defaultValue,resetValue)
    {}
};

class SIText      : public CustomDataExt<QString>{
public:
    SIText(const QString& value = "",const QString& defaultValue = "",const QString& resetValue = "")
        :CustomDataExt<QString>(value,defaultValue,resetValue)
    {}
};

class SIPlot        : public CustomDataExt<QVector<double>>{
public:
    SIPlot(const QVector<double>& value = QVector<double>()):CustomDataExt<QVector<double>>(value){}
};

class SIBars        : public SIPlot{
public:
    SIBars(const QVector<double>& value = QVector<double>()):SIPlot(value){}
};

class SIGraph        : public SIPlot{
public:
    SIGraph(const QVector<double>& value = QVector<double>()):SIPlot(value){}
};

class SIBoolean      : public CustomDataExt<bool>{
public:
    SIBoolean(bool value = false, bool defaultValue = false, bool resetValue = false)
        :CustomDataExt<bool>(value,defaultValue,resetValue)
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

#endif //CUSTOMDATA_H
