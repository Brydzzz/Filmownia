#include "guest.h"

#include "user.h"

void Guest::sign_up(std::string fname) {
    std::string user_login, user_password;
    std ::cout << "Login: \n";
    std::cin >> user_login;
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
                return;
            }
        }
        infile.close();
    } else {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }
    user->setLogin(user_login);
    std::ofstream file;
    file.open(fname, std::ios::app);  // Open in append mode

    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }
    file << "\n" << user_login << " " << user_password;
    file.close();
}