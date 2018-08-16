#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "detectFaces.h"
#include "Face.h"
#include "JsonWriter.h"
#include "Detector.h"
#include <filesystem>

using namespace std;
using namespace cv;

vector<Point> detectFaces(string fileName, std::filesystem::path fileNamePath)
{
	Detector detector;
	detector.setImage(fileNamePath);
	vector<Rect> foundedFaces = detector.detectFaces();
	detector.setFaces(foundedFaces, fileName);
	detector.detectEyes();
	detector.detectMouth();
	vector<Face> facesVector = detector.getVectorOfFaces();
	detector.saveFaces(fileNamePath, fileName);
	detector.convertFaceMembersCoordinatesFromRoiToImage();
	JsonWriter writer;
	writer.writeFacesInJson(facesVector, fileNamePath, fileName);
	getInformation(fileName, facesVector);
	return detector.getAllCoordinates(detector.getVectorOfFaces());
}

void getInformation(string fileName, vector<Face> vectorFaces)
{
	cout << "----------------------------------------" << endl;
	cout << "The process of finding faces was completed" << endl;
	cout << "FileName: " << fileName << endl;
	cout << "There are " << vectorFaces.size() << " faces on this image" << endl;
	cout << "----------------------------------------" << endl;
}
