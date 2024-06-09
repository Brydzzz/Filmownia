#include "review.h"

const Film *Review::getFilm() { return film; }

const unsigned int &Review::getScore() { return score; }

const std::string &Review::getContent() { return content; }

std::ostream &Review::write(std::ostream &os) {
    os << getUser() << ": " << getScore() << std::endl;
    os << getContent() << std::endl;
    return os;
}
bool operator==(const Review &lrev, const Review &rrev) {
    return lrev.getUser() == rrev.getUser();
}

const unsigned int &Review::getID() const { return id; }

const std::string &Review::getUser() const { return User; }

std::ostream &operator<<(std::ostream &os, Review &rev) {
    os << rev.getID() << ';';
    os << rev.getUser() << ';';
    os << rev.getFilm()->getID() << ';';
    os << rev.getScore() << ';';
    os << rev.getContent();
    return os;
}