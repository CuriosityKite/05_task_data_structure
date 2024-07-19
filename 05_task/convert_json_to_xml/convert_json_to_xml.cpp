#include "JsonToXmlConverter.h"

int main() 
{
    JsonToXmlConverter converter("D:\\2.5.json");
    converter.convertToXml("output.xml");

    return 0;
}