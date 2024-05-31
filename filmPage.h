#pragma once
#include <iostream>
#include "page.h"
#include "browsePage.h"
#include "global.h"
class FilmPage : public Page
{
    std::vector<std::string> options = {"AddReview", "SeeActor", "Browse", "Exit"};
    Film *film;

public:
    FilmPage(Film *f) : film(f){};
    void print() override;
    int nextAction() override;

    std::unique_ptr<Page> doAction(int act) override;
    void showOptions()
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << opt << std::endl;
        }
    }
};