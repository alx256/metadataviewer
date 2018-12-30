#include "Headers.h"
#include <map>

#pragma once

class FileType {
public:

    std::string file_type();
    FileType(std::string path);

private:

    std::string m_path;
    std::string* to_str(std::map<std::string, std::string> mp, std::string type);

};
