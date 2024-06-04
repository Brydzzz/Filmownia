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
class DirectorPage : public Page
{
    std::vector<std::string> options = {
        "AddFilm",
        "DeleteFilm",
        "SeeAllFilms",
        "GoBack",
        "Exit",
    };
    Director director;

public:
    DirectorPage(Director d) : director(d) {}
    void print() override; // print director info
    program_state nextAction() override;

    std::unique_ptr<Page> doAction(program_state,
                                   std::unique_ptr<Role> &us_ptr) override;
    void showOptions() override
    {
        std::cout << "Available Options: \n";
        for (auto opt : options)
        {
            std::cout << "- " << opt << std::endl;
        }
    }
};
