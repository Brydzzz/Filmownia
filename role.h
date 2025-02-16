#pragma once
#include <string>

#include "user.h"

class User;
class Role {
   protected:
    User *user;
    std::string name = "guest";

   public:
    Role(User *us) : user(us){};
    virtual ~Role() = default;
    User *getUser();
    const std::string getName() const;
    void setName(const std::string &new_name);
};
