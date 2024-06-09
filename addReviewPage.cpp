#include "addReviewPage.h"

#include <fstream>
void AddReviewPage::print() {
    std::cout << "Here you can add your review :)" << std::endl;
}

program_state AddReviewPage::nextAction() {
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end()) {
        cppIO::input("Enter desired action: ", action);
    }
    if (action == "Exit") {
        return program_state::Exit;
    } else if (action == "Add") {
        return program_state::Add;
    } else if (action == "GoBack") {
        return program_state::GoBack;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> AddReviewPage::doAction(program_state act,
                                              std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::GoBack) {
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    } else if (act == program_state::Add) {
        int rev = 11;
        while (rev > 10 || rev < 0) {
            cppIO::input("Enter score: ", rev);
            checkForCinFail(rev, 11);
            if (rev > 10 || rev < 0) {
                cppIO::log("Score value must be between 1-10.");
            }
        }
        std::string content;
        std::cout << "Your thoughts on the movie: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, content);
        DatabaseManager db_mgmt;
        unsigned int id = db_mgmt.generateReviewID();
        Review r(film, id, us_ptr->getUser()->getLogin(), rev, content);
        try {
            film->addReview(r);
        } catch (std::invalid_argument) {
            std::cout << "You already wrote a review for this movie"
                      << std::endl;
            waitForInput();
            std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
            return ptr;
        }
        std::stringstream ss;
        ss << r;
        db_mgmt.appendToFile(whichDb::reviewsDb, ss.str());
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    }
    std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
    return ptr;
}
