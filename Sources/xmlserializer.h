#pragma once

#include <string>
#include <vector>
#include "tinyxml2.h"

using namespace tinyxml2;

/*!
 * \brief The XmlSerializer class
 * позволяет сохранять/загружать состояние класса в xml структуру
 * поддерживаются списки QVector<T>, QString<T>, базовые типы: int, double, bool, QString
 * для возможности сериалиазации необходимо объявить для нужно класса два метода:
 *  friend void xmlSerialize(const MySqlSettings &_value, QDomElement *element, QDomDocument *doc, XmlSerializer *ser)
    {
        ser->serialize(_value.m_dbAdress,   "m_dbAdress",   element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_dbName,     "m_dbName",     element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_dbPassword, "m_dbPassword", element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_dbPort,     "m_dbPort",     element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_dbUser,     "m_dbUser",     element, doc, XmlSerializer::Attribute);
    }

    friend void xmlDeserialize(MySqlSettings &_value, QDomElement *element, XmlSerializer *ser)
    {
        ser->deserialize(_value.m_dbAdress,   "m_dbAdress",   element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbName,     "m_dbName",     element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbPassword, "m_dbPassword", element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbPort,     "m_dbPort",     element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbUser,     "m_dbUser",     element, XmlSerializer::Attribute);
    }

    в которых указать переменные и их названия для сохранения/загрузки.
    последний параметр XmlSerializer::Attribute/Node указывает, параметр будет добавлен как атрибут для текущего узла,
    или будет создан дочерний узел и ему присвоен атрибут value с указанными значением.

    Функции save/load слушат для сохраения/загрузки класса в файловую систему.
 */


class XmlSerializer
{
public:
    enum
    {
        Node,
        Attribute
    };

    template<class T>
    static bool save(const T &_value, const std::string &_path, const std::string &_xmlNode)
    {
        XmlSerializer ser;
        XMLDocument doc;
        XMLElement *root = doc.NewElement("root");
        doc.InsertFirstChild(root);
        if(!ser.serialize(_value, _xmlNode, root, &doc))
        {
            return false;
        }
        doc.SaveFile(_path.c_str());

        return true;
    }

    template<class T>
    static bool load(T &_value, const std::string &_path, const std::string &_xmlNode)
    {
        XmlSerializer ser;
        XMLDocument doc;
        doc.LoadFile(_path.c_str());
        XMLElement *root = doc.RootElement();
        if(!root) return false;
        if(!ser.deserialize(_value, _xmlNode, root))
        {
            return false;
        }

        return true;
    }

    template<class T>
    bool serialize(const T &_value, const std::string &_nodeName, XMLElement *const element, XMLDocument * const doc)
    {
        XMLElement *subElement;
        subElement = doc->NewElement(_nodeName.c_str());
        xmlSerialize(_value, subElement, doc, this);
        element->InsertFirstChild(subElement);

        return true;
    }

    template<class T>
    bool serialize(const std::vector<T> &_value, const std::string &_nodeName, XMLElement *const _element, XMLDocument *const _doc)
    {
        XMLElement *subElement = 0;
        subElement = _doc->NewElement(_nodeName.c_str());
        _element->InsertFirstChild(subElement);

        for(size_t i = 0 ; i < _value.size(); i++)
        {
            serialize(_value.at(i), "element", subElement, _doc);
        }

        return true;
    }

    template<class T>
    bool deserialize(T &_value, const std::string &_nodeName, const XMLElement * const _element) const
    {
        if(_nodeName == "")
        {
            xmlDeserialize(_value, _element, this);
        } else
        {
            xmlDeserialize(_value, _element->FirstChild()->ToElement(), this);
        }

        return true;
    }

    template<class T>
    bool deserialize(std::vector<T> &_value, const std::string &_nodeName, const XMLElement *const _element) const
    {
        _value.clear();

        const XMLElement *subElement = 0;

        if(_nodeName == "")
        {
            subElement = _element;
        } else
        {
            subElement = _element->FirstChildElement(_nodeName.c_str());
            if(!subElement) return false;
        }

        const XMLElement *nodeElement = subElement->FirstChildElement("element"
                                                                      "");
        if(!nodeElement) return false;

        while(nodeElement)
        {
            T item;
            deserialize(item, "", nodeElement);
            _value.push_back(item);
            nodeElement = nodeElement->NextSiblingElement();
        }

        return true;
    }

    bool serialize(const int &_value, const std::string &_nodeName, XMLElement *const element, XMLDocument *const doc, int _type = Node);
    bool serialize(const std::string &_value, const std::string &_nodeName, XMLElement * const element, XMLDocument * const doc, int _type = Node);
    bool serialize(const double &_value, const std::string &_nodeName, XMLElement * const element, XMLDocument * const doc, int _type = Node);
    bool serialize(const bool &_value, const std::string &_nodeName, XMLElement * const element, XMLDocument * const doc, int _type = Node);

    bool deserialize(int &_value, const std::string &_nodeName, const XMLElement *const _element, int _type = Node) const;
    bool deserialize(bool &_value, const std::string &_nodeName, const XMLElement *const _element, int _type = Node) const;
    bool deserialize(std::string &_value, const std::string &_nodeName, const XMLElement *const _element, int _type = Node) const;
    bool deserialize(double &_value, const std::string &_nodeName, const XMLElement *const _element, int _type = Node) const;
};
