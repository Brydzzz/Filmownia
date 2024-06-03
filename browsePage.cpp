#include "browsePage.h"
#include "global.h"
extern std::vector<Film> flist;
std::vector<Film *> BrowsePage::movieSearch(const std::string &title)
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

std::unique_ptr<Page> BrowsePage::doAction(program_state act, std::unique_ptr<Role> &us_ptr)
{
    if (act == program_state::Browse)
    {
        std::string title;
        std::cout << "Searched movie: " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, title);
        // std::cin >> title1;
        // cppIO::input("Searched movie: ", title1, title2, title3, title4);
        std::vector<Film *> found = movieSearch(title);
        if (found.size() != 0)
        {
            int a;
            if (found.size() != 1)
            {
                std::cout << "Found movies: " << std::endl;
                int i = 1;

                for (auto f : found)
                {
                    if (i <= 10)
                    {
                        std::cout << i << '.' << f->getTitle() << std::endl;
                        ++i;
                    }
                }
                cppIO::input("Choose number of a movie you wish to see or -1 for exit: ", a);
                if (a == -1)
                {
                    std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
                    return ptr;
                }
            }
            else
            {
                a = 1;
            }
            a--;
            // std::cout << found[a].getDesc() << std::endl;
            std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(found[a]);
            return ptr;
        }
        else
        {
            std::cout << "Movie not found\n";
        }
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
    else if (act == program_state::Exit)
    {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
    else if (act == program_state::GoBack)
    {
        std::unique_ptr<Page> ptr = std::make_unique<StartPage>();
        return ptr;
    }
}

program_state BrowsePage::nextAction()
{
    std::string action;
    while (std::find(options.begin(), options.end(), action) == options.end())
    {
        cppIO::input("Enter desired action: ", action);
    }
    if (action == "Exit")
    {
        return program_state::Exit;
    }
    else if (action == "Browse")
    {
        return program_state::Browse;
    }
    else if (action == "GoBack")
    {
        return program_state::GoBack;
    }
    return program_state::Exit;
}