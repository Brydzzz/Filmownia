#pragma once
#include <iostream>

#include "admin.h"
#include "browsePage.h"
#include "global.h"
#include "guest.h"
#include "logged.h"
#include "page.h"
#include "reviewsPage.h"
#include "role.h"
class FilmPage : public Page {
    std::vector<std::string> options;
    std::vector<std::string> optionsGuest = {
        "SeeDirector", "SeeActor", "SeeProducer", "Browse", "Exit", "Reviews"};
    std::vector<std::string> optionsRest = {
        "AddReview", "SeeDirector", "SeeActor", "SeeProducer",
        "Browse",    "Exit",        "Reviews"};
    Film *film;
    void loadRevs();

   public:
    FilmPage(Film *f) : film(f) { loadRevs(); };
    void print() override;
    program_state nextAction() override;

    std::unique_ptr<Page> doAction(program_state,
                                   std::unique_ptr<Role> &us_ptr) override;
    void showOptions(const Role *us_ptr) override {
        if (us_ptr->getName() == "guest") {
            options = optionsGuest;
        } else {
            options = optionsRest;
        }
        std::cout << "Available Options: \n";
        for (auto opt : options) {
            std::cout << "- " << opt << std::endl;
        }
    }
};