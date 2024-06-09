#include "userPage.h"
std::vector<Review> UserPage::findReviews(std::string name) {
    std::vector<Review> list;
    io::CSVReader<5, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
        "../reviews.csv");
    in.read_header(io::ignore_missing_column, "ID", "User", "Film_id", "Score",
                   "Content");
    unsigned int ID;
    std::string User;
    unsigned int Film_id;
    unsigned int Score;
    std::string Content;
    while (in.read_row(ID, User, Film_id, Score, Content)) {
        if (name == User) {
            auto it = flist.begin();
            it = std::find_if(it, flist.end(), [&](const Film &film) {
                return film.getID() == Film_id;
            });
            Review r(&(*it), ID, User, Score, Content);
            list.push_back(r);
        }
    }
    return list;
}
void UserPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "USER PAGE" << std::endl;
    printBorder();
    std::cout << "User name: " << usr << std::endl;
    std::cout << "Reviews: " << std::endl;

    for (Review &rev : revs) {
        std::cout << std::quoted(rev.getFilm()->getTitle()) << std::endl;
        rev.write(std::cout);
        std::cout << "------------" << std::endl;
    }
}

program_state UserPage::nextAction() {
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end()) {
        cppIO::input("Enter desired action: ", action);
    }
    if (action == "Exit") {
        return program_state::Exit;
    } else if (action == "GoBack") {
        return program_state::GoBack;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> UserPage::doAction(program_state act,
                                         std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::GoBack) {
        std::unique_ptr<StartPage> ptr = std::make_unique<StartPage>();
        return ptr;
    }
    std::unique_ptr<UserPage> ptr =
        std::make_unique<UserPage>(us_ptr->getUser()->getLogin());
    return ptr;
}