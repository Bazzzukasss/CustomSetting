#include "CustomItemTypes.h"

void registerCustomItemTypes()
{
	qRegisterMetaType<SIBoolean	>("SIBoolean");
	qRegisterMetaType<SIInteger	>("SIInteger");
	qRegisterMetaType<SIDouble	>("SIDouble");
	qRegisterMetaType<SILcd		>("SILcd");
	qRegisterMetaType<SIProgress>("SIProgress");
	qRegisterMetaType<SIString	>("SIString");
	qRegisterMetaType<SIStringList	>("SIStringList");
	qRegisterMetaType<SIBooleanList	>("SIBooleanStringList");
	qRegisterMetaType<SIText	>("SIText");
	qRegisterMetaType<SIBars	>("SIBars");
	qRegisterMetaType<SIGraph	>("SIGraph");

	QMetaType::registerConverter<SIBoolean	, QString>([](SIBoolean const& aIn) { 
		return QString("%1").arg(aIn.getValue() ? 1 : 0);
	});
	QMetaType::registerConverter<SIInteger	, QString>([](SIInteger const& aIn) {
		return QString("%1").arg(aIn.getValue());
	});
	QMetaType::registerConverter<SIDouble	, QString>([](SIDouble  const& aIn) {
		return QString("%1").arg(aIn.getValue()); 
	});
// 	QMetaType::registerConverter<SILcd		, QString>();
// 	QMetaType::registerConverter<SIProgress , QString>();
	QMetaType::registerConverter<SIString	, QString>(
		[](SIString  const& aIn) { return QString("%1").arg(aIn.getValue());
	});
//	QMetaType::registerConverter<SIBars		, QString>();
//	QMetaType::registerConverter<SIGraph	, QString>();

	QMetaType::registerConverter<QString, SIBoolean	>([](QString const& aIn) {
		return SIBoolean(1 == aIn.toInt()); 
	});
	QMetaType::registerConverter<QString, SIInteger	>([](QString const& aIn) {
		return SIInteger(aIn.toInt());	  
	});
	QMetaType::registerConverter<QString, SIDouble	>([](QString const& aIn) {
		return SIDouble (aIn.toDouble());   
	});		
// 	QMetaType::registerConverter<QString, SILcd		>([](QString const& aIn) {});		
// 	QMetaType::registerConverter<QString, SIProgress>([](QString const& aIn) {});		
	QMetaType::registerConverter<QString, SIString	>([](QString const& aIn) { 
		return SIString (aIn);			  
	});		
// 	QMetaType::registerConverter<QString, SIBars	>([](QString const& aIn) {});	
// 	QMetaType::registerConverter<QString, SIGraph	>([](QString const& aIn) {});		
}

