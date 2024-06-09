#pragma once
#include <sstream>
#include <string>

#include "film.h"
class Film;

class Review
{
    Film *film;
    unsigned int id;
    std::string User;
    unsigned int score;
    std::string content;

public:
    Review(Film *film, unsigned int id, std::string User, unsigned int score,
           std::string content)
        : film(film), id(id), User(User), score(score), content(content) {}
    const unsigned int &getID() const;
    Film *getFilm();
    const unsigned int &getScore();
    const std::string &getContent();
    const std::string &getUser() const;
    std::ostream &write(std::ostream &os);
    friend bool operator==(const Review &lrev, const Review &rrev);
    friend std::ostream &operator<<(std::ostream &os, Review &rev);
};
