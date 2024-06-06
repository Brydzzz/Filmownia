#include "csv.h"
#include "global.h"
#include "person.h"

enum class whichDb
{
    moviesDb,
    actorsDb,
    reviewsDb,
    directorsDb,
    producersDb
};

class DatabaseManager
{
    std::string moviesDb;
    std::string actorsDb;
    std::string reviewsDb;
    std::string directorsDb;
    std::string producersDb;
    std::string enumDbToStr(whichDb db);

public:
    DatabaseManager(std::string moviesDb = "../movies.csv",
                    std::string actorsDb = "../actors.csv",
                    std::string reviewsDb = "../reviews.csv",
                    std::string directorsDb = "../directors.csv",
                    std::string producersDb = "../producers.csv")
        : moviesDb(moviesDb),
          actorsDb(actorsDb),
          reviewsDb(reviewsDb),
          directorsDb(directorsDb),
          producersDb(producersDb){};
    std::vector<Film *> movieSearch(const std::string &title);
    std::vector<Actor> actorSearch(const std::string &name);
    std::vector<Director> directorSearch(const std::string &name);
    std::vector<Producer> producerSearch(const std::string &name);
    void replaceLine(std::string newLine, std::string oldLine, whichDb db);
};