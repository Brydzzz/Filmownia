#pragma once
#include <string>

#include "role.h"
class Guest : public Role {
   public:
    Guest(User *us) : Role(us){};
    bool sign_up(std::string fname = "../passwords.txt");
};