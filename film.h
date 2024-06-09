#pragma once
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "review.h"

enum class film_genre {
    Action,
    Adventure,
    Comedy,
    Drama,
    Fantasy,
    Horror,
    Mystery,
    Romance,
    SciFi,
    Thriller,
    Western,
    Unknown
};

class Review;
class Film {
    unsigned int id;
    std::string title;
    unsigned int prod_year;
    std::vector<film_genre> genre;
    std::map<std::string, std::string> cast;
    std::string desc;
    std::vector<Review> reviews;
    std::string director;
    std::map<std::string, std::string> writers;
    std::map<std::string, std::string> producers;
    unsigned int time;
    std::map<std::string, std::string> parsePeople(std::string &people);
    std::vector<film_genre> parseGenres(std::string &content);

   public:
    Film(unsigned int id, std::string title, unsigned int prod_year,
         std::vector<film_genre> genre, std::map<std::string, std::string> cast,
         std::string desc, std::vector<Review> reviews, unsigned int time,
         std::map<std::string, std::string> writers,
         std::map<std::string, std::string> producers, std::string director)
        : id(id),
          title(title),
          prod_year(prod_year),
          genre(genre),
          cast(cast),
          desc(desc),
          reviews(reviews),
          time(time),
          writers(writers),
          producers(producers),
          director(director) {}

    Film(unsigned int id, std::string title, unsigned int prod_year,
         std::string genre, std::string cast, std::string desc,
         std::vector<Review> reviews, unsigned int time, std::string writers,
         std::string producers, std::string director)
        : id(id),
          title(title),
          prod_year(prod_year),
          genre(parseGenres(genre)),
          cast(parsePeople(cast)),
          desc(desc),
          reviews(reviews),
          time(time),
          writers(parsePeople(writers)),
          producers(parsePeople(producers)),
          director(director) {}
    Film(){};
    void addReview(Review review);
    void addRole(std::string actor, std::string role);
    void deleteRole(std::string actor);
    void changeDirector(std::string new_director);
    void deleteDirector(std::string to_delete);
    void addProducer(std::string prod, std::string job);
    const unsigned int &getID() const;
    std::vector<Review> &getReviews();
    const std::string &getTitle() const;
    const unsigned int &getYear() const;
    const std::map<std::string, std::string> &getCast() const;
    const std::string &getDesc() const;
    const std::string &getDir() const;
    const unsigned int &getTime() const;
    const std::vector<film_genre> &getGenre() const;
    unsigned int getRating() const;
    friend bool operator==(const Film &lfilm, const Film &rfilm);
    friend std::ostream &operator<<(std::ostream &os, Film &fm);
    friend std::ostream &operator<<(std::ostream &os, Film *fm);
    friend std::istream &operator>>(std::istream &is, Film &fm);
    std::ostream &write(std::ostream &os);
    const std::map<std::string, std::string> &getWriters() const;
    const std::map<std::string, std::string> &getProducers() const;
};