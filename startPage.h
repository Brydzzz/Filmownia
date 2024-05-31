#pragma once
#include "page.h"
#include "browsePage.h"
#include "global.h"
class StartPage : public Page
{
    std::vector<std::string> options = {"Browse",
                                        "Exit"};
    std::string msg = "Welcome to Filmownia movie database!\nPresented to you by: Brygida S, Kinga Ł and Tomasz S\n";

public:
    int nextAction() override;
    std::unique_ptr<Page> doAction(int act) override;
    void print() override
    {
        std::cout << msg << std::endl;
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
