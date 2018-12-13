#pragma once
#include <string>
#include <fstream>
#include <vector>

namespace Util
{
	class FileSystem
	{
	public:
		FileSystem() = default;
		~FileSystem() = default;
		std::ifstream readResourceIntoStream(const std::string& path) const;
		std::string readResourceFileIntoString(const std::string& path) const;
		std::string getResourcePath(const std::string& path = std::string()) const;
		std::vector<std::string> getFilenamesInDirectory(const std::string& path = std::string()) const;
		void saveStringIntoResource(const std::string& path, const std::string& data) const;
	};
}
