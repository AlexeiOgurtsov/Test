#include <iostream>
#include <filesystem>
#include <boost/property_tree/json_parser.hpp>
#include "Face.h"

using namespace std;
using namespace cv;
using namespace boost;

void Face::makeCoordinates()
{
	Point point1(rectangle.x, rectangle.y);
	coordinates.push_back(point1);
	Point point2(rectangle.x, rectangle.y + rectangle.width);
	coordinates.push_back(point2);
	Point point3(rectangle.x + rectangle.height, rectangle.y);
	coordinates.push_back(point3);
	Point point4(rectangle.x + rectangle.height, rectangle.y + rectangle.width);
	coordinates.push_back(point4);
}

void Face::convertMouthCoordinatesFromRoiToImage(Mat inputImage)
{
	Mat mouthROI = inputImage(Rect(rectangle.x, rectangle.y + rectangle.height * 0.66, rectangle.width, rectangle.height / 3));
	Point offset;
	Size wholesize;
	Mat img(mouthROI, mouth);
	img.locateROI(wholesize, offset);
	Point point1(offset.x, offset.y);
	Point point2(offset.x + mouth.height, offset.y + mouth.width);
	mouth = Rect(point1, point2);
}

void Face::convertEyesCoordinatesFromRoiToImage(Mat inputImage)
{
	Mat eyesROI = inputImage(Rect(rectangle.x, rectangle.y + rectangle.height * 0.19, rectangle.width, rectangle.height / 3));
	for (int i = 0; i < eyes.size(); i++)
	{
		Point offset;
		Size wholesize;
		Mat img(eyesROI, eyes[i]);
		img.locateROI(wholesize, offset);
		Point point1(offset.x, offset.y);
		Point point2(offset.x + eyes[i].height, offset.y + eyes[i].width);
		eyes[i] = Rect(point1, point2);
	}

}

vector<Point> Face::getEyesCoordinates()
{
	vector<Point> eyesCoordinates;
	for (int i = 0; i < eyes.size(); i++)
		{	
			vector<Point> eyesPoints = getCoordinatesFromRectangle(eyes[i]);
			eyesCoordinates.insert(eyesCoordinates.end(), eyesPoints.begin(), eyesPoints.end());
		}
	return eyesCoordinates;
}

vector<Point> Face::getMouthCoordinates()
{
	vector<Point> mouthCoordinates;
	vector<Point> mouthPoints = getCoordinatesFromRectangle(mouth);
	mouthCoordinates.insert(mouthCoordinates.end(), mouthPoints.begin(), mouthPoints.end());
	return mouthCoordinates;
}

vector<Point> Face::getCoordinatesFromRectangle(Rect area)
{	
			vector<Point> areaCoordinates;
			Point point1(area.x, area.y);
			areaCoordinates.push_back(point1);
			Point point2(area.x, area.y + area.width);
			areaCoordinates.push_back(point2);
			Point point3(area.x + area.height, area.y);
			areaCoordinates.push_back(point3);
			Point point4(area.x + area.height, area.y + area.width);
			areaCoordinates.push_back(point4);
			return areaCoordinates;
}

Face::Face()
{

}

Face::Face(Mat Image, string Name, vector<Point> Coordinates, vector<Rect> Eyes, Rect Mouth)
{
	image = Image;
	name = Name;
	coordinates = Coordinates;
	eyes = Eyes;
	mouth = Mouth;
}

void Face::setImage(Mat Image)
{
	image = Image(Rect(rectangle.x, rectangle.y, rectangle.width, rectangle.height));
}

void Face::setRectangle(Rect Rectangle)
{
	rectangle = Rectangle;
}

void Face::setName(string Name)
{
	name = Name;
}

void Face::generateName(int numberOfFoundFace, string fileName)
{
	unsigned lastIndex = fileName.find_last_of(".");
	string fileNameWithoutExtention = fileName.substr(0, lastIndex);
	string generatedName = (boost::format("%1%Face%2%.jpg") % fileNameWithoutExtention % numberOfFoundFace).str();
	name = generatedName;
}

void Face::setCoordinates(vector<Point> Coordinates)
{
	coordinates = Coordinates;
}

void Face::setEyes(vector<Rect> Eyes)
{
	eyes = Eyes;
}

void Face::setMouth(Rect Mouth)
{
	mouth = Mouth;
}

Mat Face::getImage()
{
	return image;
}

Rect Face::getRectangle()
{
	return rectangle;
}

string Face::getName()
{
	return name;
}

vector<Point> Face::getCoordinates()
{
	return coordinates;
}

vector<Rect> Face::getEyes()
{
	return eyes;
}

Rect Face::getMouth()
{
	return mouth;
}

void Face::saveFace(std::filesystem::path folderPath, string fileName)
{
	mirrorEffect();
	imwrite(makeAFullPathToSaveImage(folderPath, fileName), image);
	mirrorEffect();
}

void Face::mirrorEffect()
{
	flip(image, image, 1);
}

string Face::makeAFullPathToSaveImage(std::filesystem::path folderPath, string fileName)
{	
	string pathString = folderPath.parent_path().string();
	string fullPath = (boost::format("%1%/%2%") % pathString % name).str();
	return fullPath;
}

Face::~Face()
{
}
