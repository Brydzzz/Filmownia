#include "csv.h"
#include "global.h"
#include "person.h"

enum class whichDb { moviesDb, actorsDb, reviewsDb, directorsDb, producersDb };

class DatabaseManager {
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
    template <typename T>
    std::vector<T> personSearch(const std::string &name) {
        std::vector<T> persons;
        std::string db;
        if constexpr (std::is_same<T, Producer>::value) {
            db = producersDb;
        } else if constexpr (std::is_same<T, Actor>::value) {
            db = actorsDb;
        } else if constexpr (std::is_same<T, Director>::value) {
            db = directorsDb;
        }
        io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'>> in(db);
        in.read_header(io::ignore_missing_column, "ID", "Name", "Birthday",
                       "Films");
        unsigned int ID;
        std::string Name;
        std::string Birthday;
        std::string Films;
        while (in.read_row(ID, Name, Birthday, Films)) {
            if (Name.find(name) != std::string::npos) {
                Date BirthdayDate;
                std::istringstream bday(Birthday);
                bday >> BirthdayDate;
                T p(ID, Name, BirthdayDate, Films);
                persons.push_back(p);
            }
        }
        return persons;
    }
};