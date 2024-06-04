#include "actorPage.h"

#include "databaseManager.h"
#include "page.h"
program_state ActorPage::nextAction()
{
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end())
    {
        cppIO::input("Enter desired action: ", action);
    }
    if (action == "Exit")
    {
        return program_state::Exit;
    }
    if (action == "GoBack")
    {
        return program_state::GoBack;
    }
    if (action == "AddRole")
    {
        return program_state::AddRole;
    }
    if (action == "DeleteRole")
    {
        return program_state::DeleteRole;
    }
    if (action == "SeeAllRoles")
    {
        return program_state::SeeAllRoles;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> ActorPage::doAction(program_state act,
                                          std::unique_ptr<Role> &us_ptr)
{
    if (act == program_state::GoBack)
    {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
    else if (act == program_state::AddRole)
    {
        DatabaseManager db_mgmt;
        std::string character;
        std::cout << "Played character: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, character);
        std::string film;
        std::cout << "In movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, film);
        std::vector<Film *> found = db_mgmt.movieSearch(film);
        if (found.size() == 0)
        {
            std::cout << "Movie not found" << std::endl;
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
            return ptr;
        }
        else if (found.size() == 1)
        {
            std::ostringstream os;
            os << actor;
            std::string oldRecord = os.str();
            actor.addRole(character, *found[0]);
            os.str("");
            os << actor;
            std::string newRecord = os.str();
            db_mgmt.replaceLine(newRecord, oldRecord, whichDb::actorsDb);
            found[0]->addRole(actor.getName(), character);
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
            return ptr;
        }
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
        return ptr;
    }
    else if (act == program_state::DeleteRole)
    {
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
        return ptr;
    }
    else if (act == program_state::SeeAllRoles)
    {
        clearTerminal();
        actor.displayRoles(std::cout);

        // Pause until Enter is pressed
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
        return ptr;
    }
    else if (act == program_state::Exit)
    {
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
        return ptr;
    }
    std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
    return ptr;
}

void ActorPage::print()
{
    clearTerminal();
    printBorder();
    std::cout << "ACTOR PAGE" << std::endl;
    printBorder();
    actor.displayActorInfo(std::cout);
}
