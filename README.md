# xmlserializer

Класс для сериализации/десериализации полей класса в Xml формат.
Есть вариант на основе Qt: QDomDocument, QDomElement и на основе TinyXml


Использование с Qt:
  В pro своего проекта подключить файл qtbase/Sources/XmlSerializer.pri
  В pro файле в CONFIG добавить xml.
  Для класс который необходимо сериализовать/десериализвать в любом месте определить функции:
  
  ```c++
    friend void xmlSerialize(const MySqlSettings &_value, QDomElement *element, QDomDocument *doc, XmlSerializer *ser)
    {
        ser->serialize(_value.m_dbAdress,   "m_dbAdress",   element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_dbName,     "m_dbName",     element, doc, XmlSerializer::Attribute);
        ser->serialize(_value.m_dbPassword, "m_dbPassword", element, doc);
        ser->serialize(_value.m_dbPort,     "m_dbPort",     element, doc, XmlSerializer::Node);
        ser->serialize(_value.m_dbUser,     "m_dbUser",     element, doc, XmlSerializer::Node);
    }

    friend void xmlDeserialize(MySqlSettings &_value, QDomElement *element, XmlSerializer *ser)
    {
        ser->deserialize(_value.m_dbAdress,   "m_dbAdress",   element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbName,     "m_dbName",     element, XmlSerializer::Attribute);
        ser->deserialize(_value.m_dbPassword, "m_dbPassword", element);
        ser->deserialize(_value.m_dbPort,     "m_dbPort",     element, XmlSerializer::Node);
        ser->deserialize(_value.m_dbUser,     "m_dbUser",     element, XmlSerializer::Node);
    }
  ```
  
  если полем класса - является другой класс или неподдерживаемый тип данных, то для него также определить подобные функции.
  
  Используя статические функции 
  ```c++
  XmlSerializer::load(m_settings, path, "Settings") 
  XmlSerializer::save(m_settings, path, "Settings") 
  ```
  загрузить или сохранить состояние.

Для использования версии основанной на TinyXml необходимо сначала собрать библиотеку tinyxml2, для этого можно использовать скрипты tinyxmlbased\tinyxml2\vcproj_Build_tinyXML.cmd или tinyxmlbased\tinyxml2\vcproj_Build_tinyXML static.cmd в который указать путь к иснтрументам msvc. Или открыть проект в Visual Studio и собрать из неё.
