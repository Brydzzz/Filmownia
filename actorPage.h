#pragma once
#include <iostream>

#include "admin.h"
#include "browsePage.h"
#include "global.h"
#include "guest.h"
#include "logged.h"
#include "page.h"
#include "person.h"
#include "role.h"
class ActorPage : public Page {
    std::vector<std::string> options;
    std::vector<std::string> optionsRest = {
        "SeeAllRoles",
        "GoBack",
        "Exit",
    };
    std::vector<std::string> optionsAdmin = {
        "AddRole", "DeleteRole", "SeeAllRoles", "GoBack", "Exit",
    };
    Actor actor;
    Film *filmLink;  // used in GoBack option

   public:
    ActorPage(Actor a, Film *filmLink = nullptr)
        : actor(a), filmLink(filmLink) {}
    void print() override;  // print actor info
    program_state nextAction() override;

    std::unique_ptr<Page> doAction(program_state,
                                   std::unique_ptr<Role> &us_ptr) override;
    void showOptions(const Role *us_ptr) override {
        if (us_ptr->getName() == "admin") {
            options = optionsAdmin;
        } else {
            options = optionsRest;
        }
        std::cout << "Available Options: \n";
        for (auto opt : options) {
            std::cout << "- " << opt << std::endl;
        }
    }
};
