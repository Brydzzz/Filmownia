#include "reviewsPage.h"

void ReviewsPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "REVIEWS PAGE" << std::endl;
    printBorder();
    if (film->getReviews().size() == 0) {
        std::cout << "No reviews found" << std::endl;
    }
    for (auto &r : film->getReviews()) {
        r.write(std::cout);
        std::cout << "------------" << std::endl;
    }
}

program_state ReviewsPage::nextAction() {
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
    } else if (action == "Browse") {
        return program_state::Browse;
    } else if (action == "GoBack") {
        return program_state::GoBack;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> ReviewsPage::doAction(program_state act,
                                            std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::Exit) {
        std::unique_ptr<ReviewsPage> ptr = std::make_unique<ReviewsPage>(film);
        return ptr;
    } else if (act == program_state::Browse) {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    } else if (act == program_state::GoBack) {
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    }
    std::unique_ptr<ReviewsPage> ptr = std::make_unique<ReviewsPage>(film);
    return ptr;
}