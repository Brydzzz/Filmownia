#include <memory>
#include "page.h"
#include "user.h"
class InputSimulator
{
    std::istringstream input;

public:
    InputSimulator(const std::string &data) : input(data)
    {
        std::cin.rdbuf(input.rdbuf());
    }
};

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
    };
    return 0;
}