#include <fstream>
#include <iostream>
#include <sstream>

#include "cppio.hpp"
#include "csv.h"
#include "film.h"
#include "person.h"
int main() {
    // std::string action;
    // cppIO::input("Enter desired action: ", action);
    // std::cout << action;
    // std::vector<Film> list;
    // io::CSVReader<10, io::trim_chars<' '>, io::no_quote_escape<';'>>
    // in("../movies.csv"); in.read_header(io::ignore_missing_column, "ID",
    // "Title", "Genres", "Year", "Runtime", "Description", "Cast", "Director",
    // "Writers", "Producers"); unsigned int ID; std::string Title; std::string
    // Genres; unsigned int Year; unsigned int Runtime; std::string Description;
    // std::string Cast;
    // std::string Director;
    // std::string Writers;
    // std::string Producers;
    // while (in.read_row(ID, Title, Genres, Year, Runtime, Description, Cast,
    // Director, Writers, Producers))
    // {
    //     Film f(ID, Title, Year, Genres, Cast, Description, {}, Runtime,
    //     Writers, Producers, Director); list.push_back(f);
    // }
    // std::vector<Actor> actors;
    // io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
    //     "../actors2.csv");
    // in.read_header(io::ignore_missing_column, "ID", "Name", "Birthday",
    //                "Films");
    // unsigned int ID;
    // std::string Name;
    // std::string Birthday;
    // std::string Films;
    // while (in.read_row(ID, Name, Birthday, Films)) {
    //     Date BirthdayDate;
    //     // if (Birthday.size() > 1) {
    //     //     std::istringstream bday(Birthday);
    //     //     bday >> BirthdayDate;
    //     // }
    //     std::istringstream bday(Birthday);
    //     bday >> BirthdayDate;
    //     Actor a(ID, Name, BirthdayDate, Films);
    //     actors.push_back(a);
    // }
    // std::ofstream out("../actors3.csv");
    // out << "ID;Name;Birthday;Films\n";
    // for (auto actor : actors) {
    //     out << actor << '\n';
    // }
    std::vector<Director> directors;
    io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
        "../directors.csv");
    in.read_header(io::ignore_missing_column, "ID", "Name", "Birthday",
                   "Films");
    unsigned int ID;
    std::string Name;
    std::string Birthday;
    std::string Films;
    while (in.read_row(ID, Name, Birthday, Films)) {
        Date BirthdayDate;
        // if (Birthday.size() > 1) {
        //     std::istringstream bday(Birthday);
        //     bday >> BirthdayDate;
        // }
        std::istringstream bday(Birthday);
        bday >> BirthdayDate;
        Director d(ID, Name, BirthdayDate, Films);
        directors.push_back(d);
    }
    std::ofstream out("../directors2.csv");
    out << "ID;Name;Birthday;Films\n";
    for (auto director : directors) {
        out << director << '\n';
    }
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

    // std::vector<Writer> writers;
    // io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
    //     "../writers.csv");
    // in.read_header(io::ignore_missing_column, "ID", "Name", "Birthday",
    //                "Films");
    // unsigned int ID;
    // std::string Name;
    // std::string Birthday;
    // std::string Films;
    // while (in.read_row(ID, Name, Birthday, Films))
    // {
    //     Date BirthdayDate;
    //     if (Birthday.size() == 4)
    //     {
    //         unsigned int year = std::stol(Birthday);
    //         BirthdayDate = Date(1, 1, year);
    //     }
    //     else if (Birthday.size() > 1)
    //     {
    //         std::istringstream bday(Birthday);
    //         bday >> BirthdayDate;
    //     }
    //     else
    //     {
    //         BirthdayDate = Date(1, 1, 1970);
    //     }
    //     std::cout << ID << std::endl;
    //     Writer w(ID, Name, BirthdayDate, Films);
    //     writers.push_back(w);
    // }
    // std::ofstream out("../writers3.csv");
    // out << "ID;Name;Birthday;Films\n";
    // for (auto writer : writers)
    // {
    //     out << writer << '\n';
    // }
    // std::vector<Producer> producers;
    // io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
    //     "../producers.csv");
    // in.read_header(io::ignore_missing_column, "ID", "Name", "Birthday",
    //                "Films");
    // unsigned int ID;
    // std::string Name;
    // std::string Birthday;
    // std::string Films;
    // while (in.read_row(ID, Name, Birthday, Films)) {
    //     Date BirthdayDate;
    //     if (Birthday.size() == 4) {
    //         unsigned int year = std::stol(Birthday);
    //         BirthdayDate = Date(1, 1, year);
    //     } else if (Birthday.size() > 1) {
    //         std::istringstream bday(Birthday);
    //         bday >> BirthdayDate;
    //     } else {
    //         BirthdayDate = Date(1, 1, 1970);
    //     }
    //     std::cout << ID << std::endl;
    //     Producer p(ID, Name, BirthdayDate, Films);
    //     producers.push_back(p);
    // }
    // std::ofstream out("../producers2.csv");
    // out << "ID;Name;Birthday;Films\n";
    // for (auto writer : producers) {
    //     out << writer << '\n';
    // }
    return 0;
}
