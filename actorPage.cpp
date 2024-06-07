#include "actorPage.h"

#include "databaseManager.h"
#include "global.h"
#include "page.h"
extern Film *findAndChooseMovie(std::string title);
program_state ActorPage::nextAction() {
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
    } else if (action == "AddRole") {
        return program_state::AddRole;
    } else if (action == "DeleteRole") {
        return program_state::DeleteRole;
    } else if (action == "SeeAllRoles") {
        return program_state::SeeAll;
    }
    return program_state::Exit;  // tylko dla kompilatora taka sytuacja nie
                                 // wystąpi w normalnym działaniu programu
}

std::unique_ptr<Page> ActorPage::doAction(program_state act,
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
    } else if (act == program_state::AddRole) {
        DatabaseManager db_mgmt;
        std::string character;
        std::cout << "Played character: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, character);
        std::string film;
        std::cout << "In movie: " << std::endl;
        std::getline(std::cin, film);
        Film *f = findAndChooseMovie(film);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
            return ptr;
        }
        std::ostringstream os;
        os << actor;
        std::string oldRecord = os.str();
        try {
            actor.addRole(character, *f);
        } catch (const std::invalid_argument &e) {
            std::cout << "Actor already has a role in this movie\n";
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
            return ptr;
        }
        os.str("");
        os << actor;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::actorsDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        f->addRole(actor.getName(), character);
        os.str("");
        os << f;
        std::string newMovie = os.str();
        db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
        return ptr;
    } else if (act == program_state::DeleteRole) {
        DatabaseManager db_mgmt;
        std::string film;
        std::cout << "Delete role from movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, film);
        Film *f = findAndChooseMovie(film);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
            return ptr;
        }
        std::ostringstream os;
        os << actor;
        std::string oldRecord = os.str();
        actor.deleteRole(*f);
        os.str("");
        os << actor;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::actorsDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        try {
            f->deleteRole(actor.getName());
        } catch (const std::invalid_argument &e) {
            std::cout << "This actor never had a role in this movie in the "
                         "first place\n";
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
            return ptr;
        }
        os.str("");
        os << f;
        std::string newMovie = os.str();
        db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
        return ptr;
    } else if (act == program_state::SeeAll) {
        clearTerminal();
        actor.displayRoles(std::cout);

        waitForInput();

        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
        return ptr;
    } else if (act == program_state::Exit) {
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
        return ptr;
    }
    std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor, filmLink);
    return ptr;
}

void ActorPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "ACTOR PAGE" << std::endl;
    printBorder();
    actor.displayActorInfo(std::cout);
}
