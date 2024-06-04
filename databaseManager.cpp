#include "databaseManager.h"
#include <fstream>
#include <iostream>
void DatabaseManager::replaceLine(std::string newLine, std::string oldLine, whichDb db)
{
    std::ifstream fileHandler(enumDbToStr(db));
    if (!fileHandler.is_open())
    {
        std::cerr << "Error when opening file" << std::endl;
        return;
    }
    std::string line;
    std::ofstream temp("../temp.txt");
    while (std::getline(fileHandler, line))
    {
        if (line == oldLine)
        {
            temp << newLine << '\n';
        }
        else
        {
            temp << line << '\n';
        }
    }
    temp.close();
    fileHandler.close();
    std::ifstream temp2("../temp.txt", std::ios::in);
    std::ofstream fileHandler2(enumDbToStr(db), std::ios::out);
    while (std::getline(temp2, line))
    {
        fileHandler2 << line << '\n';
    }
}

std::string DatabaseManager::enumDbToStr(whichDb db)
{
    switch (db)
    {
    case whichDb::moviesDb:
        return moviesDb;
    case whichDb::actorsDb:
        return actorsDb;
    case whichDb::reviewsDb:
        return reviewsDb;
    default:
        return "Unknown";
    }
}

std::vector<Film *> DatabaseManager::movieSearch(const std::string &title)
{
    auto it = flist.begin();
    std::vector<Film *> result = {};
    while (it != flist.end())
    {
        it = std::find_if(it, flist.end(), [&](const Film &film)
                          { return film.getTitle().find(title) != std::string::npos; });
        if (it == flist.end())
        {
            break;
        }
        Film *f = &(*it);
        ++it;
        result.push_back(f);
        // std::cout << f.getTitle() << std::endl;
    }
    return result;
}

std::vector<Actor> DatabaseManager::actorSearch(const std::string &name)
{
    std::vector<Actor> actors;
    io::CSVReader<4, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
        actorsDb);
    in.read_header(io::ignore_missing_column, "ID", "Name", "Birthday",
                   "Films");
    unsigned int ID;
    std::string Name;
    std::string Birthday;
    std::string Films;
    while (in.read_row(ID, Name, Birthday, Films))
    {
        if (Name.find(name) != std::string::npos)
        {
            Date BirthdayDate;
            std::istringstream bday(Birthday);
            bday >> BirthdayDate;
            Actor a(ID, Name, BirthdayDate, Films);
            actors.push_back(a);
        }
    }
    return actors;
}

void updateActors(const Actor *changedActor) {}