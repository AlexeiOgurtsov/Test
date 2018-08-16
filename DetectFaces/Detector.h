#ifndef Detector_HEADER
#define Detector_HEADER

#include<opencv2/opencv.hpp>
#include "Face.h"
#include <filesystem>

class Detector
{
private:
	cv::Mat image;
	std::vector<Face> faces;
	cv::Mat makeARoi(Face face, cv::Mat image, float coefficient);
public:
	void setFaces(std::vector<cv::Rect> foundedFaces, std::string fileName);
	void setImage(std::filesystem::path fileNamePath);
	cv::Mat getImage();
	std::vector<cv::Rect> detectFaces();
	void detectEyes();
	void makeFacesCoordinates();
	void convertFaceMembersCoordinatesFromRoiToImage();
	void detectMouth();	
	std::vector<cv::Point> getAllCoordinates(std::vector<Face> vectorFaces);
	std::vector<Face> getVectorOfFaces();
	void saveFaces(std::filesystem::path fileNamePath, std::string fileName);
	Detector();
	~Detector();
};
#endif
