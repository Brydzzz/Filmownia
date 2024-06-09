#include "databaseManager.h"

#include <fstream>
#include <iostream>
#include <type_traits>

void DatabaseManager::appendToFile(whichDb db, std::string content) {
    std::fstream f;
    f.open("../reviews.csv", std::ios::app);
    f << content << "\n";
    f.close();
}

void DatabaseManager::deleteLine(std::string oldLine, whichDb db) {
    std::ifstream fileHandler(enumDbToStr(db));
    if (!fileHandler.is_open()) {
        std::cerr << "Error when opening file" << std::endl;
        return;
    }
    std::string line;
    std::ofstream temp("../temp.txt");
    while (std::getline(fileHandler, line)) {
        if (line == oldLine) {
            continue;
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

void DatabaseManager::loadRevs(Film *f) {
    if (f->getReviews().size() == 0) {
        io::CSVReader<5, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
            reviewsDb);
        in.read_header(io::ignore_missing_column, "ID", "User", "Film_id",
                       "Score", "Content");
        unsigned int ID;
        std::string User;
        unsigned int Film_id;
        unsigned int Score;
        std::string Content;
        while (in.read_row(ID, User, Film_id, Score, Content)) {
            if (Film_id == f->getID()) {
                Review r(f, ID, User, Score, Content);
                f->addReview(r);
            }
        }
    }
    return;
}

unsigned int DatabaseManager::generateReviewID() {
    unsigned int id = 0;
    io::CSVReader<5, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
        "../reviews.csv");
    in.read_header(io::ignore_missing_column, "ID", "User", "Film_id", "Score",
                   "Content");
    unsigned int ID;
    std::string User;
    unsigned int Film_id;
    unsigned int Score;
    std::string Content;
    while (in.read_row(ID, User, Film_id, Score, Content)) {
        id = ID;
    }
    id++;
    return id;
}
std::vector<Review> DatabaseManager::findReviews(std::string name) {
    std::vector<Review> list;
    io::CSVReader<5, io::trim_chars<' '>, io::no_quote_escape<';'>> in(
        "../reviews.csv");
    in.read_header(io::ignore_missing_column, "ID", "User", "Film_id", "Score",
                   "Content");
    unsigned int ID;
    std::string User;
    unsigned int Film_id;
    unsigned int Score;
    std::string Content;
    while (in.read_row(ID, User, Film_id, Score, Content)) {
        if (name == User) {
            auto it = flist.begin();
            it = std::find_if(it, flist.end(), [&](const Film &film) {
                return film.getID() == Film_id;
            });
            Review r(&(*it), ID, User, Score, Content);
            list.push_back(r);
        }
    }
    return list;
}
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
        case whichDb::producersDb:
            return producersDb;
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