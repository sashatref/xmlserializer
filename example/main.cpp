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

    std::cout << XmlSerializer::save(someClass, "C:/out.xml", "SomeClass");
	_getch();
    return 0;
}

