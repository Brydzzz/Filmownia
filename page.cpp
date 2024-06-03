#include "page.h"

#include <cstdlib>
void clearTerminal() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
