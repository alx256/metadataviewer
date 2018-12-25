#include "FileSize.h"

#include <fstream>

FileSize::FileSize(const std::string& path): m_stream(path, std::ifstream::ate | std::ifstream::binary) {}

std::string FileSize::stream_size() { return (m_stream.tellg() != -1) ? unit(m_stream.tellg()) : "NON EXISTENT"; }

std::string FileSize::unit(int val) {

	// TO DO: Implement some fancy byte display unit thingy.

	return std::to_string(val);

}
