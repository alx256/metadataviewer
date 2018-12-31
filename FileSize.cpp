#include "FileSize.h"

#include <fstream>
#include <iomanip>
#include <sstream>

#include <boost/filesystem.hpp>

FileSize::FileSize(const std::string& path): m_stream(path, std::ifstream::ate | std::ifstream::binary), m_path(path) {}

std::string FileSize::stream_size() { return (m_stream.tellg() != -1) ? unit(m_stream.tellg()) : "NON EXISTENT"; }

std::string FileSize::directory_size() {
	
	size_t size;
	
	for (boost::filesystem::recursive_directory_iterator rdi(m_path);
	rdi != boost::filesystem::recursive_directory_iterator();
	++rdi) {
		if (!boost::filesystem::is_directory(*rdi))
		size += boost::filesystem::file_size(*rdi);
	}
	
	return unit(size);

}

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