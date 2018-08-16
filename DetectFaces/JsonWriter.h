#include<opencv2/opencv.hpp>
#include<iostream>
#include <boost/property_tree/json_parser.hpp>
#include "Face.h"
#include <filesystem>

class JsonWriter
{
public:
	JsonWriter();
	boost::property_tree::ptree makeCoordinatesRoot(Face face);
	boost::property_tree::ptree makeANodeWithFileNameAndCoordinates(Face face);
	void writeFacesInJson(std::vector<Face> faces, std::filesystem::path fileNamePath, std::string fileName);
	std::string generateJsonName(std::filesystem::path fileNamePath, std::string fileName);
	~JsonWriter();
};

