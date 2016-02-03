#pragma once

#include <QDomDocument>
#include <QDomElement>
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QFile>

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
        ser->serialize(_value.m_dbPort,     "m_dbPort",     element, doc, XmlSerializer::Node);
        ser->serialize(_value.m_dbUser,     "m_dbUser",     element, doc, XmlSerializer::Node);
    }

    friend void xmlDeserialize(MySqlSettings &_value, QDomElement *element, XmlSerializer *ser)
    {
        ser->deserialize(_value.m_dbAdress,   "m_dbAdress",   element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbName,     "m_dbName",     element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbPassword, "m_dbPassword", element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbPort,     "m_dbPort",     element, XmlSerializer::Node);
        ser->deserialize(_value.m_dbUser,     "m_dbUser",     element, XmlSerializer::Node);
    }

    в которых указать переменные и их названия для сохранения/загрузки.
    последний параметр XmlSerializer::Attribute/Node указывает, параметр будет добавлен как атрибут для текущего узла,
    или будет создан дочерний узел и ему присвоен атрибут value с указанными значением.

    Функции save/load слушат для сохраения/загрузки класса в файловую систему.
 */


bool writeToFile(const QString &_path, const QString &_text, bool _append = true, const QString &_codec = "UTF-8");
QString readFromFile(const QString &_path, const QString &_codec = "UTF-8");

class XmlSerializer
{
public:
    enum
    {
        Node,
        Attribute
    };

    template<class T>
    static bool save(const T &_value, const QString &_path, const QString &_xmlNode)
    {
        XmlSerializer ser;
        QDomDocument doc;
        QDomElement root = doc.createElement("root");
        doc.appendChild(root);
        if(!ser.serialize(_value, _xmlNode, &root, &doc))
        {
            return false;
        }

        if(!writeToFile(_path, doc.toString(4), false))
        {
            return false;
        }
        return true;
    }

    template<class T>
    static bool load(T &_value, const QString &_path, const QString &_xmlNode)
    {
        XmlSerializer ser;
        QString xml = readFromFile(_path);
        QDomDocument doc;
        doc.setContent(xml);
        QDomElement root = doc.documentElement();
        if(!ser.deserialize(_value, _xmlNode, &root))
        {
            return false;
        }

        return true;
    }

    template<class T>
    bool serialize(const T &_value, const QString &_nodeName, QDomElement *const element, QDomDocument * const doc)
    {
        QDomElement subElement;
        subElement = doc->createElement(_nodeName);
        xmlSerialize(_value, &subElement, doc, this);
        element->appendChild(subElement);

        return true;
    }

    template<class T>
    bool serialize(const QVector<T> &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc)
    {
        QDomElement subElement;
        subElement = doc->createElement(_nodeName);
        element->appendChild(subElement);

        for(int i = 0 ; i < _value.size(); i++)
        {
            serialize(_value.at(i), "element", &subElement, doc);
        }

        return true;
    }

    template<class T>
    bool serialize(const QList<T> &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc)
    {
        QDomElement subElement;
        subElement = doc->createElement(_nodeName);
        element->appendChild(subElement);

        for(int i = 0 ; i < _value.size(); i++)
        {
            serialize(_value.at(i), "element", &subElement, doc);
        }

        return true;
    }

    template<class T>
    bool deserialize(T &_value, const QString &_nodeName, const QDomElement * const element)
    {
        QDomElement subElement;
        QDomNodeList nodeList;
        if(_nodeName.isEmpty())
        {
            subElement = element->cloneNode().toElement();
        } else
        {
            subElement = element->firstChildElement(_nodeName);
        }

        xmlDeserialize(_value, &subElement, this);

        return true;
    }

    template<class T>
    bool deserialize(QVector<T> &_value, const QString &_nodeName, const QDomElement *const element)
    {
        _value.clear();

        QDomElement subElement;
        QDomNodeList nodeList;
        if(_nodeName.isEmpty())
        {
            subElement = element->cloneNode().toElement();
        } else
        {
            subElement = element->firstChildElement(_nodeName);
        }

        nodeList = subElement.childNodes();

        for(int i = 0 ; i < nodeList.size(); i++)
        {
            T item;
            deserialize(item, "", &nodeList.at(i).toElement());
            _value.push_back(item);
        }

        return true;
    }



    template<class T>
    bool deserialize(QList<T> &_value, const QString &_nodeName, const QDomElement *const element)
    {
        _value.clear();

        QDomElement subElement;
        QDomNodeList nodeList;
        if(_nodeName.isEmpty())
        {
            subElement = element->cloneNode().toElement();
        } else
        {
            subElement = element->firstChildElement(_nodeName);
        }

        nodeList = subElement.childNodes();

        for(int i = 0 ; i < nodeList.size(); i++)
        {
            T item;
            deserialize(item, "", &nodeList.at(i).toElement());
            _value.push_back(item);
        }

        return true;
    }

    bool serialize(const int &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type = Node);
    bool serialize(const QString &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type = Node);
    bool serialize(const double &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type = Node);
    bool serialize(const bool &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type = Node);
    bool serialize(const QStringList &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc);
    bool serialize(const QByteArray &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type = Node);

    bool deserialize(int &_value, const QString &_nodeName, const QDomElement *const element, int _type = Node);
    bool deserialize(bool &_value, const QString &_nodeName, const QDomElement *const element, int _type = Node);
    bool deserialize(QString &_value, const QString &_nodeName, const QDomElement *const element, int _type = Node);
    bool deserialize(double &_value, const QString &_nodeName, const QDomElement *const element, int _type = Node);
    bool deserialize(QStringList &_value, const QString &_nodeName, const QDomElement *constelement);
    bool deserialize(QByteArray &_value, const QString &_nodeName, const QDomElement *const element, int _type = Node);
};
