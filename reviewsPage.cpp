#include "reviewsPage.h"

void ReviewsPage::print()
{
    for (auto &r : film->getReviews())
    {
        r.write(std::cout);
        std::cout << "------------" << std::endl;
    }
}

program_state ReviewsPage::nextAction()
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
}

std::unique_ptr<Page> ReviewsPage::doAction(program_state act, std::unique_ptr<Role> &us_ptr)
{
    if (act == program_state::Exit)
    {
        std::unique_ptr<ReviewsPage> ptr = std::make_unique<ReviewsPage>(film);
        return ptr;
    }
}