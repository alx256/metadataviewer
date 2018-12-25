#include "FileType.h"

#include <map>
#include <boost/filesystem.hpp>

struct Extensions {

    std::map<std::string, std::string> images = {
        std::make_pair(".jpg", "JPEG"),
        std::make_pair(".png", "PNG")
    };

    std::map<std::string, std::string> archives = {
        std::make_pair(".tar.gz", "TAR"),
        std::make_pair(".zip", "ZIP")
    };

    std::map<std::string, std::string> plain_text = {
        std::make_pair(".txt", "Plain Text")
    };

};

std::string* FileType::identify_extension(std::pair<std::string, std::string>& pair) {

    if (boost::filesystem::extension(m_path) == pair.first) {
        return &pair.second;
    } else {
        return nullptr;
    }

}

std::string FileType::file_type() {

    Extensions type_container;
    
    if (!(boost::filesystem::is_regular_file(m_path))) return "Directory";
    
    for (std::pair<std::string, std::string> y : type_container.images)  
    { if(identify_extension(y) != nullptr) return *identify_extension(y) + " Image"; }
    
    for (std::pair<std::string, std::string> y : type_container.archives) 
    { if(identify_extension(y) != nullptr) return *identify_extension(y) + " Archive"; }
    
    for (std::pair<std::string, std::string> y : type_container.plain_text) 
    { if(identify_extension(y) != nullptr) return *identify_extension(y) + " File"; }

    return "Unknown Filetype";

}

FileType::FileType(std::string path): m_path(path) { }
