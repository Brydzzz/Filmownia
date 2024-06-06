#pragma once
#include <iostream>
#include "page.h"
#include "browsePage.h"
#include "global.h"
#include "role.h"
#include "logged.h"
#include "guest.h"
#include "admin.h"
#include "reviewsPage.h"
class FilmPage : public Page
{
    std::vector<std::string> options;
    std::vector<std::string> optionsGuest = {"SeeDirector", "SeeActor", "Browse", "Exit", "Reviews"};
    std::vector<std::string> optionsRest = {"AddReview", "SeeDirector", "SeeActor", "Browse", "Exit", "Reviews"};
    Film *film;
    void loadRevs();

public:
    FilmPage(Film *f) : film(f) { loadRevs(); };
    void print() override;
    program_state nextAction() override;

    std::unique_ptr<Page> doAction(program_state, std::unique_ptr<Role> &us_ptr) override;
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
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << "- " << opt << std::endl;
        }
    }
};