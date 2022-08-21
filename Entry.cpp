#include "Headers.h"
#include "FileInformationGeneral.h"
#include "FileSize.h"
#include "Command.h"

#include <vector>
#include <algorithm>
#include <sstream>

#include <boost/filesystem.hpp>

std::vector<std::string> flags, flags_args;

inline bool flag_passed(std::string flg) { 
        return (std::find(std::begin(flags), std::end(flags), flg) != std::end(flags)) ? true : false; 
}

int setup_flags(Command_Exception_Presets pres) {
        std::vector<std::string> possible_flags_strings = {"-recursive", "-ignore", "-help"};
        std::vector<char> possible_flags_chars = {'r', 'i'};

        for (std::string y : flags_args) { 
                if (y[0] != '-') {
                        pres.exception_flags_error(y);
                        return EXIT_FAILURE;
                }
        }

        for (std::string y : flags_args) { 
                if (y[0] != '-') {
                        pres.exception_flags_error(y);
                        return EXIT_FAILURE;
                
                }

                y.erase(0, 1);

                if (std::find(std::begin(possible_flags_strings), std::end(possible_flags_strings), y) == std::end(possible_flags_strings)) {
                        for (char x : y) {
                                if (std::find(std::begin(possible_flags_chars), std::end(possible_flags_chars), x) == std::end(possible_flags_chars)) {
                                        pres.exception_flags_error(y);
                                        return EXIT_FAILURE;
                                } else {
                                        flags.push_back("-" + std::string(1, x));
                                }
                        }
                } else {
                        flags.push_back("-" + y); 
                }
        }
}

int main(int argc, const char ** argv) {

        std::vector<std::string> files;
        // std::string file;
        std::vector<std::string> single_flags = {"--help"};
        bool flags_used;
        Command_Exception_Presets pres;

        // NOTE: Currently coloured text is set to only support Unix terminals. 
        // TODO: Add Windows coloured text support

        //=============================== Empty Check ===========================
        if (argc == 1) {
                pres.exception_invalid_arguments_error.report();
                pres.exception_help_message.report();
                return EXIT_FAILURE;
        } else {
                if (argc > 1) {
                        flags_used = (argv[1][0] == '-') ? true : false;

                        for (int i = (flags_used) ? 2 : 1; i <= argc - 1; ++i)
                                files.push_back(std::string(argv[i]));
                }
        }

        //=============================== Flag Setup ===========================
        if (argc > 2 && flags_used) {
                for (int i = 2; i <= argc - 1; ++i)
                        flags_args.push_back(argv[i - 1]);
        } else {
                if (argv[1][0] == '-') {
                        setup_flags(pres);

                        for (std::string y : single_flags) {
                                if (std::string(argv[argc - 1]).find(y) != std::string::npos) {
                                        pres.exception_help_message.report();
                                        return EXIT_SUCCESS;
                                } else {
                                        pres.exception_flags_error(std::string(argv[argc - 1]));
                                        return EXIT_FAILURE;
                                }
                        }
                } else {
                        setup_flags(pres);
                }
        }
        //=============================== Variable Setup ========================
        for (std::string file : files) {
                FileInformationGeneral fig(file);
                FileSize fs(file);

                if (!boost::filesystem::exists(file)) {
                        pres.exception_non_existent_error.report();
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
                if (!(flag_passed("-r") || flag_passed("-i") || flag_passed("--recursive") || flag_passed("--ignore")) 
                && boost::filesystem::is_directory(file))
                        pres.exception_directory_warning.report();

                if ((flag_passed("-r") || flag_passed("--recursive")) && size == "perm_denied") {
                        pres.exception_permisssion_denied_error.report();
                        return EXIT_FAILURE;
                }

                //============================== File Name ==============================
                std::cout << file << '\n';
                //=============================== File Type =============================    
                std::cout << "Type: " << type << '\n';
                //============================= File Last Modified ======================
                std::cout << "Date Last Modified: " << lod << '\n';
                //============================== Permissions ============================
                std::cout << "Permissions: " << perms << '\n';
                //=============================== File Size =============================
                std::cout << "Size: " << size << '\n';
                
        }

}
