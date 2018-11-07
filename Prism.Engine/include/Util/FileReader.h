#pragma once
#include <string>

using namespace std;

namespace Util {
	class FileReader
	{
	public:
		FileReader();
		string readResourceFileIntoString(string path) const;
		~FileReader();
	};
}