#include "Headers.h"

#pragma once

class FileSize {
public:

    FileSize(const std::string& path);
    std::string streamSize();

private:

    std::ifstream m_stream;

};