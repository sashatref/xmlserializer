#include <string>
#include <conio.h>
#include <iostream>

#include "myclass.h"
#include "xmlserializer.h"

int main(int, char **)
{
    MyClass someClass;
//    someClass.intVec.push_back(0);
//    someClass.intVec.push_back(1);
//    someClass.intVec.push_back(2);
//    someClass.intVec.push_back(3);
//    someClass.intVec.push_back(4);

//    someClass.subClassVec.push_back(SubClass());
//    someClass.subClassVec.push_back(SubClass());
//    someClass.subClassVec.push_back(SubClass());
//    someClass.subClassVec.push_back(SubClass());

    /*std::cout << XmlSerializer::save(someClass, "C:/out.xml", "SomeClass");*/

	XMLDocument *doc = new XMLDocument();
	
	XMLElement *el1 = doc->NewElement("root");
	el1->SetAttribute("attr1", "value1");

	doc->LinkEndChild(el1);

	XMLElement *el2 = doc->NewElement("subroot");

	//el2->SetText("SomeText <b>Text</b> asdas");

	el2->SetValue("SomeText_asdas");

	el1->LinkEndChild(el2);

	doc->SaveFile("C:/out1.xml");

	_getch();
    return 0;
}

