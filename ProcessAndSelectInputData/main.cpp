#include "browseTheFolderTree.h"

int main(int argc, char* argv[])
{
	std::string stringFolderPath = argv[1];
	std::filesystem::path folderPath = stringFolderPath;
	folderPath.u8string();
	unsigned numberOfWorkers = std::stoul(argv[2]);
	browseTheFolderTree(folderPath, numberOfWorkers);
	system("pause");
	return 0;
}

