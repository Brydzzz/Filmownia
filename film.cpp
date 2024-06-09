#include "film.h"

#include <iostream>

#include "cppio.hpp"
#include "csv.h"
void Film::addReview(Review review) { reviews.push_back(review); }

std::vector<Review> &Film::getReviews() { return reviews; }

const unsigned int &Film::getID() const { return id; }

const std::string &Film::getTitle() const { return title; }

const unsigned int &Film::getYear() const { return prod_year; }

const std::map<std::string, std::string> &Film::getCast() const { return cast; }
const std::string &Film::getDir() const { return director; }

const std::map<std::string, std::string> &Film::getWriters() const {
    return writers;
}

const std::map<std::string, std::string> &Film::getProducers() const {
    return producers;
}

const std::string &Film::getDesc() const { return desc; }
const unsigned int &Film::getTime() const { return time; }

const std::vector<film_genre> &Film::getGenre() const { return genre; }

unsigned int Film::getRating() const {
    int score = 0;
    int revs = 0;
    for (auto rev : reviews) {
        score += rev.getScore();
        revs++;
    }
    if (revs != 0) {
        return score / revs;
    }
    return 0;
}

bool operator==(const Film &lfilm, const Film &rfilm) {
    return lfilm.getID() == rfilm.getID();
}

void Film::deleteRole(std::string actor) {
    if (cast.count(actor) == 0) {
        throw std::invalid_argument("Actor doesn't have a role in this movie");
    }
    cast.erase(actor);
}
void Film::deleteProducer(std::string prod) {
    if (producers.count(prod) == 0) {
        throw std::invalid_argument(
            "Producer doesn't have a job in this movie");
    }
    producers.erase(prod);
}
void Film::addRole(std::string actor, std::string role) {
    if (cast.count(actor) != 0) {
        throw std::invalid_argument("Actor already has a role in this movie");
    }
    cast[actor] = role;
}

void Film::addProducer(std::string prod, std::string job) {
    if (producers.count(prod) != 0) {
        throw std::invalid_argument(
            "Producer already has a role in this movie");
    }
    producers[prod] = job;
}

void Film::addWriter(std::string writer, std::string job) {
    if (writers.count(writer) != 0) {
        throw std::invalid_argument("Writer already has a role in this movie");
    }
    writers[writer] = job;
}

void Film::deleteWriter(std::string writer) {
    if (writers.count(writer) == 0) {
        throw std::invalid_argument("Writer doesn't have a job in this movie");
    }
    writers.erase(writer);
}

void Film::changeDirector(std::string new_director) { director = new_director; }

void Film::deleteDirector(std::string to_delete) {
    if (director == to_delete) {
        director = "";
    } else {
        throw std::invalid_argument(
            "This director was never in this movie in the first place");
    }
}

film_genre toGenre(const std::string &genreStr) {
    if (genreStr == "Action") return film_genre::Action;
    if (genreStr == "Adventure") return film_genre::Adventure;
    if (genreStr == "Comedy") return film_genre::Comedy;
    if (genreStr == "Drama") return film_genre::Drama;
    if (genreStr == "Fantasy") return film_genre::Fantasy;
    if (genreStr == "Horror") return film_genre::Horror;
    if (genreStr == "Mystery") return film_genre::Mystery;
    if (genreStr == "Romance") return film_genre::Romance;
    if (genreStr == "Science Fiction") return film_genre::SciFi;
    if (genreStr == "Thriller") return film_genre::Thriller;
    if (genreStr == "Western") return film_genre::Western;
    return film_genre::Unknown;
}

std::vector<film_genre> Film::parseGenres(std::string &content) {
    char l1, l2;
    content.erase(content.size() - 1);
    std::stringstream s(content);
    std::string wtf = s.str();
    s >> l1;
    std::string genre;
    std::vector<film_genre> genres;
    while (std::getline(s, genre, ',')) {
        genre.erase(0, genre.find_first_not_of(" "));
        genre.erase(0, 1);
        genre.erase(genre.size() - 1);
        genres.push_back(toGenre(genre));
    }
    return genres;
}

std::map<std::string, std::string> Film::parsePeople(std::string &people) {
    char l1, l2;
    std::stringstream s(people);
    s >> l1;
    std::string actrole;
    std::map<std::string, std::string> ncast;
    while (std::getline(s, actrole, ']')) {
        actrole.erase(0, actrole.find_first_not_of(","));
        actrole.erase(0, actrole.find_first_not_of(" "));
        actrole.erase(0, actrole.find_first_not_of("["));
        std::stringstream ss(actrole);
        std::string name;
        std::getline(ss, name, ',');
        if (name.size() > 2) {
            std::string role;
            std::getline(ss, role, ',');
            role.erase(0, role.find_first_not_of(" "));
            ncast[name] = role;
        }
    }
    return ncast;
}

