#pragma once
#include <iostream>
#include<opencv2/opencv.hpp>

typedef std::vector<cv::Point>(*importFunction)(std::string, std::filesystem::path folderPath);

importFunction getImportFunctionName();