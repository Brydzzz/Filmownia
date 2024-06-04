#include "csv.h"
#include "global.h"
#include "person.h"
class DatabaseManager
{
    std::string moviesDb;
    std::string actorsDb;
    std::string reviewsDb;

public:
    DatabaseManager(std::string moviesDb = "movies.csv", std::string actorsDb = "actors2.csv", std::string reviewsDb = "reviews.csv")
        : moviesDb(moviesDb), actorsDb(actorsDb), reviewsDb(reviewsDb){};
    std::vector<Film *> movieSearch(const std::string &title);
    std::vector<Actor> actorSearch(const std::string &name);
    void replaceLine(std::string newLine);
};