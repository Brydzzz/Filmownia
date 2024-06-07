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
    std::vector<std::string> options;
    std::vector<std::string> optionsRest = {"Browse",
                                            "Exit", "MyPage", "LogOut"};
    std::vector<std::string> optionsGuest = {"Browse",
                                             "Exit", "SignUp", "LogIn"};
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
    void showOptions(const Role *us_ptr) override
    {
        if (us_ptr->getName() == "guest")
        {
            options = optionsGuest;
        }
        else
        {
            options = optionsRest;
        }
        std::cout << "Available Options: \n";
        for (auto opt : options)
        {
            std::cout << "- " << opt << std::endl;
        }
    }
};
