#include "FileSize.h"

#include <fstream>
#include <iomanip>
#include <sstream>

FileSize::FileSize(const std::string& path): m_stream(path, std::ifstream::ate | std::ifstream::binary) {}

std::string FileSize::stream_size() { return (m_stream.tellg() != -1) ? unit(m_stream.tellg()) : "NON EXISTENT"; }

std::string FileSize::unit(int val) {
	
	long double cal = 1000;	
	std::stringstream fin;
	fin << std::fixed;
	fin << std::setprecision(1);
	
	if (val < cal)
	
		fin << val << " Bytes";
		
	else if (val < (cal * 1000))
		
		fin << val / cal << " Kilobytes";
		
	else if (val < (cal * 1000 * 1000)) 
		
		fin << val / (cal * 1000) << " Megabytes";
		
	else if (val < (cal * 1000 * 1000 * 1000))
		
		fin << val / (cal * 1000 * 1000) << " Gigabytes";
		
	else if (val < (cal * 1000 * 1000 * 1000 * 1000))
	
		fin << val / (cal * 1000 * 1000 * 1000) << " Terabytes";
	
	return fin.str();	
}