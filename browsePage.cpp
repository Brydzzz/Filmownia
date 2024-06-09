#include "browsePage.h"

#include "actorPage.h"
#include "csv.h"
#include "databaseManager.h"
#include "date.h"
#include "directorPage.h"
#include "global.h"
#include "producerPage.h"
#include "writerPage.h"
extern std::vector<Film> flist;

std::unique_ptr<Page> BrowsePage::doAction(program_state act,
                                           std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::BrowseMovies) {
        std::string title;
        std::cout << "Searched movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, title);
        DatabaseManager db_mgmt;
        std::vector<Film *> found = db_mgmt.movieSearch(title);
        if (found.size() != 0) {
            std::cout << "Found movies: " << std::endl;
            int i = 0;

            for (auto f : found) {
                if (i < 10) {
                    std::cout << i + 1 << '.' << f->getTitle() << std::endl;
                    ++i;
                }
            }
            int a = 0;
            while (a < -1 || a > 10 || a > found.size() || a == 0) {
                cppIO::input(
                    "Choose number of a movie you wish to see or -1 for exit: ",
                    a);
                if (a == -1) {
                    break;
                }
            }

            if (a == -1) {
                std::unique_ptr<BrowsePage> ptr =
                    std::make_unique<BrowsePage>();
                return ptr;
            } else {
                a--;
            }
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
        std::vector<Actor> foundActors = db_mgmt.personSearch<Actor>(name);
        std::cout << foundActors.size() << std::endl;
        if (foundActors.size() != 0) {
            int a = 0;
            std::cout << "Found actors: " << std::endl;
            int i = 0;

            for (auto a : foundActors) {
                if (i < 10) {
                    std::cout << i + 1 << '.' << a.getName() << std::endl;
                    ++i;
                }
            }
            while (a < -1 || a > 10 || a > foundActors.size() || a == 0) {
                cppIO::input(
                    "Choose number of a actor you wish to see or -1 for exit: ",
                    a);
                if (a == -1) {
                    break;
                }
            }

            if (a == -1) {
                std::unique_ptr<BrowsePage> ptr =
                    std::make_unique<BrowsePage>();
                return ptr;
            } else {
                a--;
            }
            std::unique_ptr<ActorPage> ptr =
                std::make_unique<ActorPage>(foundActors[a]);
            return ptr;
        } else {
            std::cout << "Actor not found\n";
            waitForInput();
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    } else if (act == program_state::BrowseWriters) {
        std::string name;
        std::cout << "Enter writer's name: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        DatabaseManager db_mgmt;
        std::vector<Writer> foundWriters = db_mgmt.personSearch<Writer>(name);
        if (foundWriters.size() != 0) {
            int a;
            std::cout << "Found writers: " << std::endl;
            int i = 0;

            for (auto w : foundWriters) {
                if (i < 10) {
                    std::cout << i + 1 << '.' << w.getName() << std::endl;
                    ++i;
                }
            }
            while (a < -1 || a > 10 || a > foundWriters.size() || a == 0) {
                cppIO::input(
                    "Choose number of a writer you wish to see or -1 for "
                    "exit: ",
                    a);
                if (a == -1) {
                    break;
                }
            }
            if (a == -1) {
                std::unique_ptr<BrowsePage> ptr =
                    std::make_unique<BrowsePage>();
                return ptr;
            } else {
                a--;
            }
            std::unique_ptr<WriterPage> ptr =
                std::make_unique<WriterPage>(foundWriters[a]);
            return ptr;
        } else {
            std::cout << "Writer not found\n";
            waitForInput();
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    } else if (act == program_state::BrowseProducers) {
        std::string name;
        std::cout << "Enter producer's name: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        DatabaseManager db_mgmt;
        std::vector<Producer> foundProducers =
            db_mgmt.personSearch<Producer>(name);
        if (foundProducers.size() != 0) {
            int a = 0;
            std::cout << "Found producers: " << std::endl;
            int i = 0;

            for (auto p : foundProducers) {
                if (i < 10) {
                    std::cout << i + 1 << '.' << p.getName() << std::endl;
                    ++i;
                }
            }
            while (a < -1 || a > 10 || a > foundProducers.size() || a == 0) {
                cppIO::input(
                    "Choose number of a producer you wish to see or -1 for "
                    "exit: ",
                    a);
                if (a == -1) {
                    break;
                } else if (a < -1 || a > 10 || a > foundProducers.size() ||
                           a == 0) {
                    cppIO::log(
                        "Invalid number. Choose one of available options.");
                }
            }
            if (a == -1) {
                std::unique_ptr<BrowsePage> ptr =
                    std::make_unique<BrowsePage>();
                return ptr;
            } else {
                a--;
            }
            std::unique_ptr<ProducerPage> ptr =
                std::make_unique<ProducerPage>(foundProducers[a]);
            return ptr;
        } else {
            std::cout << "Producer not found\n";
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
        std::vector<Director> foundDirectors =
            db_mgmt.personSearch<Director>(name);
        if (foundDirectors.size() != 0) {
            int a = 0;
            std::cout << "Found directors: " << std::endl;
            int i = 0;

            for (auto d : foundDirectors) {
                if (i < 10) {
                    std::cout << i + 1 << '.' << d.getName() << std::endl;
                    ++i;
                }
            }
            while (a < -1 || a > 10 || a > foundDirectors.size() || a == 0) {
                cppIO::input(
                    "Choose number of a director you wish to see or -1 for "
                    "exit: ",
                    a);
                if (a == -1) {
                    break;
                } else if (a < -1 || a > 10 || a > foundDirectors.size() ||
                           a == 0) {
                    cppIO::log(
                        "Invalid number. Choose one of available options.");
                }
            }
            if (a == -1) {
                std::unique_ptr<BrowsePage> ptr =
                    std::make_unique<BrowsePage>();
                return ptr;
            } else {
                a--;
            }
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
    } else if (action == "BrowseMovies") {
        return program_state::BrowseMovies;
    } else if (action == "BrowseActors") {
        return program_state::BrowseActors;
    } else if (action == "BrowseDirectors") {
        return program_state::BrowseDirectors;
    } else if (action == "BrowseProducers") {
        return program_state::BrowseProducers;
    } else if (action == "BrowseWriters") {
        return program_state::BrowseWriters;
    } else if (action == "GoBack") {
        return program_state::GoBack;
    }
    return program_state::Exit;
}