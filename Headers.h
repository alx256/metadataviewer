#include <iostream>
#include <string>
#include <fstream>

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define PLAT_WIN
#endif