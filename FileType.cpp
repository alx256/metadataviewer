#include "FileType.h"
#include "Extensions.h"

#include <boost/filesystem.hpp>

std::string FileType::file_type() {

    using file_pair = std::pair<std::string, std::string>;
    
    Extensions type_container;
    
    if (!(boost::filesystem::is_regular_file(m_path))) return "Directory";
    
    for (auto y : type_container.format)
        for (auto x : y.first)
            if (boost::filesystem::extension(m_path) == x.first)
                return x.second + ' ' + y.second;
    
    return "Unknown Filetype";

}

FileType::FileType(std::string path): m_path(path) {}