#pragma once
#include "admin.h"
#include "filmPage.h"
#include "global.h"
#include "guest.h"
#include "logged.h"
#include "page.h"
#include "person.h"
#include "role.h"
#include "startPage.h"
class BrowsePage : public Page
{
    std::string msg = "CHOOSE OPTION: ";
    std::vector<std::string> options = {"Exit", "BrowseMovies", "BrowseActors",
                                        "BrowseDirectors", "GoBack"};

public:
    void print() override
    {
        clearTerminal();
        printBorder();
        std::cout << msg << std::endl;
        printBorder();
    }
    std::vector<Film *> movieSearch(const std::string &title);
    std::vector<Actor> actorSearch(const std::string &name);
    std::unique_ptr<Page> doAction(program_state act,
                                   std::unique_ptr<Role> &us_ptr) override;

    program_state nextAction() override;
    void showOptions(const Role *us_ptr) override
    {
        std::cout << "Available Options: \n";
        for (auto opt : options)
        {
            std::cout << "- " << opt << std::endl;
        }
    }
};