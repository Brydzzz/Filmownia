#include "film.cpp"
#include "role.cpp"

class Admin : public Role {
   public:
    Admin();
    void add_movie(const Film& new_film);
    void delete_movie(const Film& to_delete);
    void modify_movie(Film& to_modify);
};