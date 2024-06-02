#include "startPage.h"
program_state StartPage::nextAction()
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
    else if (action == "Browse")
    {
        return program_state::Browse;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> StartPage::doAction(program_state act)
{
    if (act == program_state::Browse)
    {
        std::unique_ptr<BrowsePage> ptr;
        ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
}