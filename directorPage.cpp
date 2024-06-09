#include "directorPage.h"

#include "actorPage.h"
#include "databaseManager.h"
#include "global.h"
#include "page.h"

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
        if (filmLink != nullptr) {
            std::unique_ptr<FilmPage> ptr =
                std::make_unique<FilmPage>(filmLink);
            return ptr;
        } else {
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    } else if (act == program_state::AddDirectorFilm) {
        DatabaseManager db_mgmt;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string title;
        std::cout << "Movie: " << std::endl;
        std::getline(std::cin, title);
        std::vector<Film *> foundFilms = findMovies(title);
        Film *f = chooseMovie(foundFilms);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<DirectorPage> ptr =
                std::make_unique<DirectorPage>(director, filmLink);
            return ptr;
        }
        std::ostringstream os;
        // std::string old_dir_name = f->getDir();
        // std::vector<Director> found_director =
        //     db_mgmt.personSearch<Director>(old_dir_name);
        // Director old_director = found_director[0];
        // std::ostringstream os;

        // if (found_director.size() > 0) {
        //     os << old_director;
        //     std::string oldRecord = os.str();
        //     old_director.deleteFilm(*f);
        //     os.str("");
        //     os << old_director;
        //     std::string newRecord = os.str();
        //     db_mgmt.replaceLine(newRecord, oldRecord, whichDb::directorsDb);
        //     os.clear();
        // }
        os << director;
        std::string oldRecord = os.str();
        try {
            director.addFilm(*f);
        } catch (const std::invalid_argument &e) {
            std::cout << "This director is already in this movie.\n";
            waitForInput();
            std::unique_ptr<DirectorPage> ptr =
                std::make_unique<DirectorPage>(director, filmLink);
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
            std::make_unique<DirectorPage>(director, filmLink);
        return ptr;

    } else if (act == program_state::DeleteDirectorFilm) {
        DatabaseManager db_mgmt;
        std::string title;
        std::cout << "Delete director from movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, title);
        std::vector<Film *> foundFilms = director.findFilmsByTitle(title);
        Film *f = chooseMovie(foundFilms);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<DirectorPage> ptr =
                std::make_unique<DirectorPage>(director, filmLink);
            return ptr;
        }
        std::ostringstream os;
        os << director;
        std::string oldRecord = os.str();
        try {
            director.deleteFilm(*f);
        } catch (const std::invalid_argument &e) {
            std::cout << "This director was never in this movie in the "
                         "first place\n";
            waitForInput();
            std::unique_ptr<DirectorPage> ptr =
                std::make_unique<DirectorPage>(director, filmLink);
            return ptr;
        }
        os.str("");
        os << director;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::directorsDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        if (f->getDir() == director.getName()) {
            f->deleteDirector(director.getName());
            os.str("");
            os << f;
            std::string newMovie = os.str();
            db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        }
        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(director, filmLink);
        return ptr;
    } else if (act == program_state::SeeAll) {
        clearTerminal();
        director.displayFilms(std::cout);

        waitForInput();

        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(director, filmLink);
        return ptr;
    } else if (act == program_state::Exit) {
        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(director, filmLink);
        return ptr;
    }
    std::unique_ptr<DirectorPage> ptr =
        std::make_unique<DirectorPage>(director, filmLink);
    return ptr;
}

void DirectorPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "DIRECTOR PAGE" << std::endl;
    printBorder();
    director.displayDirectorInfo(std::cout);
}
