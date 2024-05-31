
#include "global.h"
#include <memory>
#include "page.h"
#include "user.h"
#include "csv.h"
#include "film.h"
#include "startPage.h"
#include "browsePage.h"

// correct login: Lara, 1234

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
        pg_ptr = std::move(pg_ptr->doAction(act));
        pg_ptr->print();
        pg_ptr->showOptions();
        act = pg_ptr->nextAction();
    };
    std::cout << "Thank you for using Filmownia Software :)" << std::endl;
    return 0;
}