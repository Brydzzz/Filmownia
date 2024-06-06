#include "global.h"
#include "csv.h"
#include "user.h"
#include "databaseManager.h"
#include "page.h"

std::vector<Film> loadFilms()
{
    std::vector<Film> list;
    io::CSVReader<10, io::trim_chars<' '>, io::no_quote_escape<';'>> in("../movies.csv");
    in.read_header(io::ignore_missing_column, "ID", "Title", "Genres", "Year", "Runtime", "Description", "Cast", "Director", "Writers", "Producers");
    unsigned int ID;
    std::string Title;
    std::string Genres;
    unsigned int Year;
    unsigned int Runtime;
    std::string Description;
    std::string Cast;
    std::string Director;
    std::string Writers;
    std::string Producers;
    while (in.read_row(ID, Title, Genres, Year, Runtime, Description, Cast, Director, Writers, Producers))
    {
        Film f(ID, Title, Year, Genres, Cast, Description, {}, Runtime, Writers, Producers, Director);
        list.push_back(f);
    }
    return list;
}
std::vector<Film> flist = loadFilms();

std::vector<Review> loadReviews(User &user)
{
    std::vector<Review> list;
    io::CSVReader<5, io::trim_chars<' '>, io::no_quote_escape<';'>> in("../reviews.csv");
    in.read_header(io::ignore_missing_column, "ID", "User", "Film_id", "Score", "Content");
    unsigned int ID;
    std::string User;
    unsigned int Film_id;
    unsigned int Score;
    std::string Content;
    while (in.read_row(ID, User, Film_id, Score, Content))
    {
        if (user.getLogin() == User)
        {
            auto it = flist.begin();
            it = std::find_if(it, flist.end(), [&](const Film &film)
                              { return film.getID() == Film_id; });
            Review r(&(*it), ID, User, Score, Content);
            list.push_back(r);
        }
    }
    return list;
}
