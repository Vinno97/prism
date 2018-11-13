#pragma once
#include <string>
#include <fstream>

namespace Util {
	class FileReader
	{
	public:
		FileReader() = default;
		~FileReader() = default;
		std::ifstream readResourceIntoStream(std::string path) const;
		std::string readResourceFileIntoString(std::string path) const;
		void saveStringIntoResource(std::string path, std::string data) const;
	};
}
