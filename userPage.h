#pragma once
#include <memory>
#include "page.h"
#include "csv.h"
#include "startPage.h"
class UserPage : public Page
{
    std::vector<std::string> options = {"GoBack", "Exit"};
    std::string usr;
    std::vector<Review> revs;
    std::vector<Review> findReviews(std::string name);

public:
    UserPage(std::string usr) : usr(usr) { revs = findReviews(usr); };
    void print() override;
    program_state nextAction() override;
    std::unique_ptr<Page> doAction(program_state act, std::unique_ptr<Role> &us_ptr) override;
    void showOptions(const Role *us_ptr) override
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << "- " << opt << std::endl;
        }
    }
};