#pragma once
#include <memory>
#include "page.h"
#include "user.h"
#include "csv.h"
#include "film.h"
// correct login: Lara, 1234
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
int main()
{
    User user;
    user.log_in();
    std::unique_ptr<Page> pg_ptr = std::make_unique<StartPage>();
    pg_ptr->print();
    int act = 0;
    act = pg_ptr->nextAction();
    while (act != 0)
    {
        pg_ptr = std::move(pg_ptr->doAction(act));
        pg_ptr->print();
        pg_ptr->showOptions();
        act = pg_ptr->nextAction();
    };
    return 0;
}