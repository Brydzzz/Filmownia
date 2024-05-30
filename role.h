#pragma once
#ifndef ROLE_H
#define ROLE_H

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