#include "filmPage.h"
#include "csv.h"
#include "addReviewPage.h"
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
    while (std::find(options.begin(), options.end(), action) == options.end())
    {
        cppIO::input("Enter desired action: ", action);
        // for (int i = 0; i < action.size(); ++i)
        // {
        //     action[i] = (char)tolower(action[i]);
        // }
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
    else
    //    (act == program_state::Exit)
    {
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    }
}

void FilmPage::print()
{
    film->write(std::cout);
}