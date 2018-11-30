#include "FileType.h"
#include "FileSize.h"

int main(int argc, const char ** argv) {

    std::string file;

    //=============================== Empty Check ===============================
    if (argc == 1) {
        
        std::cerr << "Error: Invalid arguments\n";
        return EXIT_FAILURE;

    } else {

        file = std::string(argv[1]);

    }

    //=============================== File Type ===============================
    
    FileType ft(file);
    std::cout << ft.fileType() << '\n';
    std::cout << "\n\n";

    //=========================================================================
    //=============================== File Size ===============================

    FileSize fs(file);
    std::cout << fs.streamSize() << '\n';

}