#include "FileInformationGeneral.h"
#include "Extensions.h"

#include <boost/filesystem.hpp>
#include <ctime>

#include <sys/stat.h>
#include <sys/types.h>

#ifndef PLAT_WIN
#include <unistd.h>
#endif

#ifdef PLAT_WIN
#define stat _stat
#endif

struct stat st;

std::string FileInformationGeneral::file_type() {

        using file_pair = std::pair<std::string, std::string>;
    
        Extensions type_container;

        if (boost::filesystem::is_directory(m_path)) return "Directory";
    
        for (auto y : type_container.format)
                for (auto x : y.first)
                        if (boost::filesystem::extension(m_path) == x.first)
                                return x.second + ' ' + y.second;
    
        return "Unknown Filetype";

}

std::string FileInformationGeneral::permissions() {
    
        if (stat(m_path.c_str(), &st) == 0) {
                mode_t permissions = st.st_mode;
                std::string permissions_str;
        
                permissions_str += (permissions & S_IRUSR) ? 'r' : '-';
                permissions_str += (permissions & S_IWUSR) ? 'w' : '-';
                permissions_str += (permissions & S_IXUSR) ? 'x' : '-';
        
                permissions_str += (permissions & S_IRGRP) ? 'r' : '-';
                permissions_str += (permissions & S_IWGRP) ? 'w' : '-';
                permissions_str += (permissions & S_IXGRP) ? 'x' : '-';
                
                permissions_str += (permissions & S_IROTH) ? 'r' : '-';
                permissions_str += (permissions & S_IWOTH) ? 'w' : '-';
                permissions_str += (permissions & S_IXOTH) ? 'x' : '-';
                
                return permissions_str;
        }
    
}

std::string FileInformationGeneral::last_opened_date() {
    
        if (stat(m_path.c_str(), &st) == 0) {
                char date[10];
                strftime(date, 10, "%d/%m/%y", localtime(&(st.st_mtime)));
                return std::string(date);
        }
        
        return "Unkown";
    
}

FileInformationGeneral::FileInformationGeneral(std::string path): m_path(path) {}