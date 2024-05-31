#include "filmPage.h"
int FilmPage::nextAction()
{
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end())
    {
        cppIO::input("Enter desired action: ", action);
    }
    if (action == "Exit")
    {
        return 0;
    }

    if (action == "Browse")
    {
        return 1;
    }
}

std::unique_ptr<Page> FilmPage::doAction(int act)
{
    if (act == 1)
    {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
}

void FilmPage::print()
{
    film->write(std::cout);
}