#pragma once

#ifdef XML_SUPPORT
    #include "xmlserializer.h"
#endif

#include "setgetMacro.h"
#include <algorithm>

#include <QObject>
#include <QDate>
#include <QDateTime>
#include <QFont>
#include <QVector>
#include <QDebug>


class MyClass : public QObject
{
    Q_OBJECT
public:
    buildProperty(int, field1)
    buildProperty(QString, field2)
    buildProperty(double, field3)
    buildProperty(bool, field4)

    QString toString() const
    {
        QString result;
        result += "IntValue:" + QString::number(m_field1) +
                " StringValue:" + m_field2 +
                " DoubleValue:" + QString::number(m_field3) +
                " BoolValue:" + QString::number(m_field4);
        return result;
    }

    MyClass()
    {
        m_field1 = rand() % 100;
        m_field3 = rand() % 100;
        m_field4 = rand() % 2;
    }

    MyClass(const MyClass &other)
    {
        qDebug() << "MyClass(const MyClass &)";
        m_field1 = other.m_field1;
        m_field2 = other.m_field2;
        m_field3 = other.m_field3;
        m_field4 = other.m_field4;
    }

    MyClass &operator=(const MyClass &other)
    {
        qDebug() << "MyClass() operator=";
        m_field1 = other.m_field1;
        m_field2 = other.m_field2;
        m_field3 = other.m_field3;
        m_field4 = other.m_field4;
        return *this;
    }

#ifdef XML_SUPPORT
    friend void xmlSerialize(const MyClass &_value, QDomElement *element, QDomDocument *doc, XmlSerializer *ser)
    {
        ser->serialize(_value.m_field1, "filed1", element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_field2, "filed2", element, doc, XmlSerializer::Node);
        ser->serialize(_value.m_field3, "filed3", element, doc, XmlSerializer::Node);
        ser->serialize(_value.m_field4, "filed4", element, doc, XmlSerializer::Node);
    }

    friend void xmlDeserialize(MyClass &_value, QDomElement *element, XmlSerializer *ser)
    {
        ser->deserialize(_value.m_field1, "filed1", element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_field2, "filed2", element, XmlSerializer::Node);
        ser->deserialize(_value.m_field3, "filed3", element, XmlSerializer::Node);
        ser->deserialize(_value.m_field4, "filed4", element, XmlSerializer::Node);
    }
#endif
};



Q_DECLARE_METATYPE(MyClass)


class TestObject : public QObject
{
    Q_OBJECT
public:
    buildProperty(int, intValue)
    buildProperty(bool, boolValue)
    buildProperty(double, doubleValue)
    buildProperty(QString, stringValue)
    buildProperty(QStringList, stringListValue)
    buildProperty(MyClass, myClassValue)
    buildProperty(QByteArray, byteArrayValue)
    buildProperty(QList<MyClass>, myClassList)

    TestObject(QObject *parent = 0) :
        QObject(parent)
    {
        m_intValue = rand() % 100;
        m_boolValue = rand() %2;
        m_doubleValue = rand() %100;

        int strCount = rand() % 8;
        for(int i = 0 ; i < strCount; i++)
        {
            m_stringListValue.push_back("somestr");
        }

        int myclassCount = rand() % 5;
        for(int i = 0 ; i < myclassCount; i++)
        {
            m_myClassList.push_back(MyClass());
        }
    }

    QString toString() const
    {
        QString result;
        result += "IntValue:" + QString::number(m_intValue) + "\n"
                + "BoolValue:" + QString::number(m_boolValue) + "\n"
                + "DoubleValue:" + QString::number(m_doubleValue) + "\n"
                + "StringValue:" + m_stringValue + "\n"
                + "StringListValue:" + m_stringListValue.join(' ') + "\n"
                + "MyClassValue:" + m_myClassValue.toString() + "\n"
                + "ByteArrayValue:" + QString(m_byteArrayValue) + "\n"
                + "MyClassList:\n";
        for(int i = 0 ; i < m_myClassList.size(); i++)
        {
            result += "Element" +QString::number(i) + ": " + m_myClassList[i].toString() + "\n";
        }
        return result;
    }

    TestObject(const TestObject &other)
    {
        m_intValue        = other.m_intValue;
        m_boolValue       = other.m_boolValue;
        m_doubleValue     = other.m_doubleValue;
        m_stringValue     = other.m_stringValue;
        m_linkStringValue = other.m_linkStringValue;
        m_stringListValue = other.m_stringListValue;
        m_myClassValue    = other.m_myClassValue;
        m_byteArrayValue  = other.m_byteArrayValue;
    }

    const TestObject &operator =(const TestObject &other)
    {
        m_intValue        = other.m_intValue;
        m_boolValue       = other.m_boolValue;
        m_doubleValue     = other.m_doubleValue;
        m_stringValue     = other.m_stringValue;
        m_linkStringValue = other.m_linkStringValue;
        m_stringListValue = other.m_stringListValue;
        m_myClassValue    = other.m_myClassValue;
        m_byteArrayValue  = other.m_byteArrayValue;
        return *this;
    }

#ifdef XML_SUPPORT
    friend void xmlSerialize(const TestObject &_value, QDomElement *element, QDomDocument *doc, XmlSerializer *ser)
    {
        ser->serialize(_value.m_intValue,       "m_intValue", element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_doubleValue,    "m_doubleValue", element, doc, XmlSerializer::Node);
        ser->serialize(_value.m_boolValue,      "m_boolValue", element, doc, XmlSerializer::Node);
        ser->serialize(_value.m_stringValue,    "m_stringValue", element, doc, XmlSerializer::Node);
        ser->serialize(_value.m_myClassValue,   "m_myClassValue", element, doc);
        ser->serialize(_value.m_stringListValue, "m_stringListValue", element, doc);
        ser->serialize(_value.m_myClassList, "m_myClassList", element, doc);
    }

    friend void xmlDeserialize(TestObject &_value, QDomElement *element, XmlSerializer *ser)
    {
        ser->deserialize(_value.m_intValue,       "m_intValue", element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_doubleValue,    "m_doubleValue", element, XmlSerializer::Node);
        ser->deserialize(_value.m_boolValue,      "m_boolValue", element, XmlSerializer::Node);
        ser->deserialize(_value.m_stringValue,    "m_stringValue", element, XmlSerializer::Node);
        ser->deserialize(_value.m_myClassValue,   "m_myClassValue", element);
        ser->deserialize(_value.m_stringListValue, "m_stringListValue", element);
        ser->deserialize(_value.m_myClassList, "m_myClassList", element);
    }
#endif

private:
    QVector<MyClass> m_linkStringValue;
};

Q_DECLARE_METATYPE(TestObject)

