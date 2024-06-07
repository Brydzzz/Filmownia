#pragma once
#include "browsePage.h"
#include "filmPage.h"
#include "page.h"
class ReviewsPage : public Page {
    std::vector<std::string> options = {"Exit", "GoBack", "Browse"};
    Film *film;

   public:
    ReviewsPage(Film *film) : film(film){};
    void print() override;
    program_state nextAction() override;
    std::unique_ptr<Page> doAction(program_state,
                                   std::unique_ptr<Role> &us_ptr) override;
    void showOptions(const Role *us_ptr) override {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options) {
            std::cout << "- " << opt << std::endl;
        }
    }
};