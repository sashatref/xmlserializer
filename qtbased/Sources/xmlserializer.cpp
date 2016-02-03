#include "xmlserializer.h"


bool XmlSerializer::serialize(const int &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type)
{
    QDomElement subElement;
    switch(_type)
    {
    case Node:
        subElement = doc->createElement(_nodeName);
        subElement.setAttribute("value", _value);
        element->appendChild(subElement);
        break;
    case Attribute:
        element->setAttribute(_nodeName, _value);
        break;
    }

    return true;
}

bool XmlSerializer::serialize(const QString &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type)
{
    QDomElement subElement;
    switch(_type)
    {
    case Node:
        subElement = doc->createElement(_nodeName);
        subElement.setAttribute("value", _value);
        element->appendChild(subElement);
        break;
    case Attribute:
        element->setAttribute(_nodeName, _value);
        break;
    }

    return true;
}

bool XmlSerializer::serialize(const double &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type)
{
    QDomElement subElement;
    switch(_type)
    {
    case Node:
        subElement = doc->createElement(_nodeName);
        subElement.setAttribute("value", _value);
        element->appendChild(subElement);
        break;
    case Attribute:
        element->setAttribute(_nodeName, _value);
        break;
    }

    return true;
}

bool XmlSerializer::serialize(const bool &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc, int _type)
{
    QDomElement subElement;
    switch(_type)
    {
    case Node:
        subElement = doc->createElement(_nodeName);
        subElement.setAttribute("value", _value);
        element->appendChild(subElement);
        break;
    case Attribute:
        element->setAttribute(_nodeName, _value);
        break;
    }

    return true;
}

bool XmlSerializer::serialize(const QStringList &_value, const QString &_nodeName, QDomElement *const element, QDomDocument *const doc)
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

bool XmlSerializer::serialize(const QByteArray &_value, const QString &_nodeName, QDomElement * const element, QDomDocument * const doc, int _type)
{
    QDomElement subElement;
    switch(_type)
    {
    case Node:
        subElement = doc->createElement(_nodeName);
        subElement.setAttribute("value", QString(_value));
        element->appendChild(subElement);
        break;
    case Attribute:
        element->setAttribute(_nodeName, QString(_value));
        break;
    }

    return true;
}

bool XmlSerializer::deserialize(QStringList &_value, const QString &_nodeName, const QDomElement *const element)
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
        QString item;
        deserialize(item, "", &nodeList.at(i).toElement());
        _value.push_back(item);
    }

    return true;
}

bool XmlSerializer::deserialize(QByteArray &_value, const QString &_nodeName, const QDomElement * const element, int _type)
{
    if(_nodeName.isEmpty())
    {
        _value = element->attribute("value").toUtf8();
        return true;
    }

    switch(_type)
    {
    case Node:
        _value = element->firstChildElement(_nodeName).attribute("value").toUtf8();
        break;
    case Attribute:
        _value = element->attribute(_nodeName).toUtf8();
        break;
    }

    return true;
}

bool XmlSerializer::deserialize(int &_value, const QString &_nodeName, const QDomElement *const element, int _type)
{
    if(_nodeName.isEmpty())
    {
        _value = element->attribute("value").toInt();
        return true;
    }

    switch(_type)
    {
    case Node:
        _value = element->firstChildElement(_nodeName).attribute("value").toInt();
        break;
    case Attribute:
        _value = element->attribute(_nodeName).toInt();
        break;
    }

    return true;
}

bool XmlSerializer::deserialize(bool &_value, const QString &_nodeName, const QDomElement *const element, int _type)
{
    QDomElement subElement;
    QDomNodeList nodeList;
    if(_nodeName.isEmpty())
    {
        _value = element->attribute("value").toInt();
        return true;
    }

    switch(_type)
    {
    case Node:
        _value = element->firstChildElement(_nodeName).attribute("value").toInt();
        break;
    case Attribute:
        _value = element->attribute(_nodeName).toInt();
        break;
    }

    return true;
}

bool XmlSerializer::deserialize(QString &_value, const QString &_nodeName, const QDomElement *const element, int _type)
{
    if(_nodeName.isEmpty())
    {
        _value = element->attribute("value");
        return true;
    }

    switch(_type)
    {
    case Node:
        _value = element->firstChildElement(_nodeName).attribute("value");
        break;
    case Attribute:
        _value = element->attribute(_nodeName);
        break;
    }

    return true;
}

bool XmlSerializer::deserialize(double &_value, const QString &_nodeName, const QDomElement *const element, int _type)
{
    QDomElement subElement;
    QDomNodeList nodeList;
    if(_nodeName.isEmpty())
    {
        _value = element->attribute("value").toDouble();
        return true;
    }

    switch(_type)
    {
    case Node:
        _value = element->firstChildElement(_nodeName).attribute("value").toDouble();
        break;
    case Attribute:
        _value = element->attribute(_nodeName).toDouble();
        break;
    }

    return true;
}

bool writeToFile(const QString &_path, const QString &_text, bool _append, const QString &_codec)
{
    QFile file(_path);
    if(file.open(_append ? QIODevice::Append : QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(qPrintable(_codec));
        stream << _text;
        file.close();
        return true;
    }

    return false;
}

QString readFromFile(const QString &_path, const QString &_codec)
{
    QString result;

    QFile file(_path);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(_codec.toStdString().c_str());
        result = stream.readAll();
        file.close();
    }

    return result;
}
