#include "addReviewPage.h"
#include <fstream>
void AddReviewPage::print()
{
    std::cout << "Here you can add your review :)" << std::endl;
}

program_state AddReviewPage::nextAction()
{
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end())
    {
        cppIO::input("Enter desired action: ", action);
        // for (int i = 0; i < action.size(); ++i)
        // {
        //     action[i] = (char)tolower(action[i]);
        // }
    }
    if (action == "Exit")
    {
        return program_state::Exit;
    }
    else if (action == "Add")
    {
        return program_state::Add;
    }
    else if (action == "GoBack")
    {
        return program_state::GoBack;
    }
    return program_state::Exit;
}

unsigned int AddReviewPage::generateID()
{
    std::ifstream inputFile("../reviews.csv");
    std::string line;
    unsigned int count = 0;
    while (std::getline(inputFile, line))
    {
        count++;
    }
    return count;
}

std::unique_ptr<Page> AddReviewPage::doAction(program_state act, std::unique_ptr<Role> &us_ptr)
{
    if (act == program_state::GoBack)
    {
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    }
    else if (act == program_state::Add)
    {
        int rev = 11;
        while (rev > 10 || rev < 0)
        {
            cppIO::input("Enter score: ", rev);
        }
        std::string content;
        std::cout << "Your thoughts on the movie: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, content);
        unsigned int id = generateID();
        Review r(film, id, us_ptr->getUser()->getLogin(), rev, content);
        film->addReview(r);
        std::fstream f;
        f.open("../reviews.csv", std::ios::app);
        f << r << "\n";
        f.close();
        std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
        return ptr;
    }
    std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(film);
    return ptr;
}
