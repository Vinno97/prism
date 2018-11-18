#pragma once
#include <string>
#include <fstream>

namespace Util {
	class FileSystem
	{
	public:
		FileSystem() = default;
		~FileSystem() = default;
		std::ifstream readResourceIntoStream(const std::string &path) const;
		std::string readResourceFileIntoString(const std::string &path) const;
		void saveStringIntoResource(const std::string &path, const std::string &data) const;
	};
}