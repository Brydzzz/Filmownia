#include "page.h"

#include <cstdlib>
void clearTerminal() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void printBorder() {
    { std::cout << "------------------------------" << std::endl; }
}

void waitForInput() {
    int u;
    cppIO::input("Press 1 to continue... ", u);
    return;
}
