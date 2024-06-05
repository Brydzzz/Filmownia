#include "browsePage.h"

#include "actorPage.h"
#include "csv.h"
#include "databaseManager.h"
#include "date.h"
#include "directorPage.h"
#include "global.h"
extern std::vector<Film> flist;

std::unique_ptr<Page> BrowsePage::doAction(program_state act,
                                           std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::BrowseMovies) {
        std::string title;
        std::cout << "Searched movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, title);
        // std::cin >> title1;
        // cppIO::input("Searched movie: ", title1, title2, title3, title4);
        DatabaseManager db_mgmt;
        std::vector<Film *> found = db_mgmt.movieSearch(title);
        if (found.size() != 0) {
            int a;
            if (found.size() != 1) {
                std::cout << "Found movies: " << std::endl;
                int i = 1;

                for (auto f : found) {
                    if (i <= 10) {
                        std::cout << i << '.' << f->getTitle() << std::endl;
                        ++i;
                    }
                }
                cppIO::input(
                    "Choose number of a movie you wish to see or -1 for exit: ",
                    a);
                if (a == -1 || a < -1 || a >= found.size()) {
                    std::unique_ptr<BrowsePage> ptr =
                        std::make_unique<BrowsePage>();
                    return ptr;
                }
            } else {
                a = 1;
            }
            a--;
            // std::cout << found[a].getDesc() << std::endl;
            std::unique_ptr<FilmPage> ptr =
                std::make_unique<FilmPage>(found[a]);
            return ptr;
        } else {
            std::cout << "Movie not found\n";
            waitForInput();
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    } else if (act == program_state::BrowseActors) {
        std::string name;
        std::cout << "Enter actor's name: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        DatabaseManager db_mgmt;
        std::vector<Actor> foundActors = db_mgmt.actorSearch(name);
        if (foundActors.size() != 0) {
            int a;
            if (foundActors.size() != 1) {
                std::cout << "Found actors: " << std::endl;
                int i = 1;

                for (auto a : foundActors) {
                    if (i <= 10) {
                        std::cout << i << '.' << a.getName() << std::endl;
                        ++i;
                    }
                }
                cppIO::input(
                    "Choose number of a actor you wish to see or -1 for exit: ",
                    a);
                if (a == -1) {
                    std::unique_ptr<BrowsePage> ptr =
                        std::make_unique<BrowsePage>();
                    return ptr;
                }
            } else {
                a = 1;
            }
            a--;
            std::unique_ptr<ActorPage> ptr =
                std::make_unique<ActorPage>(foundActors[a]);
            return ptr;
        } else {
            std::cout << "Actor not found\n";
            waitForInput();
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    } else if (act == program_state::BrowseDirectors) {
        std::string name;
        std::cout << "Enter director's name: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        DatabaseManager db_mgmt;
        std::vector<Director> foundDirectors = db_mgmt.directorSearch(name);
        if (foundDirectors.size() != 0) {
            int a;
            if (foundDirectors.size() != 1) {
                std::cout << "Found directors: " << std::endl;
                int i = 1;

                for (auto d : foundDirectors) {
                    if (i <= 10) {
                        std::cout << i << '.' << d.getName() << std::endl;
                        ++i;
                    }
                }
                cppIO::input(
                    "Choose number of a actor you wish to see or -1 for exit: ",
                    a);
                if (a == -1) {
                    std::unique_ptr<BrowsePage> ptr =
                        std::make_unique<BrowsePage>();
                    return ptr;
                }
            } else {
                a = 1;
            }
            a--;
            std::unique_ptr<DirectorPage> ptr =
                std::make_unique<DirectorPage>(foundDirectors[a]);
            return ptr;
        } else {
            std::cout << "Director not found\n";
            waitForInput();
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    } else if (act == program_state::Exit) {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    } else if (act == program_state::GoBack) {
        std::unique_ptr<Page> ptr = std::make_unique<StartPage>();
        return ptr;
    }
    std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
    return ptr;
}

program_state BrowsePage::nextAction() {
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end()) {
        cppIO::input("Enter desired action: ", action);
        // for (int i = 0; i < action.size(); ++i)
        // {
        //     action[i] = (char)tolower(action[i]);
        // }
    }
    if (action == "Exit") {
        return program_state::Exit;
    } else if (action == "BrowseMovies") {
        return program_state::BrowseMovies;
    } else if (action == "BrowseActors") {
        return program_state::BrowseActors;
    } else if (action == "BrowseDirectors") {
        return program_state::BrowseDirectors;
    } else if (action == "GoBack") {
        return program_state::GoBack;
    }
    return program_state::Exit;
}