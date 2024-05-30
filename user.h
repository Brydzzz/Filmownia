#pragma once
#include <ctype.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// tymczasowo zakładamy ze pierwsze dane w pliku to admin
class Role;
class User
{
    std::string login = "guest";
    Role *role;

public:
    User(){};
    const std::string &getLogin() const;
    void setLogin(std::string const &new_login);
    const Role *getRole() const;
    void setRole(Role *new_role);
    void log_in(std::string fname = "../passwords.txt");
    void log_out();
};