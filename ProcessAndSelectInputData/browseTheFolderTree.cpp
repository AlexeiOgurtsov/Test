#include "browseTheFolderTree.h"
#include <iostream>
#include "ThreadPool.h"
#include "getImportFunctionName.h"
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void browseTheFolderTree(std::filesystem::path folderPath, unsigned numberOfWorkers)
{
		ThreadPool pool(numberOfWorkers);
		pool.init();
		for (auto & fileOrFolder : std::filesystem::directory_iterator(folderPath))
		{
			if (is_directory(fileOrFolder))
			{
				browseTheFolderTree(fileOrFolder.path(), numberOfWorkers);
			}				
			else
			{
				string fileName = fileOrFolder.path().filename().string();
				string fileOrFolderString = fileOrFolder.path().string();
				//importFunction functionName = getImportFunctionName();
				//functionName(fileName, fileOrFolderString);
				pool.submit(getImportFunctionName(), fileName, fileOrFolderString);
			}
		}
		pool.shutdown();
}
