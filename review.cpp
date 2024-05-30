#include "review.h"

const Film *Review::getFilm()
{
    return film;
}

const unsigned int &Review::getScore()
{
    return score;
}

const std::string &Review::getContent()
{
    return content;
}

std::ostream &operator<<(std::ostream &os, Review &rev)
{
    os << rev.getScore() << std::endl;
    os << rev.getContent() << std::endl;
    return os;
}
bool operator==(const Review &lrev, const Review &rrev)
{
    return lrev.getID() == rrev.getID();
}

const unsigned int &Review::getID() const
{
    return id;
}