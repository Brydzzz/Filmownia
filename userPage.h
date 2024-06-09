#pragma once
#include <memory>

#include "csv.h"
#include "databaseManager.h"
#include "page.h"
#include "startPage.h"
class UserPage : public Page {
    std::vector<std::string> options = {"DeleteReview", "GoBack", "Exit"};
    std::string usr;
    std::vector<Review> revs;

   public:
    UserPage(std::string usr) : usr(usr) {
        DatabaseManager db_mgmt;
        revs = db_mgmt.findReviews(usr);
    };
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