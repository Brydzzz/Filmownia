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
    else if (action == "MyPage")
    {
        return program_state::MyPage;
    }
    return program_state::Exit;
}

std::unique_ptr<Page> StartPage::doAction(program_state act, std::unique_ptr<Role> &us_ptr)
{
    if (act == program_state::Browse)
    {
        std::unique_ptr<BrowsePage> ptr;
        ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
    else if (act == program_state::MyPage)
    {
        std::unique_ptr<UserPage> ptr = std::make_unique<UserPage>(us_ptr->getUser()->getLogin());
        return ptr;
    }
    std::unique_ptr<Page> ptr = std::make_unique<StartPage>();
    return ptr;
}