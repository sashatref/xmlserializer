#include "xmlserializer.h"


bool XmlSerializer::serialize(const int &_value, const std::string &_nodeName, XMLElement * const element, XMLDocument * const doc, int _type)
{
    XMLElement *subElement = 0;
    switch(_type)
    {
    case Node:
        subElement = doc->NewElement(_nodeName.c_str());
        subElement->SetAttribute("value", _value);
        element->InsertEndChild(subElement);
        break;
    case Attribute:
        element->SetAttribute(_nodeName.c_str(), _value);
        break;
    }

    return true;
}

bool XmlSerializer::serialize(const std::string &_value, const std::string &_nodeName, XMLElement * const element, XMLDocument * const doc, int _type)
{
    XMLElement *subElement = 0;
    switch(_type)
    {
    case Node:
        subElement = doc->NewElement(_nodeName.c_str());
        subElement->SetAttribute("value", _value.c_str());
        element->InsertEndChild(subElement);
        break;
    case Attribute:
        element->SetAttribute(_nodeName.c_str(), _value.c_str());
        break;
    }

    return true;
}

bool XmlSerializer::serialize(const double &_value, const std::string &_nodeName, XMLElement * const element, XMLDocument * const doc, /*QDomElement *const element, QDomDocument *const doc,*/ int _type)
{
    XMLElement *subElement = 0;
    switch(_type)
    {
    case Node:
        subElement = doc->NewElement(_nodeName.c_str());
        subElement->SetAttribute("value", _value);
        element->InsertEndChild(subElement);
        break;
    case Attribute:
        element->SetAttribute(_nodeName.c_str(), _value);
        break;
    }

    return true;
}

bool XmlSerializer::serialize(const bool &_value, const std::string &_nodeName, XMLElement * const element, XMLDocument * const doc, /*QDomElement *const element, QDomDocument *const doc,*/ int _type)
{
    XMLElement *subElement = 0;
    switch(_type)
    {
    case Node:
        subElement = doc->NewElement(_nodeName.c_str());
        subElement->SetAttribute("value", _value);
        element->InsertEndChild(subElement);
        break;
    case Attribute:
        element->SetAttribute(_nodeName.c_str(), _value);
        break;
    }
    return true;
}


bool XmlSerializer::deserialize(int &_value, const std::string &_nodeName, const XMLElement * const _element, int _type) const
{
    const XMLElement *subElement = 0;
    const char *valueCh = 0;
    if(_nodeName == "")
    {
        valueCh = _element->Attribute("value");
        if(valueCh)
        {
            _value = atoi(valueCh);
        }
        return true;
    }

    switch(_type)
    {
    case Node:
        subElement = _element->FirstChildElement(_nodeName.c_str());
        if(subElement)
        {
            valueCh = subElement->Attribute("value");
            if(valueCh)
            {
                _value = atoi(valueCh);
            }
        }
        break;
    case Attribute:
        valueCh = _element->Attribute(_nodeName.c_str());
        if(valueCh)
        {
            _value = atoi(valueCh);
        }
        break;
    }

    return true;
}

#pragma warning(push, 0)

bool XmlSerializer::deserialize(bool &_value, const std::string &_nodeName, const XMLElement * const _element, int _type) const
{
    const XMLElement *subElement = 0;
    const char *valueCh = 0;
    if(_nodeName == "")
    {
        valueCh = _element->Attribute(_nodeName.c_str());
        if(valueCh)
        {
            _value = (bool)atoi(valueCh);
        }
        return true;
    }

    switch(_type)
    {
    case Node:
        subElement = _element->FirstChildElement(_nodeName.c_str());
        if(subElement)
        {
            valueCh = subElement->Attribute("value");
            if(valueCh)
            {
                _value = (bool)atoi(valueCh);
            }
        }
        break;
    case Attribute:
        valueCh = _element->Attribute(_nodeName.c_str());
        if(valueCh)
        {
            _value = (bool)atoi(valueCh);
        }
        break;
    }

    return true;
}
#pragma warning(pop)

bool XmlSerializer::deserialize(std::string &_value, const std::string &_nodeName, const XMLElement * const _element, int _type) const
{
    const XMLElement *subElement = 0;
    const char *valueCh = 0;
    if(_nodeName == "")
    {
        valueCh = _element->Attribute(_nodeName.c_str());
        if(valueCh)
        {
            _value = std::string(valueCh);
        }
        return true;
    }

    switch(_type)
    {
    case Node:
        subElement = _element->FirstChildElement(_nodeName.c_str());
        if(subElement)
        {
            valueCh = subElement->Attribute("value");
            if(valueCh)
            {
                _value = std::string(valueCh);
            }
        }
        break;
    case Attribute:
        valueCh = _element->Attribute(_nodeName.c_str());
        if(valueCh)
        {
            _value = std::string(valueCh);
        }
        break;
    }

    return true;
}

bool XmlSerializer::deserialize(double &_value, const std::string &_nodeName, const XMLElement * const _element, int _type) const
{
    const XMLElement *subElement = 0;
    const char *valueCh = 0;
    if(_nodeName == "")
    {
        valueCh = _element->Attribute(_nodeName.c_str());
        if(valueCh)
        {
            _value = atof(valueCh);
        }
        return true;
    }

    switch(_type)
    {
    case Node:
        subElement = _element->FirstChildElement(_nodeName.c_str());
        if(subElement)
        {
            valueCh = subElement->Attribute("value");
            if(valueCh)
            {
                _value = atof(valueCh);
            }
        }
        break;
    case Attribute:
        valueCh = _element->Attribute(_nodeName.c_str());
        if(valueCh)
        {
            _value = atof(valueCh);
        }
        break;
    }

    return true;
}
