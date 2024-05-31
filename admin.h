#pragma once
#include "film.h"
#include "role.h"

class Admin : public Role
{
public:
    Admin(User *us) : Role(us){};
    void add_movie(const Film &new_film);
    void delete_movie(const Film &to_delete);
    void modify_movie(Film &to_modify);
};