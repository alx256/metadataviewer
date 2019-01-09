#include "FileInformationGeneral.h"
#include "FileSize.h"

#include <vector>
#include <algorithm>

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define PLAT_WIN
#endif

#include <boost/filesystem.hpp>

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

        // NOTE: Currently coloured text is set to only support Unix terminals. 
        // TODO: Add Windows coloured text support

        //=============================== Empty Check ===========================
        if (argc == 1) {
                #ifndef PLAT_WIN
                std::cerr << "\x1B[31mError: Invalid arguments\x1B[1m\n";
                #else
                std::cerr << "Error: Invalid arguments\n";
                #endif
                return EXIT_FAILURE;
        } else {
                file = std::string(argv[argc - 1]);
        }
        //=============================== Flag Setup ===========================
        if (argc > 2) {
                for (int i = 2; i <= argc - 1; ++i)
                        flags_args.push_back(argv[i - 1]);
        }

        for (std::string y : flags_args) { 
                if (y[0] != '-') {
                        #ifndef PLAT_WIN
                        std::cerr << "\x1B[31mError: Invalid flag '" << y << "'\x1B[0m\n";
                        #else
                        std::cerr << "Error: Invalid flag '" << y << "'\n";
                        #endif
                        return EXIT_FAILURE;
        }

        y.erase(0, 1);

        if (std::find(std::begin(possible_flags_strings), std::end(possible_flags_strings), y) == std::end(possible_flags_strings)) {
                for (char x : y) {
                        if (std::find(std::begin(possible_flags_chars), std::end(possible_flags_chars), x) == std::end(possible_flags_chars)) {
                                #ifndef PLAT_WIN
                                std::cerr << "\x1B[31mError: Invalid flag '" << y << "'\x1B[0m\n";
                                #else
                                std::cerr << "Error: Invalid flag '" << y << "'\n";
                                #endif
                                return EXIT_FAILURE;
                        } else {
                                flags.push_back("-" + std::string(1, x));
                        }
                }
        } else {
                        flags.push_back("-" + y); 
                }
        }
        
        //=============================== Variable Setup ========================
        FileInformationGeneral fig(file);
        FileSize fs(file);

        if (!boost::filesystem::exists(file)) {
                #ifndef PLAT_WIN
                std::cout << "\x1B[31mError: File or Directory does not exist\x1B[0m\n";
                #else
                std::cout << "Error: File or Directory does not exist\n";
                #endif
                return EXIT_FAILURE;
        }

        std::string type = fig.file_type(), lod = fig.last_opened_date(), perms = fig.permissions(), size;

        if (type == "Directory")
                if (flag_passed("-r") || flag_passed("--recursive"))
                        size = fs.directory_size();
                else
                        size = "Not Calculated";
        else
                size = fs.file_size();
        //=========================== Directory Warning ===========================
        #ifndef PLAT_WIN
        if (type == "Directory" && !(flag_passed("-i") || flag_passed("--ignore") || flag_passed("-r") || flag_passed("--recursive")))
        std::cout << 
        "\x1B[33mWarning: Directory size will not be calculated because it can take some time with larger directories." <<
        " If you want the size to be calculated, please pass the flag '-r' or '--recursive' or use the flag '-i' or '--ignore' to silence this warning.\x1B[0m" <<
        '\n';
        #else
        if (type == "Directory" && !(flag_passed("-i") || flag_passed("--ignore")))
        std::cout << 
        "Warning: Directory size will not be calculated because it can take some time with larger directories." <<
        " If you want the size to be calculated, please pass the flag '-r' or '--recursive' or use the flag '-i' or '--ignore' to silence this warning." <<
        '\n';
        #endif

        if ((flag_passed("-r") || flag_passed("--recursive")) && size == "perm_denied") {
                #ifndef PLAT_WIN
                std::cerr << "\x1B[31mError: Ecountered Permssion Denied while calculating file size\n" <<
                "Please try running as root\x1B[0m\n"; 
                #else
                std::cer << "Error: Encountered Permission Denied while calculating file size\n" <<
                "Please try running as root\n";
                #endif
                return EXIT_FAILURE;
        }
        //=============================== File Type =============================    
        std::cout << "Type: " << type << '\n';
        //============================= File Last Opened ========================
        std::cout << "Date Last Modified: " << lod << '\n';
        //============================== Permissions ============================
        std::cout << "Permissions: " << perms << '\n';
        //=============================== File Size =============================
        std::cout << "Size: " << size << '\n';

}
