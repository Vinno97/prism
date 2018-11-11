#include "Util/FileReader.h"
#include <fstream>
#include <streambuf>
#ifdef _MSC_VER
#include <filesystem>
#else
#include <experimental/filesystem>
#endif
#include <iostream>

using namespace std;
using namespace std::experimental;

namespace Util {
	FileReader::FileReader() {}

	std::string FileReader::readResourceFileIntoString(std::string path) const {
		auto pwd = filesystem::current_path();

		auto filename = pwd.concat("/res").concat(path);

		std::ifstream file(filename);
		if (!file) {
			std::cout << "Resource file could not be opened: " << filename << std::endl;
			throw std::runtime_error("Resource file could not be opened");
		}

		std::string str((std::istreambuf_iterator<char>(file)),
						std::istreambuf_iterator<char>());

		return str;
	}

	FileReader::~FileReader() {}
} // namespace Util