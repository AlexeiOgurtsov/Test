#pragma once
#include <windows.h>
#include <stdio.h>
#include "WinBase.h"
#include <iostream>
#include<opencv2/opencv.hpp>
#include<filesystem>

typedef std::vector<cv::Point>(*importFunction)(std::string, std::filesystem::path folderPath);

importFunction getImportFunctionName()
{
	importFunction detectFaces;
	HMODULE hDll = LoadLibrary("DetectFaces.dll");
	detectFaces = (importFunction)GetProcAddress(hDll, "detectFaces");
	return detectFaces;
}