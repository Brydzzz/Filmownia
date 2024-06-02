#include "film.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "csv.h"
#include "cppio.hpp"

int main()
{
    std::string action;
    cppIO::input("Enter desired action: ", action);
    std::cout << action;
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
    // std::ofstream out("../movies2.csv");
    // out << "ID;Title;Genres;Year;Runtime;Description;Cast;Director;Writers;Producers\n";
    // for (auto film : list)
    // {
    //     out << film << '\n';
    // }

    // std::ifstream input("../movies.csv");
    // if (!input.is_open())
    // {
    //     std::cerr << "Unable to open file movies.csv";
    // }
    // std::string row;
    // getline(input, row, '\n');
    // while (getline(input, row, '\n'))
    // {
    //     if (row == "")
    //         break;
    //     Film f;
    //     std::istringstream(row) >> f;
    //     list.push_back(f);
    return 0;
}
