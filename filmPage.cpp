#include "filmPage.h"

#include "actorPage.h"
#include "addReviewPage.h"
#include "csv.h"
#include "databaseManager.h"
#include "directorPage.h"
#include "producerPage.h"
#include "writerPage.h"
program_state FilmPage::nextAction() {
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

    if (action == "Browse") {
        return program_state::Browse;
    }
    if (action == "AddReview") {
        return program_state::AddReview;
    }
    if (action == "Reviews") {
        return program_state::Reviews;
    }
    if (action == "SeeActor") {
        return program_state::SeeActor;
    }
    if (action == "SeeDirector") {
        return program_state::SeeDirector;
    }
    if (action == "SeeProducer") {
        return program_state::SeeProducer;
    }
    if (action == "SeeWriter") {
        return program_state::SeeWriter;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> FilmPage::doAction(program_state act,
                                         std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::Browse) {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    } else if (act == program_state::Reviews) {
        std::unique_ptr<ReviewsPage> ptr = std::make_unique<ReviewsPage>(film);
        return ptr;
    } else if (act == program_state::AddReview) {
        std::unique_ptr<AddReviewPage> ptr =
            std::make_unique<AddReviewPage>(film);
        return ptr;
    } else if (act == program_state::SeeActor) {
        int a = 0;
        DatabaseManager db_mgmt;
        std::vector<std::string> actors;
        for (auto it = film->getCast().begin(); it != film->getCast().end();
             ++it) {
            actors.push_back(it->first);
        }
        while (a < -1 || a > actors.size() || a == 0) {
            cppIO::input(
                "Choose number of an actor you wish to see or -1 for exit: ",
                a);
            checkForCinFail(a);
            if (a == -1) {
                break;
            } else if (a < -1 || a > 10 || a > actors.size() || a == 0) {
                cppIO::log("Invalid number. Choose one of available options.");
            }
        }
        if (a == -1) {
            std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
            return ptr;
        }
        std::string actor_name = actors[a - 1];
        std::vector<Actor> foundActors =
            db_mgmt.personSearch<Actor>(actor_name);
        std::unique_ptr<ActorPage> ptr =
            std::make_unique<ActorPage>(foundActors[0], film);
        return ptr;
    } else if (act == program_state::SeeDirector) {
        DatabaseManager db_mgmt;
        std::vector<Director> foundDirector =
            db_mgmt.personSearch<Director>(film->getDir());
        std::unique_ptr<DirectorPage> ptr =
            std::make_unique<DirectorPage>(foundDirector[0], film);
        return ptr;
    } else if (act == program_state::SeeProducer) {
        int a = 0;
        DatabaseManager db_mgmt;
        std::vector<std::string> producers;
        for (auto it = film->getProducers().begin();
             it != film->getProducers().end(); ++it) {
            producers.push_back(it->first);
        }
        while (a < -1 || a > 10 || a > producers.size() || a == 0) {
            cppIO::input(
                "Choose number of a producer you wish to see or -1 for exit: ",
                a);
            checkForCinFail(a);
            if (a == -1) {
                break;
            } else if (a < -1 || a > 10 || a > producers.size() || a == 0) {
                cppIO::log("Invalid number. Choose one of available options.");
            }
        }
        if (a == -1) {
            std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
            return ptr;
        }
        std::string producer_name = producers[a - 1];
        std::vector<Producer> foundProducers =
            db_mgmt.personSearch<Producer>(producer_name);
        std::unique_ptr<ProducerPage> ptr =
            std::make_unique<ProducerPage>(foundProducers[0], film);
        return ptr;
    } else if (act == program_state::SeeWriter) {
        int a = 0;
        DatabaseManager db_mgmt;
        std::vector<std::string> writers;
        for (auto it = film->getWriters().begin();
             it != film->getWriters().end(); ++it) {
            writers.push_back(it->first);
        }
        while (a < -1 || a > 10 || a > writers.size() || a == 0) {
            cppIO::input(
                "Choose number of a writer you wish to see or -1 for exit: ",
                a);
            checkForCinFail(a);
            if (a == -1) {
                break;
            } else if (a < -1 || a > 10 || a > writers.size() || a == 0) {
                cppIO::log("Invalid number. Choose one of available options.");
            }
        }
        if (a == -1) {
            std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
            return ptr;
        }
        std::string writer_name = writers[a - 1];
        std::vector<Writer> foundWriters =
            db_mgmt.personSearch<Writer>(writer_name);
        std::unique_ptr<WriterPage> ptr =
            std::make_unique<WriterPage>(foundWriters[0], film);
        return ptr;
    } else {
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    }
}

void FilmPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "FILM PAGE" << std::endl;
    printBorder();
    film->write(std::cout);
}