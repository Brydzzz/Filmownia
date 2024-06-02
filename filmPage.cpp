#include "filmPage.h"
program_state FilmPage::nextAction()
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

    if (action == "Browse")
    {
        return program_state::Browse;
    }
    if (action == "AddReview")
    {
        return program_state::Browse;
    }
}

std::unique_ptr<Page> FilmPage::doAction(program_state act, std::unique_ptr<Role> &us_ptr)
{
    if (act == program_state::Browse)
    {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
}

void FilmPage::print()
{
    film->write(std::cout);
}