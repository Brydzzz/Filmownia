#include "actorPage.h"

#include "databaseManager.h"
#include "page.h"
program_state ActorPage::nextAction()
{
    std::string action;
    bool condition = std::find(options.begin(), options.end(), action) == options.end();
    while (condition)
    {
        cppIO::input("Enter desired action: ", action);
        condition = std::find(options.begin(), options.end(), action) == options.end();
        if (condition)
        {
            cppIO::log("No such option available for this user. Chose one from the list.");
        }
    }
    if (action == "Exit")
    {
        return program_state::Exit;
    }
    else if (action == "GoBack")
    {
        return program_state::GoBack;
    }
    else if (action == "AddRole")
    {
        return program_state::AddRole;
    }
    else if (action == "DeleteRole")
    {
        return program_state::DeleteRole;
    }
    else if (action == "SeeAllRoles")
    {
        return program_state::SeeAllRoles;
    }
    return program_state::Exit; // tylko dla kompilatora taka sytuacja nie wystąpi w normalnym działaniu programu
}

Film *findAndChooseMovie(std::string title)
{
    DatabaseManager db_mgmt;
    std::vector<Film *> found = db_mgmt.movieSearch(title);
    Film *f;
    if (found.size() == 0)
    {
        std::cout << "Movie not found" << std::endl;
        return nullptr;
    }
    else if (found.size() == 1)
    {
        f = found[0];
    }
    else
    {
        int i = 1;
        for (auto f : found)
        {
            if (i <= 10)
            {
                std::cout << i << '.' << f->getTitle() << std::endl;
                ++i;
            }
        }
        int a = 0;
        while (a < 1 || a > 10)
        {
            cppIO::input("Choose number of a movie you wish to choose: ", a);
            f = found[a - 1];
        }
    }
    return f;
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
        std::getline(std::cin, film);
        Film *f = findAndChooseMovie(film);
        if (f == nullptr)
        {
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
            return ptr;
        }
        std::ostringstream os;
        os << actor;
        std::string oldRecord = os.str();
        try
        {
            actor.addRole(character, *f);
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Actor already has a role in this movie\n";
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
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
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
        return ptr;
    }
    else if (act == program_state::DeleteRole)
    {
        DatabaseManager db_mgmt;
        std::string film;
        std::cout << "Delete role from movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, film);
        Film *f = findAndChooseMovie(film);
        if (f == nullptr)
        {
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
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
        try
        {
            f->deleteRole(actor.getName());
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "This actor never had a role in this movie in the "
                         "first place\n";
            waitForInput();
            std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
            return ptr;
        }
        os.str("");
        os << f;
        std::string newMovie = os.str();
        db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        std::unique_ptr<ActorPage> ptr = std::make_unique<ActorPage>(actor);
        return ptr;
    }
    else if (act == program_state::SeeAllRoles)
    {
        clearTerminal();
        actor.displayRoles(std::cout);

        waitForInput();

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
