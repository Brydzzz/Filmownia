#pragma once
#include "film.h"
#include "role.h"

class Admin : public Role {
   public:
    Admin(User *us) : Role(us){};
};