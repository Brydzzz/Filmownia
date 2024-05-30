#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <ctype.h>

// tymczasowo zakładamy ze pierwsze dane w pliku to admin

template <typename T>
class User
{
    std::string login;
    // std::string password;
    T type;

public:
    User() : type() {}
    const std::string &getLogin() const
    {
        return login;
    }
    const T &getType() const
    {
        return type;
    }
    void log(std::string fname = "../passwords.txt")
    {
        std::vector<std::pair<std::string, std::string>> users;
        std::ifstream file(fname);
        if (!file)
        {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }

        std::string user_login, user_password;
        while (file >> user_login >> user_password)
        {
            users.emplace_back(user_login, user_password);
        }
        std ::cout << "Login: \n";
        std::cin >> user_login;
        std::cout << "Password: \n";
        std::cin >> user_password;
        std::pair<std::string, std::string> user_data = {user_login, user_password};
        auto it = std::find_if(users.begin(), users.end(), [user_data](const std::pair<std::string, std::string> &ud)
                               { return (ud.first == user_data.first && ud.second == user_data.second); });
        if (it == users.end())
        {
            std::cout << "User not found" << std::endl;
        }

        else if (it == users.begin())
        {
            login = user_login;
            type = "admin"; // tymczasowo potem będą klasy
        }
        else
        {
            login = user_login;
            type = "logged";
        }
    }
    void logout()
    {
        login.clear();
        // password.clear();
        type = T(); // Reset type to its default value
        std::cout << "Logged out successfully" << std::endl;
    }
};