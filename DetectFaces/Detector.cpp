#include <iostream>
#include <filesystem>
#include <boost/property_tree/json_parser.hpp>
#include "Detector.h"
#include "Face.h"

using namespace std;
using namespace cv;
using namespace boost;

void Detector::setFaces(vector<Rect> foundedFaces, string fileName)
{
	for (int founedFaceIndex = 0; founedFaceIndex < foundedFaces.size(); founedFaceIndex++)
	{
		Face face;
		face.setRectangle(foundedFaces[founedFaceIndex]);
		face.makeCoordinates();
		face.setImage(image);
		face.generateName(founedFaceIndex, fileName);
		faces.push_back(face);
	}
}

cv::Mat Detector::makeARoi(Face face, cv::Mat image, float coefficient)
{
	Rect rectangle = face.getRectangle();
	Mat roi = image(Rect(rectangle.x, rectangle.y + rectangle.height * coefficient, rectangle.width, rectangle.height / 3));
	return roi;
}
void Detector::detectEyes()
{
	float coefficientForEyeRoi = 0.19;
	CascadeClassifier eyeCascade;
	eyeCascade.load("haarcascade_eye.xml");
	for (int i = 0; i < faces.size(); i++)
	{
		vector<Rect> eyes;
		Mat roi = makeARoi(faces[i], image, coefficientForEyeRoi);
		eyeCascade.detectMultiScale(roi, eyes);
		faces[i].setEyes(eyes);
	}
}

void Detector::makeFacesCoordinates()
{
	for (int i = 0; i < faces.size(); i++)
	{
		faces[i].makeCoordinates();
	}
}

void Detector::convertFaceMembersCoordinatesFromRoiToImage()
{
	for (auto &face : faces)
	{
		face.convertEyesCoordinatesFromRoiToImage(image);
		face.convertMouthCoordinatesFromRoiToImage(image);
	}
}

void Detector::detectMouth()
{
	float coefficientForMouthRoi = 0.67;
	CascadeClassifier mouthCascade;
	mouthCascade.load("haarcascade_smile.xml");
	for (int i = 0; i < faces.size(); i++)
	{
		vector<Rect> mouths;
		Mat roi = makeARoi(faces[i], image, coefficientForMouthRoi);
		mouthCascade.detectMultiScale(roi, mouths);
		faces[i].setMouth(mouths[0]);
	}
}

std::vector<cv::Point> Detector::getAllCoordinates(std::vector<Face> vectorFaces)
{
	vector<Point> allCoordinates;
	for (int i = 0; i < vectorFaces.size(); i++)
	{
		vector<Point> facesPoints = vectorFaces[i].getCoordinates();
		vector<Point> eyesPoints = vectorFaces[i].getEyesCoordinates();
		vector<Point> mouthsPoints = vectorFaces[i].getMouthCoordinates();
		allCoordinates.insert(allCoordinates.end(), facesPoints.begin(), facesPoints.end());
		allCoordinates.insert(allCoordinates.end(), eyesPoints.begin(), eyesPoints.end());
		allCoordinates.insert(allCoordinates.end(), mouthsPoints.begin(), mouthsPoints.end());
	}
	return allCoordinates;
}

void Detector::setImage(std::filesystem::path fileNamePath)
{
	string stringFileNamePath = fileNamePath.string();
	image = imread(stringFileNamePath);
}

cv::Mat Detector::getImage()
{
	return image;
}

vector<Face> Detector::getVectorOfFaces()
{
	return faces;
}

void Detector::saveFaces(std::filesystem::path folderPath, string fileName)
{
	for (auto& face : faces)
		face.saveFace(folderPath, fileName);
}

vector<Rect> Detector::detectFaces()
{
	vector <Rect> foundedFaces;
	CascadeClassifier face_cascade;
	face_cascade.load("haarcascade_frontalface_alt.xml");
	face_cascade.detectMultiScale(image, foundedFaces);
	return foundedFaces;
}

Detector::Detector()
{
}


Detector::~Detector()
{
}
