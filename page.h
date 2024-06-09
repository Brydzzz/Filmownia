#pragma once
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

#include "admin.h"
#include "cppio.hpp"
#include "film.h"
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
    BrowseDirectors,
    BrowseProducers,
    BrowseWriters,
    AddRole,
    DeleteRole,
    SeeAll,
    AddDirectorFilm,
    DeleteDirectorFilm,
    SeeActor,
    SeeDirector,
    SeeProducer,
    SeeWriter,
    LogIn,
    SignUp,
    LogOut,
    AddJob,
    DeleleteJob,
};

class Page {
    std::vector<std::string> options;

   public:
    virtual void showOptions(const Role *us_ptr) {
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

void printBorder();

void waitForInput();

std::vector<Film *> findMovies(std::string title);

Film *chooseMovie(std::vector<Film *> films);
