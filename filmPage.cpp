#include "filmPage.h"
#include "csv.h"
#include "addReviewPage.h"
#include "actorPage.h"
#include "databaseManager.h"
void FilmPage::loadRevs()
{
    if (film->getReviews().size() == 0)
    {
        io::CSVReader<5, io::trim_chars<' '>, io::no_quote_escape<';'>> in("../reviews.csv");
        in.read_header(io::ignore_missing_column, "ID", "User", "Film_id", "Score", "Content");
        unsigned int ID;
        std::string User;
        unsigned int Film_id;
        unsigned int Score;
        std::string Content;
        while (in.read_row(ID, User, Film_id, Score, Content))
        {
            if (Film_id == film->getID())
            {
                Review r(film, ID, User, Score, Content);
                film->addReview(r);
            }
        }
    }
    return;
}
program_state FilmPage::nextAction()
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

    if (action == "Browse")
    {
        return program_state::Browse;
    }
    if (action == "AddReview")
    {
        return program_state::AddReview;
    }
    if (action == "Reviews")
    {
        return program_state::Reviews;
    }
    if (action == "SeeActor")
    {
        return program_state::SeeActor;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> FilmPage::doAction(program_state act, std::unique_ptr<Role> &us_ptr)
{
    if (act == program_state::Browse)
    {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
    else if (act == program_state::Reviews)
    {
        std::unique_ptr<ReviewsPage> ptr = std::make_unique<ReviewsPage>(film);
        return ptr;
    }
    else if (act == program_state::AddReview)
    {
        std::unique_ptr<AddReviewPage> ptr = std::make_unique<AddReviewPage>(film);
        return ptr;
    }
    else if (act == program_state::SeeActor)
    {
        int a = 0;
        DatabaseManager db_mgmt;
        std::vector<std::pair<std::string, std::string>> actors;
        for (auto it = film->getCast().begin(); it != film->getCast().end(); ++it)
        {
            actors.push_back(std::pair<std::string, std::string>(it->first, it->second));
        }
        while (a < -1 || a > 10 || a > actors.size() || a == 0)
        {
            cppIO::input(
                "Choose number of an actor you wish to see or -1 for exit: ",
                a);
            if (a < -1 || a > 10 || a > actors.size() || a == 0)
            {
                cppIO::log("Choose nr of one of the shown actors.");
            }
        }
        if (a == -1)
        {
            std::unique_ptr<BrowsePage> ptr =
                std::make_unique<BrowsePage>();
            return ptr;
        }
        std::string actor_name = actors[a - 1].first + " " + actors[a - 1].second;
        std::vector<Actor> foundActors = db_mgmt.actorSearch(actor_name);
        std::unique_ptr<ActorPage> ptr =
            std::make_unique<ActorPage>(foundActors[0]);
        return ptr;
    }
    else
    //    (act == program_state::Exit)
    {
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    }
}

void FilmPage::print()
{
    clearTerminal();
    printBorder();
    std::cout << "FILM PAGE" << std::endl;
    printBorder();
    film->write(std::cout);
}