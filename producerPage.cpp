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
    } else if (act == program_state::Exit) {
        std::unique_ptr<ProducerPage> ptr =
            std::make_unique<ProducerPage>(prod, filmLink);
        return ptr;
    }

    std::unique_ptr<ProducerPage> ptr = std::make_unique<ProducerPage>(prod, filmLink);
    return ptr;
}

void ProducerPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "PRODUCER PAGE" << std::endl;
    printBorder();
    prod.displayProducerInfo(std::cout);
}