#pragma once
#include "film.h"
#include "filmPage.h"
#include "page.h"
class AddReviewPage : public Page {
    std::vector<std::string> options = {"GoBack", "Exit", "Add"};
    Film *film;

   public:
    AddReviewPage(Film *film) : film(film){};
    void print() override;
    program_state nextAction() override;
    std::unique_ptr<Page> doAction(program_state act,
                                   std::unique_ptr<Role> &us_ptr) override;
    void showOptions(const Role *us_ptr) override {
        std::cout << "Available Options: \n";
        for (auto opt : options) {
            std::cout << "- " << opt << std::endl;
        }
    }
};