#pragma once
#include <string>

#include "role.h"
class Guest : public Role {
   public:
    Guest();
    void sign_up(std::string fname = "../passwords.txt");
};