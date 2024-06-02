#pragma once
#include "page.h"
#include "filmPage.h"
#include "global.h"
#include "role.h"
#include "logged.h"
#include "guest.h"
#include "admin.h"
class BrowsePage : public Page
{
    std::string msg = "Browse Movies: ";
    std::vector<std::string> options = {"Exit", "Browse"};

public:
    void print() override
    {
        std::cout << msg << std::endl;
    }
    std::vector<Film *> movieSearch(const std::string &title);
    std::unique_ptr<Page> doAction(program_state act, std::unique_ptr<Role> &us_ptr) override;

    program_state nextAction() override;
    void showOptions()
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << opt << std::endl;
        }
    }
};