#pragma once
#include <memory>
#include <limits>
#include "film.h"
#include "iostream"
#include "cppio.hpp"
#include "algorithm"
// #include "main.cpp"
extern std::vector<Film> flist;
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
    std::unique_ptr<Page> doAction(int act) override
    {
    }
    void showOptions()
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << opt << std::endl;
        }
    }
};
class BrowsePage : public Page
{
    std::string msg = "Browse Movies: ";
    std::vector<std::string> options = {"Exit", "Browse"};

public:
    void print() override
    {
        std::cout << msg << std::endl;
    }
    std::vector<Film> movieSearch(const std::string &title)
    {
        auto it = flist.begin();
        std::vector<Film> result = {};
        while (it != flist.end())
        {
            it = std::find_if(it, flist.end(), [&](const Film &film)
                              { return film.getTitle().find(title) != std::string::npos; });
            if (it == flist.end())
            {
                break;
            }
            Film f = *it;
            ++it;
            result.push_back(f);
            // std::cout << f.getTitle() << std::endl;
        }
        return result;
    }
    std::unique_ptr<Page> doAction(int act) override
    {
        if (act == 3)
        {
            std::string title;
            std::cout << "Searched movie: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, title);
            // std::cin >> title1;
            // cppIO::input("Searched movie: ", title1, title2, title3, title4);
            std::vector<Film> found = movieSearch(title);
            if (found.size() != 0)
            {
                std::cout << "Found movies: " << std::endl;
                int i = 1;
                for (auto f : found)
                {
                    if (i <= 10)
                    {
                        std::cout << i << '.' << f.getTitle() << std::endl;
                        ++i;
                    }
                }
            }
            else
            {
                std::cout << "Movie not found\n";
            }
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
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
            return 0;
        }
        else if (action == "Browse")
        {
            return 3;
        }
        return 5;
    }
    void showOptions()
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << opt << std::endl;
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
    std::unique_ptr<Page> doAction(int act) override
    {
        if (act == 4)
        {
            std::unique_ptr<BrowsePage> ptr;
            ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    }
    void print() override
    {
        std::cout << msg << std::endl;
    }
    void showOptions()
    {
        std::cout << "Avaiable Options: \n";
        for (auto opt : options)
        {
            std::cout << opt << std::endl;
        }
    }
};
