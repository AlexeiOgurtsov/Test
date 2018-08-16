#include<opencv2/opencv.hpp>
#include "Face.h"
#include<filesystem>

extern "C" __declspec(dllexport) std::vector<cv::Point> detectFaces(std::string fileName,
	std::filesystem::path fileNamePath);
void getInformation(std::string fileName, std::vector<Face> vectorFaces);