std::string gnrToStr(film_genre genre) {
    switch (genre) {
        case film_genre::Action:
            return "Action";
        case film_genre::Adventure:
            return "Adventure";
        case film_genre::Comedy:
            return "Comedy";
        case film_genre::Drama:
            return "Drama";
        case film_genre::Fantasy:
            return "Fantasy";
        case film_genre::Horror:
            return "Horror";
        case film_genre::Mystery:
            return "Mystery";
        case film_genre::Romance:
            return "Romance";
        case film_genre::SciFi:
            return "Science Fiction";
        case film_genre::Thriller:
            return "Thriller";
        case film_genre::Western:
            return "Western";
        default:
            return "Unknown";
    }
}

std::string strGenres(std::vector<film_genre> grs) {
    if (grs.size() == 0) {
        return "[]";
    }
    std::stringstream ss;
    ss << '[';
    for (auto g : grs) {
        ss << '\'' << gnrToStr(g) << '\'' << ", ";
    }
    std::string result = ss.str();
    result.resize(result.size() - 2);
    result += ']';
    return result;
}

std::string listToStr(std::map<std::string, std::string> mp) {
    std::stringstream ss;
    ss << '[';
    for (const auto &actrole : mp) {
        ss << '[';
        ss << actrole.first << ", " << actrole.second << ']' << ", ";
    }
    std::string result = ss.str();
    if (result.size() < 2) {
        return "[]";
    }
    result.resize(result.size() - 2);
    result += ']';
    return result;
}

std::ostream &Film::write(std::ostream &os) {
    os << std::quoted(getTitle()) << std::endl;
    os << "Release year: " << getYear() << "  " << "Runtime: " << getTime()
       << std::endl;
    os << "Genre: " << strGenres(getGenre()) << std::endl;
    os << "Rating: " << getRating() << std::endl;
    os << "Description: " << getDesc() << std::endl;
    os << "Director: " << getDir() << std::endl;
    os << "Producers: " << std::endl;
    unsigned int i = 1;
    for (auto person : getProducers()) {
        os << i << ". " << person.first << " - " << person.second << ", ";
        ++i;
    }
    os << std::endl;
    os << "Writers: " << std::endl;
    i = 1;
    for (auto person : getWriters()) {
        os << i << ". " << person.first << " - " << person.second << ", ";
        ++i;
    }
    i = 1;
    os << std::endl;
    os << "Cast: " << std::endl;
    for (auto person : getCast()) {
        os << i << ". " << person.first << " - " << person.second << std::endl;
        ++i;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, Film &fm) {
    Film *f = &fm;
    os << f;
    return os;
}

std::ostream &operator<<(std::ostream &os, Film *fm) {
    os << std::to_string(fm->getID()) << ';';
    os << fm->getTitle() << ';';
    os << strGenres(fm->getGenre()) << ';';
    os << fm->getYear() << ';';
    os << fm->getTime() << ';';
    os << fm->getDesc() << ';';
    os << listToStr(fm->getCast()) << ';';
    os << fm->getDir() << ';';
    os << listToStr(fm->getWriters()) << ';';
    os << listToStr(fm->getProducers());
    return os;
}

std::istream &operator>>(std::istream &is, Film &fm) {
    std::stringstream ss;
    ss << is.rdbuf();
    std::string content(ss.str());
    std::vector<std::string> row;
    std::string field;
    while (std::getline(ss, field, ';')) {
        row.push_back(field);
    }
    unsigned int id = static_cast<unsigned int>(std::stoi(row[0]));
    std::string title = row[1];
    std::vector<film_genre> genres = fm.parseGenres(row[2]);
    unsigned int year = static_cast<unsigned int>(std::stoi(row[3]));
    unsigned int runtime = 0;
    if (row[4].size() > 0) {
        runtime = static_cast<unsigned int>(std::stoi(row[4]));
    }
    std::string desc = row[5];
    std::map<std::string, std::string> cast = {};
    std::map<std::string, std::string> writers = {};
    std::map<std::string, std::string> producers = {};
    if (row[6].size() > 0)
        cast = fm.parsePeople(row[6].erase(row[6].size() - 1));
    std::string director = row[7];
    if (row[8].size() > 0)
        writers = fm.parsePeople(row[8].erase(row[8].size() - 1));
    if (row[9].size() > 0)
        producers = fm.parsePeople(row[9].erase(row[9].size() - 1));
    fm = Film(id, title, year, genres, cast, desc, {}, runtime, writers,
              producers, director);
    return is;
}