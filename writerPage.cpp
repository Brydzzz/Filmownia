#include "writerPage.h"

#include "databaseManager.h"
#include "page.h"
program_state WriterPage::nextAction() {
    std::string action;
    bool condition =
        std::find(options.begin(), options.end(), action) == options.end();
    while (condition) {
        cppIO::input("Enter desired action: ", action);
        condition =
            std::find(options.begin(), options.end(), action) == options.end();
        if (condition) {
            cppIO::log(
                "No such option available for this user. Choose one from the "
                "list.");
        }
    }
    if (action == "Exit") {
        return program_state::Exit;
    } else if (action == "GoBack") {
        return program_state::GoBack;
    } else if (action == "SeeAllJobs") {
        return program_state::SeeAll;
    } else if (action == "AddJob") {
        return program_state::AddElement;
    } else if (action == "DeleteJob") {
        return program_state::DeleteElement;
    }
    return program_state::Exit;
}
std::unique_ptr<Page> WriterPage::doAction(program_state act,
                                           std::unique_ptr<Role> &us_ptr) {
    if (act == program_state::GoBack) {
        if (filmLink != nullptr) {
            std::unique_ptr<FilmPage> ptr =
                std::make_unique<FilmPage>(filmLink);
            return ptr;
        } else {
            std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
            return ptr;
        }
    } else if (act == program_state::SeeAll) {
        clearTerminal();
        writer.displayJobs(std::cout);
        waitForInput();

        std::unique_ptr<WriterPage> ptr =
            std::make_unique<WriterPage>(writer, filmLink);
        return ptr;
    } else if (act == program_state::AddElement) {
        DatabaseManager db_mgmt;
        int j = 0;
        while (j != 1 && j != 2 && j != 3) {
            cppIO::input(
                "Choose job: \n1. Screenplay \n2. Story \n3. Writer \n", j);
        }
        std::cout << "In movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string title;
        std::getline(std::cin, title);
        std::vector<Film *> foundFilms = findMovies(title);
        Film *f = chooseMovie(foundFilms);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<WriterPage> ptr =
                std::make_unique<WriterPage>(writer, filmLink);
            return ptr;
        }
        std::ostringstream os;
        os << writer;
        std::string oldRecord = os.str();
        WriterType wt = static_cast<WriterType>(j);
        try {
            writer.addJob(wt, *f);
        } catch (const std::invalid_argument &e) {
            std::cout << "Writer already has a job in this movie\n";
            waitForInput();
            std::unique_ptr<WriterPage> ptr =
                std::make_unique<WriterPage>(writer, filmLink);
            return ptr;
        }
        os.str("");
        os << writer;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::writersDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        // f->addWriter(writer.getName(), wtypeToString(wt));
        try {
            f->addWriter(writer.getName(), wtypeToString(wt));
            os.str("");
            os << f;
            std::string newMovie = os.str();
            db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        } catch (const std::invalid_argument &e) {
            std::cout << "This writer never had a job in this movie in the "
                         "first place\n";
            waitForInput();
            std::unique_ptr<WriterPage> ptr =
                std::make_unique<WriterPage>(writer, filmLink);
            return ptr;
        }
        // os.str("");
        // os << f;
        // std::string newMovie = os.str();
        // db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        std::unique_ptr<WriterPage> ptr =
            std::make_unique<WriterPage>(writer, filmLink);
        return ptr;
    } else if (act == program_state::DeleteElement) {
        DatabaseManager db_mgmt;
        std::string title;
        std::cout << "Delete job from movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, title);
        std::vector<Film *> foundFilms = writer.findFilmsByTitle(title);
        Film *f = chooseMovie(foundFilms);
        if (f == nullptr) {
            waitForInput();
            std::unique_ptr<WriterPage> ptr =
                std::make_unique<WriterPage>(writer, filmLink);
            return ptr;
        }
        std::ostringstream os;
        os << writer;
        std::string oldRecord = os.str();
        try {
            writer.deleteJob(*f);
        } catch (const std::invalid_argument &e) {
            std::cout << "This writer never worked onn this movie in the "
                         "first place\n";
            waitForInput();
            std::unique_ptr<WriterPage> ptr =
                std::make_unique<WriterPage>(writer, filmLink);
            return ptr;
        }
        os.str("");
        os << writer;
        std::string newRecord = os.str();
        db_mgmt.replaceLine(newRecord, oldRecord, whichDb::writersDb);
        os.str("");
        os << f;
        std::string oldMovie = os.str();
        try {
            f->deleteWriter(writer.getName());
            os.str("");
            os << f;
            std::string newMovie = os.str();
            db_mgmt.replaceLine(newMovie, oldMovie, whichDb::moviesDb);
        } catch (const std::invalid_argument &e) {
            std::cout << "This writer never had a job in this movie in the "
                         "first place\n";
            waitForInput();
            std::unique_ptr<WriterPage> ptr =
                std::make_unique<WriterPage>(writer, filmLink);
            return ptr;
        }
        std::unique_ptr<WriterPage> ptr =
            std::make_unique<WriterPage>(writer, filmLink);
        return ptr;
    } else if (act == program_state::Exit) {
        std::unique_ptr<WriterPage> ptr =
            std::make_unique<WriterPage>(writer, filmLink);
        return ptr;
    }

    std::unique_ptr<WriterPage> ptr =
        std::make_unique<WriterPage>(writer, filmLink);
    return ptr;
}

void WriterPage::print() {
    clearTerminal();
    printBorder();
    std::cout << "WRITER PAGE" << std::endl;
    printBorder();
    writer.displayWriterInfo(std::cout);
}