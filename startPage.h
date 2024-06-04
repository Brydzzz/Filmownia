#pragma once
#include "page.h"
#include "browsePage.h"
#include "global.h"
#include "role.h"
#include "logged.h"
#include "guest.h"
#include "admin.h"
#include "userPage.h"
class StartPage : public Page
{
    std::vector<std::string> options = {"Browse",
                                        "Exit", "MyPage"};
    std::string msg = "Welcome to Filmownia movie database!\nPresented to you by: Brygida S, Kinga Ł and Tomasz S";

public:
    program_state nextAction() override;
    std::unique_ptr<Page> doAction(program_state act, std::unique_ptr<Role> &us_ptr) override;
    void print() override
    {
        clearTerminal();
        printBorder();
        std::cout << msg << std::endl;
        printBorder();
    }
    void showOptions() override
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << "- " << opt << std::endl;
        }
    }
};
