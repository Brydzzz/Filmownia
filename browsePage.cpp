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

std::unique_ptr<Page> BrowsePage::doAction(int act)
{
    if (act == 3)
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
            int a;
            cppIO::input("Choose number of a movie you wish to see or -1 for exit: ", a);
            if (a == -1)
            {
                std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
                return ptr;
            }
            else
            {
                a--;
                // std::cout << found[a].getDesc() << std::endl;
                std::unique_ptr<FilmPage> ptr = std::make_unique<FilmPage>(found[a]);
                return ptr;
            }
        }
        else
        {
            std::cout << "Movie not found\n";
        }
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
        return ptr;
    }
    else if (act == 0)
    {
        std::unique_ptr<BrowsePage> ptr = std::make_unique<BrowsePage>();
    }
}