#include "Headers.h"

#pragma once

class FileSize {
public:

    FileSize(const std::string& path);
    std::string stream_size();
    std::string directory_size();

private:
    
    std::string unit(int val);
    std::ifstream m_stream;
    std::string m_path;
    
};
