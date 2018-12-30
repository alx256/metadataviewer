#include <map>
#include <vector>

struct Extensions {
    using format_map = std::map<std::string, std::string>;
    
    std::vector<std::pair<format_map, std::string>> format;
    
    Extensions() {
        format_map images; 
        images[".jpg"] 				= "JPEG";
        images[".png"] 				= "PNG";
        images[".tiff"]				= "TIFF";
        images[".gif"]				= "GIF";
        format.push_back(std::make_pair(images, "Image"));
        
        format_map archives;
        archives[".gz"]				= "GZIP";
        archives[".xz"]				= "XZIP";
        archives[".bz"]				= "BZIP";
        archives[".zip"]			= "ZIP";
        format.push_back(std::make_pair(archives, "Archive"));
        
        format_map plain_text;
        plain_text[".txt"]			= "Plain Text";
        format.push_back(std::make_pair(plain_text, "File"));
        
        format_map programming_files_source;
        programming_files_source[".c"]		= "C";
        programming_files_source[".cpp"]	= "C++";
        programming_files_source[".py"]		= "Python";
        format.push_back(std::make_pair(programming_files_source, "Source"));
        
        format_map programming_files_header;
        programming_files_header[".h"]		= "C";
        programming_files_header[".hpp"]	= "C/C++";
        format.push_back(std::make_pair(programming_files_header, "Header"));
    }
};