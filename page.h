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
    virtual int nextAction() = 0;
    virtual std::unique_ptr<Page> doAction(int act) = 0;
    virtual ~Page(){};
};
