#include "Util/FileSystem.h"
#include <streambuf>
#include <windows.h>
#include <iostream>
#include <sstream>

namespace Util {
	std::ifstream FileReader::readResourceIntoStream(std::string path) const {
		char buf[256];
		GetCurrentDirectoryA(256, buf);
		std::string pwd = std::string(buf) + "/res/";

		//std::ifstream file{ pwd + path };
		auto file = std::ifstream(pwd + path);
		if (!file) {
			std::cout << "Resource file could not be opened: " << pwd + path << std::endl;
			throw std::exception("Resource file could not be opened");
		}

		return file;
	}
	std::string FileReader::readResourceFileIntoString(std::string path) const
	{
		auto file = readResourceIntoStream(path);

		std::string str((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		return str;
	}

	void FileReader::saveStringIntoResource(std::string path, std::string data) const
	{
		std::stringstream stream;
		stream << data;

		char buf[256];
		GetCurrentDirectoryA(256, buf);
		std::string pwd = std::string(buf) + "/res/";

		std::fstream outfile(pwd + path);
		outfile << data;
		outfile.close();
	}
}
