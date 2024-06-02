#pragma once
#include <memory>
#include <limits>
#include "film.h"
// #include "filmPage.h"
#include <iostream>
#include "cppio.hpp"
#include <algorithm>
// #include "main.cpp"
#include "global.h"
#include "user.h"
#include "role.h"
#include "logged.h"
#include "guest.h"
#include "admin.h"
enum class program_state
{
    Browse,
    Exit,
    AddReview,
};

class Page
{
    std::vector<std::string> options;

public:
    virtual void showOptions()
    {
        for (auto opt : options)
        {
            std::cout << opt << std::endl;
        }
    };
    virtual void print() = 0;
    virtual program_state nextAction() = 0;
    virtual std::unique_ptr<Page> doAction(program_state act, std::unique_ptr<Role> &us_ptr) = 0;
    virtual ~Page(){};
};
