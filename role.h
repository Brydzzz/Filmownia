#ifndef ROLE_H
#define ROLE_H

#include "film.cpp"
#include "review.cpp"

class User;
class Role {
   protected:
    User* user;

   public:
    Role() = default;
    User* getUser();
    void browse();
};

#endif