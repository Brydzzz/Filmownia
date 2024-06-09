#pragma once
#include <ctype.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// pierwsze dane w pliku z hasłami to admin
class Role;
class User {
   private:
    std::string login = "guest";
    Role *role = nullptr;

   public:
    User() = default;
    ~User() = default;
    const std::string &getLogin() const;
    void setLogin(std::string const &new_login);
    const Role *getRole() const;
    void setRole(Role *new_role);
    bool log_in(std::string fname = "../passwords.txt");
    void log_out();
};