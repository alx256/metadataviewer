#include "FileInformationGeneral.h"
#include "FileSize.h"

#include <vector>
#include <algorithm>

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define PLAT_WIN
#endif

std::vector<std::string> flags;

bool flag_passed(std::string flg) {

    if (std::find(std::begin(flags), std::end(flags), flg) != std::end(flags))
        return true;    
    
    return false;
}

int main(int argc, const char ** argv) {

    std::string file;
    std::vector<std::string> flags_args, possible_flags_strings = {"-recursive", "-ignore"};
    std::vector<char> possible_flags_chars = {'r', 'i'};
    
    //=============================== Empty Check ===========================
    if (argc == 1) {
        std::cerr << "Error: Invalid arguments\n";
        return EXIT_FAILURE;
    } else {
        file = std::string(argv[argc - 1]);
    }
    
    if (argc > 2) {
        for (int i = 2; i <= argc - 1; ++i)
            flags_args.push_back(argv[i - 1]);
    }
    
    for (std::string y : flags_args) { 
        if (y[0] != '-') {
            std::cerr << "Error: Invalid flag '" << y << "'\n";
            return EXIT_FAILURE;
        }
        
        y.erase(0, 1);
        
        if (std::find(std::begin(possible_flags_strings), std::end(possible_flags_strings), y) == std::end(possible_flags_strings)) {
            for (char x : y) {
                if (std::find(std::begin(possible_flags_chars), std::end(possible_flags_chars), x) == std::end(possible_flags_chars)) {
                    std::cerr << "Error: Invalid flag '-" << y << "'\n";
                    return EXIT_FAILURE;
                } else {
                    flags.push_back("-" + std::string(1, x));
                }
            }
        } else {
            flags.push_back("-" + y); 
        }
    }
    
    //=============================== Exists Check ==========================
    FileSize fs(file);
    if (fs.stream_size() == "NON EXISTENT") {
    	std::cerr << "Error: File or directory does not exist\n";
	return EXIT_FAILURE;
    }
    //=========================== Directory Check ===========================
    FileInformationGeneral fig(file);
    
    #ifndef PLAT_WIN
    if (fig.file_type() == "Directory" && !(flag_passed("-i") || flag_passed("--ignore") || flag_passed("-r") || flag_passed("--recursive")))
    std::cout << 
    "\x1B[33mWarning: Directory size will not be calculated because it can take some time with larger directories." <<
    "If you want the size to be calculated, please pass the flag '-r' or '--recursive' or use the flag '-i' or '--ignore' to silence this warning.\x1B[0m" <<
    '\n';
    #else
    if (fig.file_type() == "Directory" && !(flag_passed("-i") || flag_passed("--ignore")))
    std::cout << 
    "Warning: Directory size will not be calculated because it can take some time with larger directories." <<
    "If you want the size to be calculated, please pass the flaf '-r' or '--recursive' or use the flag '-i' or '--ignore' to silence this warning." <<
    '\n';
    #endif
    
    //=============================== File Type =============================    
    std::cout << "Type: " << fig.file_type() << "\n\n";
    //============================= File Last Opened ========================
    std::cout << "Date Last Modified: " << fig.last_opened_date() << '\n';
    
    //============================== Permissions ============================
    std::cout << "Permissions: " << fig.permissions() << '\n';
    
    //=============================== File Size =============================
    if (fig.file_type() != "Directory") {
        std::cout << "Size: " << fs.stream_size() << '\n';
    } else if (flag_passed("-r") || flag_passed("--recursive")) {
        std::cout << "Size: " << fs.directory_size() << "\n";
    } else {
        std::cout << "Size: Not Calculated" << '\n';
    }
}
