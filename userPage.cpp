#include "userPage.h"

void UserPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "USER PAGE" << std::endl;
    printBorder();
    std::cout << "User name: " << usr << std::endl;
    std::cout << "Reviews: " << std::endl;
    int i = 1;
    for (Review &rev : revs) {
        std::cout << i << ". " << std::quoted(rev.getFilm()->getTitle())
                  << std::endl;
        rev.write(std::cout);
        std::cout << "------------" << std::endl;
        i++;
    }
}

program_state UserPage::nextAction() {
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
    } else if (action == "GoBack") {
        return program_state::GoBack;
    } else if (action == "DeleteReview") {
        return program_state::DeleteElement;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> UserPage::doAction(program_state act,
                                         std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::GoBack) {
        std::unique_ptr<StartPage> ptr = std::make_unique<StartPage>();
        return ptr;
    } else if (act == program_state::DeleteElement) {
        DatabaseManager db_mgmt;
        std::string title;
        std::cout << "Delete review from movie: " << std::endl;
        int a = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (a < 1 || a > revs.size())
            cppIO::input("Delete which review?: ", a);
        Review delRev = revs[a - 1];
        std::ostringstream os;
        os << delRev;
        db_mgmt.deleteLine(os.str(), whichDb::reviewsDb);

        std::unique_ptr<UserPage> ptr =
            std::make_unique<UserPage>(us_ptr->getUser()->getLogin());
        return ptr;
    } else if (act == program_state::Exit) {
        std::unique_ptr<UserPage> ptr =
            std::make_unique<UserPage>(us_ptr->getUser()->getLogin());
        return ptr;
    }
    std::unique_ptr<UserPage> ptr =
        std::make_unique<UserPage>(us_ptr->getUser()->getLogin());
    return ptr;
}