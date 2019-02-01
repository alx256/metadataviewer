#include <map>

#pragma once

class FileInformationGeneral {
public:

        std::string file_type();
        std::string last_opened_date();
        std::string permissions();
        std::string preview(std::string file_type);
        bool exists();
        FileInformationGeneral(std::string path);

private:

        std::string m_path;

};
