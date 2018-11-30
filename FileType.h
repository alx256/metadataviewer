#pragma once

#include "Headers.h"

class FileType {
public:

    std::string fileType();
    FileType(std::string path);
    void print();

private:

    std::string m_path;
    std::vector<std::string> exts;
    std::string* identifyExtension(std::pair<std::string, std::string>& pair);
    size_t m_check;

};