#include "databaseManager.h"

#include <fstream>
#include <iostream>
#include <type_traits>
void DatabaseManager::replaceLine(std::string newLine, std::string oldLine,
                                  whichDb db) {
    std::ifstream fileHandler(enumDbToStr(db));
    if (!fileHandler.is_open()) {
        std::cerr << "Error when opening file" << std::endl;
        return;
    }
    std::string line;
    std::ofstream temp("../temp.txt");
    while (std::getline(fileHandler, line)) {
        if (line == oldLine) {
            temp << newLine << '\n';
        } else {
            temp << line << '\n';
        }
    }
    temp.close();
    fileHandler.close();
    std::ifstream temp2("../temp.txt", std::ios::in);
    std::ofstream fileHandler2(enumDbToStr(db), std::ios::out);
    while (std::getline(temp2, line)) {
        fileHandler2 << line << '\n';
    }
}

std::string DatabaseManager::enumDbToStr(whichDb db) {
    switch (db) {
        case whichDb::moviesDb:
            return moviesDb;
        case whichDb::actorsDb:
            return actorsDb;
        case whichDb::reviewsDb:
            return reviewsDb;
        case whichDb::directorsDb:
            return directorsDb;
        case whichDb::writersDb:
            return writersDb;
        default:
            return "Unknown";
    }
}

std::vector<Film *> DatabaseManager::movieSearch(const std::string &title) {
    auto it = flist.begin();
    std::vector<Film *> result = {};
    while (it != flist.end()) {
        it = std::find_if(it, flist.end(), [&](const Film &film) {
            return film.getTitle().find(title) != std::string::npos;
        });
        if (it == flist.end()) {
            break;
        }
        Film *f = &(*it);
        ++it;
        result.push_back(f);
    }
    return result;
}