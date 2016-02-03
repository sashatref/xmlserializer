#pragma once

#include <string>
#include <vector>
#include "xmlserializer.h"

using namespace tinyxml2;

class SubClass
{
public:
    SubClass() :
        subIntValue(0),
        subStringValue()
    {

    }

    int subIntValue;
    std::string subStringValue;

    friend void xmlSerialize(const SubClass &_value, XMLElement *const _element, XMLDocument *const _doc, XmlSerializer *const _ser)
    {
        _ser->serialize(_value.subIntValue, "subIntValue", _element, _doc);
        _ser->serialize(_value.subStringValue, "subStringValue", _element, _doc);
    }

    friend void xmlDeserialize(SubClass &_value, const XMLElement *const _element, const XmlSerializer *const _ser)
    {
        _ser->deserialize(_value.subIntValue, "subIntValue", _element);
        _ser->deserialize(_value.subStringValue, "subStringValue", _element);
    }
};

class MyClass
{
public:
    MyClass():
        intValue(0),
        boolValue(false),
        doubleValue(0),
        stringValue()
    {

    }

    int intValue;
    bool boolValue;
    std::string stringValue;
    double doubleValue;
    std::vector<int> intVec;
    std::vector<std::string> stringVec;
    SubClass subClassValue;
    std::vector<SubClass> subClassVec;

    friend void xmlSerialize(const MyClass &_value, XMLElement *const _element, XMLDocument *const _doc, XmlSerializer *const _ser)
    {
        _ser->serialize(_value.intValue, "intValue", _element, _doc);
        _ser->serialize(_value.boolValue, "boolValue", _element, _doc);
        _ser->serialize(_value.stringValue, "stringValue", _element, _doc);
        _ser->serialize(_value.doubleValue, "doubleValue", _element, _doc);
        _ser->serialize(_value.intVec, "intVec", _element, _doc);
        _ser->serialize(_value.stringVec, "stringVec", _element, _doc);
        _ser->serialize(_value.subClassValue, "subClassValue", _element, _doc);
        _ser->serialize(_value.subClassVec, "subClassVec", _element, _doc);
    }

    friend void xmlDeserialize(MyClass &_value, const XMLElement *const _element, const XmlSerializer *const _ser)
    {
        _ser->deserialize(_value.intValue, "intValue", _element);
        _ser->deserialize(_value.boolValue, "boolValue", _element);
        _ser->deserialize(_value.stringValue, "stringValue", _element);
        _ser->deserialize(_value.doubleValue, "doubleValue", _element);
        _ser->deserialize(_value.intVec, "intVec", _element);
        _ser->deserialize(_value.stringVec, "stringVec", _element);
        _ser->deserialize(_value.subClassValue, "subClassValue", _element);
        _ser->deserialize(_value.subClassVec, "subClassVec", _element);
    }
};




