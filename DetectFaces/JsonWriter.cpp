#include <filesystem>
#include "JsonWriter.h"
#include "Face.h"

using namespace std;
using namespace cv;
using namespace boost;
using namespace boost::property_tree;
using namespace std::filesystem;

JsonWriter::JsonWriter()
{
}

ptree JsonWriter::makeCoordinatesRoot(Face face)
{
	ptree root, child;
	vector<Point> vectorOfPoints = face.getCoordinates();
	for (auto &point : vectorOfPoints)
	{
		child.put("", point);
		root.push_back(std::make_pair("", child));
	}
	return root;
}

ptree JsonWriter::makeANodeWithFileNameAndCoordinates(Face face)
{
	ptree root;
	root.put("Name Of file", face.getName());
	root.add_child("Coordinates", makeCoordinatesRoot(face));
	return root;
}

void JsonWriter::writeFacesInJson(vector<Face> faces, std::filesystem::path fileNamePath, string fileName)
{
	ptree root, children;
	for (int i = 0; i < faces.size(); i++)
	{
		ptree node = makeANodeWithFileNameAndCoordinates(faces[i]);
		children.push_back(make_pair("", node));
	}
	root.add_child("Result", children);
	write_json(generateJsonName(fileNamePath, fileName), root);
}

string JsonWriter::generateJsonName(std::filesystem::path fileNamePath, string fileName)
{
		string pathString = fileNamePath.parent_path().string();
		string jsonName = (boost::format("ResultJson%1%.json") % fileName).str();
		string fullPath = (boost::format("%1%/%2%") % pathString % jsonName).str();
		return fullPath;		
}

JsonWriter::~JsonWriter()
{
}