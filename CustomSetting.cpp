#include "CustomSetting.h"
std::ostream& operator<<(std::ostream& s, const CustomSetting& aSetting)
{
    static QString space("");
    s << space.toStdString() << "<" << aSetting.getTag().toStdString() << toString(aSetting.getXMLAttributes()).toStdString() << ">" << aSetting.getStringValue().toStdString() << std::endl;
    space += " ";
    for(auto& child : aSetting.mSettings)
        s << space.toStdString() << *child;
    space = space.left(space.length() - 1);
    return s;
}
