
#include <memory>

#include "browsePage.h"
#include "csv.h"
#include "film.h"
#include "global.h"
#include "guest.h"
#include "logged.h"
#include "page.h"
#include "role.h"
#include "startPage.h"
#include "user.h"

// correct login: Lara, 1234
// extern std::vector<Review> loadReviews(User &user);
extern std::vector<Film> flist;
int main() {
    User user;
    Guest *guest = new Guest(&user);
    user.setRole(dynamic_cast<Role *>(guest));
    // user.log_in();
    // loadReviews(user);
    std::unique_ptr<Role> us_ptr = std::make_unique<Guest>(&user);
    // if (user.getRole()->getName() == "logged")
    // {
    //     us_ptr = std::make_unique<Logged>(&user, loadReviews(user));
    // }
    std::unique_ptr<Page> pg_ptr = std::make_unique<StartPage>();
    pg_ptr->print();
    pg_ptr->showOptions(user.getRole());
    program_state act;
    act = pg_ptr->nextAction();
    while (act != program_state::Exit) {
        pg_ptr = std::move(pg_ptr->doAction(act, us_ptr));
        pg_ptr->print();
        pg_ptr->showOptions(user.getRole());
        act = pg_ptr->nextAction();
    };
    std::cout << "Thank you for using Filmownia Software :)" << std::endl;
    delete guest;
    // user.log_out();
    return 0;
}
