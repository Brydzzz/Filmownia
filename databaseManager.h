#include "csv.h"
#include "global.h"
#include "person.h"
enum class whichDb
{
    moviesDb,
    actorsDb,
    reviewsDb,
    directorsDb
};

class DatabaseManager
{
    std::string moviesDb;
    std::string actorsDb;
    std::string reviewsDb;
    std::string directorsDb;
    std::string enumDbToStr(whichDb db);

public:
    DatabaseManager(std::string moviesDb = "../movies.csv",
                    std::string actorsDb = "../actors.csv",
                    std::string reviewsDb = "../reviews.csv",
                    std::string directorsDb = "../directors.csv")
        : moviesDb(moviesDb),
          actorsDb(actorsDb),
          reviewsDb(reviewsDb),
          directorsDb(directorsDb){};
    std::vector<Film *> movieSearch(const std::string &title);
    std::vector<Actor> actorSearch(const std::string &name);
    std::vector<Director> directorSearch(const std::string &name);
    void replaceLine(std::string newLine, std::string oldLine, whichDb db);
};