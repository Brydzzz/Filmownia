#pragma once
#include <limits>
#include <memory>

#include "film.h"
// #include "filmPage.h"
#include <algorithm>
#include <iostream>

#include "cppio.hpp"
// #include "main.cpp"

#include "admin.h"
#include "global.h"
#include "guest.h"
#include "logged.h"
#include "role.h"
#include "user.h"
enum class program_state {
    Browse,
    Exit,
    AddReview,
    Reviews,
    GoBack,
    MyPage,
    Add,
    BrowseMovies,
    BrowseActors,
    AddRole,
    DeleteRole,
    SeeAllRoles
};

class Page {
    std::vector<std::string> options;

   public:
    virtual void showOptions() {
        for (auto opt : options) {
            std::cout << opt << std::endl;
        }
    };
    virtual void print() = 0;
    virtual program_state nextAction() = 0;
    virtual std::unique_ptr<Page> doAction(program_state act,
                                           std::unique_ptr<Role> &us_ptr) = 0;
    virtual ~Page(){};
};

void clearTerminal();