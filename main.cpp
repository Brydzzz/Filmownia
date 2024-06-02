
#include "global.h"
#include <memory>
#include "page.h"
#include "user.h"
#include "csv.h"
#include "film.h"
#include "startPage.h"
#include "browsePage.h"
#include "role.h"
#include "logged.h"
#include "guest.h"

// correct login: Lara, 1234
extern std::vector<Review> loadReviews(User &user);
extern std::vector<Film> flist;
int main()
{
    User user;
    user.log_in();
    loadReviews(user);
    std::unique_ptr<Role> us_ptr = std::make_unique<Guest>(&user);
    if (user.getRole()->getName() == "logged")
    {
        us_ptr = std::make_unique<Logged>(&user, loadReviews(user));
    }
    std::unique_ptr<Page> pg_ptr = std::make_unique<StartPage>();
    pg_ptr->print();
    pg_ptr->showOptions();
    program_state act;
    act = pg_ptr->nextAction();
    while (act != program_state::Exit)
    {
        pg_ptr = std::move(pg_ptr->doAction(act, us_ptr));
        pg_ptr->print();
        pg_ptr->showOptions();
        act = pg_ptr->nextAction();
    };
    std::cout << "Thank you for using Filmownia Software :)" << std::endl;
    // user.log_out();
    return 0;
}
