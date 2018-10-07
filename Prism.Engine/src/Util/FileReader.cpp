#include "Util/FileReader.h"
#include <fstream>
#include <streambuf>
#include <windows.h>
#include <iostream>

namespace Util {
	FileReader::FileReader()
	{
	}

	string FileReader::readResourceFileIntoString(string path)
	{
		char buf[256];
        GetCurrentDirectoryA(256, buf);
        string pwd = string(buf)+"/res";

		ifstream file(pwd+path);
		if (!file) {
			cout << "Resource file could not be opened: " << pwd + path << endl;
			throw exception("Resource file could not be opened");
		}

		string str((istreambuf_iterator<char>(file)),
					istreambuf_iterator<char>());

		return str;
	}


	FileReader::~FileReader()
	{
	}
}