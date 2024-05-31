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
    std::unique_ptr<Page> doAction(int act) override;

    int nextAction() override
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
        else if (action == "Browse")
        {
            return 3;
        }
        return 5;
    }
    void showOptions()
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << opt << std::endl;
        }
    }
};