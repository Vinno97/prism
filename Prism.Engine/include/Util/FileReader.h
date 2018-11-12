#pragma once
#include <string>
#include <fstream>

namespace Util {
	class FileReader
	{
	public:
		FileReader();
		std::ifstream readResourceIntoStream(std::string path) const;
		std::string readResourceFileIntoString(std::string path) const;
		~FileReader();
	};
}
