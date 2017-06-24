#include <iostream>
#include "Builder.h"

using namespace std;

void main()
{
	Txt_converter converter1{ "Input.txt" };
	converter1.attach_xml(std::make_unique<Xml_file>());

	Director director{};
	director.attach(&converter1);
	director.convert_to_xml();

	system("pause");
}