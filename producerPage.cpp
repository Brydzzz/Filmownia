#include "producerPage.h"

#include "databaseManager.h"
#include "page.h"
program_state ProducerPage::nextAction() {
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
    } else if (action == "GoBack") {
        return program_state::GoBack;
    } else if (action == "SeeAllJobs") {
        return program_state::SeeAll;
    } else if (action == "AddJob") {
        return program_state::AddElement;
    } else if (action == "DeleteJob") {
        return program_state::DeleteElement;
    }
    return program_state::Exit;  // tylko dla kompilatora taka sytuacja nie
                                 // wystąpi w normalnym działaniu programu
}

std::unique_ptr<Page> ProducerPage::doAction(program_state act,
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
    } else if (act == program_state::SeeAll) {
        clearTerminal();
        prod.displayJobs(std::cout);
        waitForInput();

        std::unique_ptr<ProducerPage> ptr =
            std::make_unique<ProducerPage>(prod, filmLink);
        return ptr;
    } else if (act == program_state::AddElement) {
        DatabaseManager db_mgmt;
        int j = 0;
        while (j != 1 && j != 2) {
            cppIO::input("Choose job: \n1.Producer \n2.Executive Producer\n",
                         j);
        }
        std::cout << "In movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string title;
        std::getline(std::cin, title);
        std::vector<Film *> foundFilms = findMovies(title);
        Film *f = chooseMovie(foundFilms);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<ProducerPage> ptr =
                std::make_unique<ProducerPage>(prod, filmLink);
            return ptr;
        }
        std::ostringstream os;
        os << prod;
        std::string oldRecord = os.str();
        ProducerType pt = static_cast<ProducerType>(j);
        try {
            prod.addJob(pt, *f);
        } catch (const std::invalid_argument &e) {
            std::cout << "Producer already has a job in this movie\n";
            waitForInput();
            std::unique_ptr<ProducerPage> ptr =
                std::make_unique<ProducerPage>(prod, filmLink);
            return ptr;
        }
        os.str("");
        os << prod;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::producersDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        f->addProducer(prod.getName(), ptypeToString(pt));
        os.str("");
        os << f;
        std::string newMovie = os.str();
        db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        std::unique_ptr<ProducerPage> ptr =
            std::make_unique<ProducerPage>(prod, filmLink);
    } else if (act == program_state::DeleteElement) {
        DatabaseManager db_mgmt;
        std::string title;
        std::cout << "Delete job from movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, title);
        std::vector<Film *> foundFilms = prod.findFilmsByTitle(title);
        Film *f = chooseMovie(foundFilms);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<ProducerPage> ptr =
                std::make_unique<ProducerPage>(prod, filmLink);
            return ptr;
        }
        std::ostringstream os;
        os << prod;
        std::string oldRecord = os.str();
        prod.deleteJob(*f);
        os.str("");
        os << prod;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::producersDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        try {
            f->deleteProducer(prod.getName());
        } catch (const std::invalid_argument &e) {
            std::cout << "This producer never had a job in this movie in the "
                         "first place\n";
            waitForInput();
            std::unique_ptr<ProducerPage> ptr =
                std::make_unique<ProducerPage>(prod, filmLink);
            return ptr;
        }
        os.str("");
        os << f;
        std::string newMovie = os.str();
        db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        std::unique_ptr<ProducerPage> ptr =
            std::make_unique<ProducerPage>(prod, filmLink);
        return ptr;
    } else if (act == program_state::Exit) {
        std::unique_ptr<ProducerPage> ptr =
            std::make_unique<ProducerPage>(prod, filmLink);
        return ptr;
    }

    std::unique_ptr<ProducerPage> ptr =
        std::make_unique<ProducerPage>(prod, filmLink);
    return ptr;
}

void ProducerPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "PRODUCER PAGE" << std::endl;
    printBorder();
    prod.displayProducerInfo(std::cout);
}