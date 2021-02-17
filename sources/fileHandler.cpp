#include "fileHandler.h"

bool fileHandler::openFile(std::string fileName) {
	file.open(fileName);
	if (file.is_open())
	{
		return true;
	}

	return false;
}

bool fileHandler::createFile(std::string fileName) {
	std::ofstream outFile(fileName);
	outFile.close();
	return true;
}

void fileHandler::closeFile() {
	file.close();
}

bool fileHandler::removeFile(const char * fileName) {
	if (file.is_open())
	{
		fileHandler::closeFile();
	}
	try
	{
		std::remove(fileName);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
}

bool fileHandler::readFile(std::string fileName, std::string & content) {
	try
	{
		content = "";
		//Variable for containing a single line of the file
		std::string line;

		file = std::fstream(fileName);

		//Reading the file
		while (std::getline(file, line))
		{
			content += line + "\n";
		}

		file.close();
		return true;

	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool fileHandler::writeFile(std::string fileName, std::string content) {
	//Open and create the file
	if (fileHandler::openFile(fileName)) {
		//Write to the file
		file << content;
		return true;
	}
	else
	{
		fileHandler::createFile(fileName);
		file = std::fstream(fileName);

		file << content;
		return true;
	}

	return false;
}

bool fileHandler::createDir(const char* path) {
	return _mkdir(path) ? true : false;
}