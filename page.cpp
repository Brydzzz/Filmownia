#include "page.h"

#include <cstdlib>

#include "databaseManager.h"
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
    checkForCinFail(u, 1);
    return;
}

void checkForCinFail(int &answer, int restoreValue = 0) {
    if (std::cin.fail()) {
        std::cin.clear();  // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n');  // Ignore remaining input
        std::cout << "Invalid input. Please enter a number." << std::endl;
        answer = restoreValue;  // Reset 'a' to ensure the loop continues
    }
}

std::vector<Film *> findMovies(std::string title) {
    DatabaseManager db_mgmt;
    std::vector<Film *> found = db_mgmt.movieSearch(title);
    return found;
}

Film *chooseMovie(std::vector<Film *> films) {
    Film *f;
    if (films.size() == 0) {
        std::cout << "Movie not found" << std::endl;
        return nullptr;
    } else {
        int i = 1;
        for (auto f : films) {
            if (i <= 10) {
                std::cout << i << '.' << f->getTitle() << std::endl;
                ++i;
            }
        }
        int a = 0;
        while (a < 1 || a > 10 || a > films.size()) {
            cppIO::input(
                "Choose number of a movie you wish to choose or -1 to exit "
                "action: ",
                a);
            checkForCinFail(a);
            f = films[a - 1];
            if (a == -1) {
                return nullptr;
            }
        }
    }
    return f;
}
