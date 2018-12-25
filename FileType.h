#include "Headers.h"

#pragma once

class FileType {
public:

    std::string file_type();
    FileType(std::string path);
    void print();

private:

    std::string m_path;
    std::string* identify_extension(std::pair<std::string, std::string>& pair);

};
