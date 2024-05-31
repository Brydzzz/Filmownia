#pragma once
#include "film.h"
#include "iostream"
#include "cppio.hpp"
#include "algorithm"
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
};

class FilmPage : public Page
{
    std::vector<std::string> options = {"AddReview", "SeeActor", "Browse", "Exit"};
    Film *film;

public:
    void print() override
    {
        film->write(std::cout);
    }
    int nextAction() override
    {
        std::string action;
        while (std::find(options.begin(), options.end(), action) == options.end())
        {
            cppIO::input("Enter desired action: ", action);
        }
        if (action == "Exit")
        {
            return 3;
        }
    }
};

class StartPage : public Page
{
    std::vector<std::string> options = {"Browse",
                                        "Exit"};
    std::string msg = "Welcome to Filmownia movie database!\nPresented to you by: Brygida S, Kinga Ł and Tomasz S\n";

public:
    int nextAction() override
    {
        std::string action;
        while (std::find(options.begin(), options.end(), action) == options.end())
        {
            cppIO::input("Enter desired action: ", action);
        }
        if (action == "Exit")
        {
            return 5;
        }
        else if (action == "Browse")
        {
            return 4;
        }
        return 0;
    }
    void print() override
    {
        std::cout << msg << std::endl;
    }
};