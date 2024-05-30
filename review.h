#pragma once
#include <string>
#include <sstream>
class Film;

class Review
{
    Film &film;
    unsigned int id;
    std::string User;
    unsigned int score;
    std::string content;

public:
    Review(Film &film, unsigned int id, std::string User, unsigned int score, std::string content)
        : film(film), id(id), User(User), score(score), content(content)
    {
    }
    const unsigned int &getID() const;
    const Film &getFilm();
    const unsigned int &getScore();
    friend std::ostream &operator<<(std::ostream &os, Review &rev);
    const std::string &getContent();
    friend bool operator==(const Review &lrev, const Review &rrev);
};
