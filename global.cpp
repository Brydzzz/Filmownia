#include "global.h"
#include "csv.h"

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
