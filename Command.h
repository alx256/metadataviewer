#pragma once

#include <string>
#include <iostream>
#include <sstream>

class Command_Exception {
public:
        std::string value;
        std::string type;

        #ifdef PLAT_WIN
        std::string get_type() {
                if (type == "error") {
                        return "Error: ";
                } else if (type == "warning") {
                        return "Warning: ";
                } else {
                        return "";
                }
        }
        #else
        std::string get_type() {
                if (type == "error") {
                        return "\x1B[31mError: ";
                } else if (type == "warning") {
                        return "\x1B[33mWarning: ";
                } else {
                        return "";
                }
        }
        #endif

        std::string get_value()  { return value; }
        #ifndef PLAT_WIN
        void report()    { std::cerr << get_type() << value << "\x1B[0m\n"; }
        #else
        void report()    { std::cerr << get_type() << value << "\n"; }
        #endif

        Command_Exception(std::string raw, std::string exception_type): 
        value(raw), type(exception_type) {}

        Command_Exception() {}

};

struct Command_Exception_Presets {
        
        Command_Exception exception_non_existent_error  = Command_Exception("File or directory does not exist", "error");
        Command_Exception exception_permisssion_denied_error = Command_Exception(
                "Encountered Permission Denied while calculating file size.\nPlease try running as root", "error"
        );
        Command_Exception exception_invalid_arguments_error = Command_Exception("Invalid Arguments", "error");

        Command_Exception exception_directory_warning = Command_Exception();

        Command_Exception exception_help_message = Command_Exception();

        Command_Exception_Presets() {
                directory_war << "Directory size will not be calculated because it can take some time with larger directories.\n"
                << "If you want the size to be calculated, please pass the flag '-r' or '--recursive' or use the flag '-i' or '--ignore' to silence this warning.";

                help_mess <<
                "Usage: MetaData [File1] [...]  Gives information about a file\n\n" <<
                "-r / --recursive               Runs recursive search through directories\n" <<
                "-i / --ignore                  Ignores warnings";

                exception_directory_warning = Command_Exception(directory_war.str(), "warning");
                exception_help_message = Command_Exception(help_mess.str(), "message");

        }

        void exception_flags_error(std::string flag) {
                Command_Exception("Invalid flag '" + flag + '\'', "error").report();
        }

        private:
        std::stringstream directory_war;
        std::stringstream help_mess;

};

class Command {

        void help_message();

};