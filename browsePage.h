#pragma once
#include "page.h"
#include "filmPage.h"
#include "global.h"
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
    std::unique_ptr<Page> doAction(program_state act) override;

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