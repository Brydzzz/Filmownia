#include "guest.h"

#include "user.h"

bool Guest::sign_up(std::string fname) {
    std::string user_login, user_password;
    std ::cout << "Login: \n";
    std::cin >> user_login;
    if (user_login == "-1") {
        getUser()->setLogin("");
        return true;
    }
    std::cout << "Password: \n";
    std::cin >> user_password;

    // Check if the login is already taken
    std::ifstream infile(fname);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            if (line.find(user_login) != std::string::npos) {
                std::cerr << "Login already taken, please choose another one."
                          << std::endl;
                infile.close();
                return false;
            }
        }
        infile.close();
    } else {
        std::cerr << "Could not open the file!" << std::endl;
        return false;
    }
    user->setLogin(user_login);
    std::ofstream file;
    file.open(fname, std::ios::app);  // Open in append mode

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return false;
    }
    file << "\n" << user_login << " " << user_password;
    file.close();
    return true;
}