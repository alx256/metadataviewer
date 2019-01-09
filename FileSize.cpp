#include "FileSize.h"

#include <fstream>
#include <iomanip>
#include <sstream>

#include <boost/filesystem.hpp>

FileSize::FileSize(const std::string& path): m_path(path) {}

std::string FileSize::file_size() { 
	
	if (boost::filesystem::is_directory(m_path)) {
		return "DIRECTORY";
	} else {
		if (!boost::filesystem::exists(m_path)) {
			return "NON EXISTENT";	
		} else {
			return unit(boost::filesystem::file_size(m_path));
		}
	}
	 
}

std::string FileSize::directory_size() {
	
	size_t size = 0u;
        boost::filesystem::path pth(m_path);
	try {
		for (auto const& file : boost::filesystem::recursive_directory_iterator(pth)) {
                        if (boost::filesystem::is_regular_file(file)) size += boost::filesystem::file_size(file);
                }
        } catch (const boost::filesystem::filesystem_error& ex) {
		if((std::string(ex.what()).find("Permission denied") != std::string::npos) ||
		std::string(ex.what()).find("Operation not permitted") != std::string::npos) {
			return "perm_denied";
		}
	}
	
	return unit(size);
	
}

std::string FileSize::unit(size_t val) {
	
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