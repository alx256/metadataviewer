#include "FileSize.h"

#include <fstream>

FileSize::FileSize(const std::string& path): m_stream(path, std::ifstream::ate | std::ifstream::binary) {}

std::string FileSize::streamSize() { return std::to_string(m_stream.tellg()); }