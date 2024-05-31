#include "startPage.h"
int StartPage::nextAction()
{
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end())
    {
        cppIO::input("Enter desired action: ", action);
    }
    if (action == "Exit")
    {
        return 5;
    }
    else if (action == "Browse")
    {
        return 4;
    }
    return 0;
}

std::unique_ptr<Page> StartPage::doAction(int act)
{
    if (act == 4)
    {
        std::unique_ptr<BrowsePage> ptr;
        ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
}