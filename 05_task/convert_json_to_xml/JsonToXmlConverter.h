#include <iostream>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <fstream>

class JsonToXmlConverter
{
private:
    boost::property_tree::ptree pt;

public:
    JsonToXmlConverter(const std::string& fileName)
    {
        boost::property_tree::read_json(fileName, pt);
    }

    void convertToXml(const std::string& outputFilePath = "output.xml")
    {
        boost::property_tree::ptree xml;
        xml.put("root.error.code", pt.get<std::string>("error.code"));
        xml.put("root.error.text", pt.get<std::string>("error.text"));

        BOOST_FOREACH(auto response, pt.get_child("response"))
        {
            boost::property_tree::ptree response_node;
            response_node.put("id", response.second.get<std::string>("id"));
            response_node.put("number", response.second.get<std::string>("number"));

            BOOST_FOREACH(auto detail, response.second.get_child("details"))
            {
                boost::property_tree::ptree detail_node;
                detail_node.put("id", detail.second.get<std::string>("id"));
                detail_node.put("name", detail.second.get<std::string>("name"));
                detail_node.put("value", detail.second.get<std::string>("value"));
                response_node.add_child("details.detail", detail_node);
            }

            xml.add_child("root.response.detail", response_node);
        }

        std::ofstream xml_file(outputFilePath);
        boost::property_tree::write_xml(xml_file, xml, boost::property_tree::xml_writer_make_settings<std::string>(' ', 2));
    }
};