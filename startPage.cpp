#include "startPage.h"

extern std::vector<Review> loadReviews(User &user);
program_state StartPage::nextAction()
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
    else if (action == "Browse")
    {
        return program_state::Browse;
    }
    else if (action == "MyPage")
    {
        return program_state::MyPage;
    }
    else if (action == "LogIn")
    {
        return program_state::LogIn;
    }
    else if (action == "LogOut")
    {
        return program_state::LogOut;
    }
    else if (action == "SignUp")
    {
        return program_state::SignUp;
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
    else if (act == program_state::LogIn)
    {
        us_ptr->getUser()->log_in();
        loadReviews(*us_ptr->getUser());
        us_ptr = std::make_unique<Logged>(us_ptr->getUser(), loadReviews(*us_ptr->getUser()));
    }
    else if (act == program_state::LogOut)
    {
        us_ptr->getUser()->log_out();
        us_ptr = std::make_unique<Guest>(us_ptr->getUser());
    }
    else if (act == program_state::SignUp)
    {
        Guest *guest_ptr = dynamic_cast<Guest *>(us_ptr.get());
        guest_ptr->sign_up();
    }
    std::unique_ptr<Page> ptr = std::make_unique<StartPage>();
    return ptr;
}