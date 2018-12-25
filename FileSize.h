#include "Headers.h"

#pragma once

class FileSize {
public:

    FileSize(const std::string& path);
    std::string stream_size();

private:
    
    std::string unit(int val);
    std::ifstream m_stream;

};
