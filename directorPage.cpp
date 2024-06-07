#include "directorPage.h"

#include "actorPage.h"
#include "databaseManager.h"
#include "global.h"
#include "page.h"
extern Film *findAndChooseMovie(std::string title);
program_state DirectorPage::nextAction() {
    std::string action;
    bool condition =
        std::find(options.begin(), options.end(), action) == options.end();
    while (condition) {
        cppIO::input("Enter desired action: ", action);
        condition =
            std::find(options.begin(), options.end(), action) == options.end();
        if (condition) {
            cppIO::log(
                "No such option available for this user. Chose one from the "
                "list.");
        }
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
        return program_state::SeeAll;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> DirectorPage::doAction(program_state act,
                                             std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::GoBack) {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    } else if (act == program_state::AddDirectorFilm) {
        DatabaseManager db_mgmt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string film;
        std::cout << "Movie: " << std::endl;
        std::getline(std::cin, film);
        Film *f = findAndChooseMovie(film);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<DirectorPage> ptr =
                std::make_unique<DirectorPage>(director);
            return ptr;
        }
        std::ostringstream os;
        os << director;
        std::string oldRecord = os.str();
        try {
            director.addFilm(*f);
        } catch (const std::invalid_argument &e) {
            std::cout << "Director already is already in this movie.\n";
            waitForInput();
            std::unique_ptr<DirectorPage> ptr =
                std::make_unique<DirectorPage>(director);
            return ptr;
        }
        os.str("");
        os << director;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::directorsDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        f->changeDirector(director.getName());
        os.str("");
        os << f;
        std::string newMovie = os.str();
        db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(director);
        return ptr;
    } else if (act == program_state::DeleteDirectorFilm) {
        // DatabaseManager db_mgmt;
        // std::string film;
        // std::cout << "Delete director from movie: " << std::endl;
        // std::cin.clear();
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // std::getline(std::cin, film);
        // Film *f = findAndChooseMovie(film);
        // if (f == nullptr)
        // {
        //     waitForInput();
        //     std::unique_ptr<DirectorPage> ptr =
        //     std::make_unique<DirectorPage>(director); return ptr;
        // }
        // std::ostringstream os;
        // os << director;
        // std::string oldRecord = os.str();
        // director.deleteFilm(*f);
        // os.str("");
        // os << director;
        // std::string newRecord = os.str();
        // db_mgmt.replaceLine(newRecord, oldRecord, whichDb::actorsDb);
        // os.str("");
        // os << f;
        // std::string oldMovie = os.str();
        // try
        // {
        //     f->(actor.getName());
        // }
        // catch (const std::invalid_argument &e)
        // {
        //     std::cout << "This actor never had a role in this movie in the "
        //                  "first place\n";
        //     waitForInput();
        //     std::unique_ptr<ActorPage> ptr =
        //     std::make_unique<ActorPage>(actor); return ptr;
        // }
        // os.str("");
        // os << f;
        // std::string newMovie = os.str();
        // db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        // std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
        // return ptr;
        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(director);
        return ptr;
    } else if (act == program_state::SeeAll) {
        clearTerminal();
        director.displayFilms(std::cout);

        waitForInput();

        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(director);
        return ptr;
    } else if (act == program_state::Exit) {
        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(director);
        return ptr;
    }
    std::unique_ptr<DirectorPage> ptr =
        std::make_unique<DirectorPage>(director);
    return ptr;
}

void DirectorPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "DIRECTOR PAGE" << std::endl;
    printBorder();
    director.displayDirectorInfo(std::cout);
}
