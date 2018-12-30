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

    //=============================== Exists Check ============================
    FileSize fs(file);
    if (fs.stream_size() == "NON EXISTENT") {
    	std::cerr << "Error: File or directory does not exist\n";
	return EXIT_FAILURE;
    }
	
    //=============================== File Type ===============================    
    FileType ft(file);
    std::cout << "Type: " << ft.file_type() << "\n\n";

    //=============================== File Size ===============================
    std::cout << "Size: " << fs.stream_size() << '\n';

}
