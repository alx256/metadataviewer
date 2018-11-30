#include "FileType.h"

typedef std::vector<std::pair<std::string, std::string>> extensionVect;

struct Extensions {

    extensionVect images = {
        std::make_pair<std::string, std::string>(".jpg", "JPEG"),
        std::make_pair<std::string, std::string>(".png", "PNG")
    };

    extensionVect archives = {
        std::make_pair<std::string, std::string>(".tar.gz", "TAR"),
        std::make_pair<std::string, std::string>(".zip", "ZIP")
    };

    extensionVect plainText = {
        std::make_pair<std::string, std::string>(".txt", "Plain Text")
    };

};

std::string* FileType::identifyExtension(std::pair<std::string, std::string>& pair) {

    m_check = m_path.find(pair.first);

    if (m_check != std::string::npos && m_check == m_path.size() - pair.first.size()) {
        return &pair.second;
    } else {
        return nullptr;
    }

}

std::string FileType::fileType() {

    Extensions typeContainer;

    for (std::pair<std::string, std::string> y : typeContainer.images)  
    { if(identifyExtension(y) != nullptr) return *identifyExtension(y) + " Image"; }
    
    for (std::pair<std::string, std::string> y : typeContainer.archives) 
    { if(identifyExtension(y) != nullptr) return *identifyExtension(y) + " Archive"; }
    
    for (std::pair<std::string, std::string> y : typeContainer.plainText) 
    { if(identifyExtension(y) != nullptr) return *identifyExtension(y) + " File"; }

    return "Unknown Filetype";

}

FileType::FileType(std::string path): m_path(path) { }