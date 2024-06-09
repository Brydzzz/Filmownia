#include "user.h"

#include <algorithm>

#include "admin.h"
#include "guest.h"
#include "logged.h"

const std::string &User::getLogin() const { return login; }
void User::setLogin(std::string const &new_login) { login = new_login; }

const Role *User::getRole() const { return role; }
void User::setRole(Role *new_role) { role = new_role; }

bool User::log_in(std::string fname) {
    std::vector<std::pair<std::string, std::string>> users;
    std::ifstream file(fname);
    if (!file) {
        std::cerr << "Could not open the file!" << std::endl;
        return false;
    }

    std::string user_login, user_password;
    while (file >> user_login >> user_password) {
        users.emplace_back(user_login, user_password);
    }
    std ::cout << "Login: \n";
    std::cin >> user_login;
    if (user_login == "-1") {
        setLogin("");
        return true;
    }
    std::cout << "Password: \n";
    std::cin >> user_password;
    std::pair<std::string, std::string> user_data = {user_login, user_password};
    auto it = std::find_if(
        users.begin(), users.end(),
        [user_data](const std::pair<std::string, std::string> &ud) {
            return (ud.first == user_data.first &&
                    ud.second == user_data.second);
        });
    if (it == users.end()) {
        setLogin("guest");
        if (role) {
            delete role;
        }
        Guest *guest = new Guest(this);
        setRole(dynamic_cast<Role *>(guest));
        role->setName("guest");
        return false;
    }

    else if (it == users.begin()) {
        setLogin(user_login);
        if (role) {
            delete role;
        }
        Admin *admin = new Admin(this);
        setRole(dynamic_cast<Role *>(admin));
        role->setName("admin");
    } else {
        setLogin(user_login);
        if (role) {
            delete role;
        }
        Logged *logged = new Logged(this);
        setRole(dynamic_cast<Role *>(logged));
        role->setName("logged");
    }
    return true;
}
void User::log_out() {
    if (role) {
        delete role;
    }
    login = "guest";
    Guest *guest = new Guest(this);
    setRole(dynamic_cast<Role *>(guest));
    role->setName("guest");
    std::cout << "Logged out successfully" << std::endl;
};
