#include "directorPage.h"

#include "databaseManager.h"
#include "page.h"
program_state DirectorPage::nextAction() {
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end()) {
        cppIO::input("Enter desired action: ", action);
    }
    if (action == "Exit") {
        return program_state::Exit;
    }
    if (action == "GoBack") {
        return program_state::GoBack;
    }
    if (action == "AddFilm") {
        return program_state::AddDirectorFilm;
    }
    if (action == "DeleteFilm") {
        return program_state::DeleteDirectorFilm;
    }
    if (action == "SeeAllFilms") {
        return program_state::SeeAllDirectorFilms;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> DirectorPage::doAction(program_state act,
                                          std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::GoBack) {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    } else if (act == program_state::AddDirectorFilm) {
        std::unique_ptr<DirectorPage> ptr = std::make_unique<DirectorPage>(director);
        return ptr;
    } else if (act == program_state::DeleteDirectorFilm) {
        std::unique_ptr<DirectorPage> ptr = std::make_unique<DirectorPage>(director);
        return ptr;
    } else if (act == program_state::SeeAllDirectorFilms) {
        clearTerminal();
        director.displayFilms(std::cout);

        // Pause until Enter is pressed
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        std::unique_ptr<DirectorPage> ptr = std::make_unique<DirectorPage>(director);
        return ptr;
    } else if (act == program_state::Exit) {
        std::unique_ptr<DirectorPage> ptr = std::make_unique<DirectorPage>(director);
        return ptr;
    }
    std::unique_ptr<DirectorPage> ptr = std::make_unique<DirectorPage>(director);
        return ptr;
}

void DirectorPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "DIRECTOR PAGE" << std::endl;
    printBorder();
    director.displayDirectorInfo(std::cout);
}
