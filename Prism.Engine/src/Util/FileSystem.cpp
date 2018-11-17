#include "Util/FileSystem.h"
#include <streambuf>

#ifdef _MSC_VER
#include <filesystem>
#else

#include <experimental/filesystem>

#endif

#include <iostream>
#include <sstream>

using namespace std;
using namespace std::experimental;

namespace Util {

    std::ifstream FileSystem::readResourceIntoStream(const std::string &path) const {
        auto pwd = filesystem::current_path();

        auto filepath = pwd.concat("/res/").concat(path);

        auto file = std::ifstream(filepath);
        if (!file) {
            std::cout << "Resource file could not be opened: " << filepath << std::endl;
            throw std::runtime_error("Resource file could not be opened");
        }

        return file;
    }

    std::string FileSystem::readResourceFileIntoString(const std::string &path) const {
        auto file = readResourceIntoStream(path);

        std::string str((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

        return str;
    }

    void FileSystem::saveStringIntoResource(const std::string &path, const std::string &data) const {
        std::stringstream stream;
        stream << data;

        auto pwd = filesystem::current_path();

        auto filepath = pwd.concat("/res").concat(path);

        std::fstream outfile(filepath);
        outfile << data;
        outfile.close();
    }
}
