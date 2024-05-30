#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "user.cpp"

// std::cin for testing purposes
class InputSimulator {
    std::istringstream input;

   public:
    InputSimulator(const std::string &data) : input(data) {
        std::cin.rdbuf(input.rdbuf());
    }
};

TEST(userTest, defaultTest) {
    User user;
    ASSERT_EQ(user.getLogin(), "");
    Role defaultRole;
    ASSERT_EQ(user.getRole(), &defaultRole);
};

TEST(userTest, logAdminTest) {
    InputSimulator input("Admin\n0000\n");

    User user;
    user.log_in();
    Admin admin;

    ASSERT_EQ(user.getLogin(), "Admin");
    ASSERT_EQ(user.getRole(), dynamic_cast<Role *>(&admin));
};
TEST(userTest, logLoggedTest) {
    InputSimulator input("Lara\n1234\n");

    User user;
    user.log_in();
    Logged logged;

    ASSERT_EQ(user.getLogin(), "Lara");
    ASSERT_EQ(user.getRole(), dynamic_cast<Role *>(&logged));
};

TEST(userTest, logIncorrectTest) {
    InputSimulator input("Lara\n5678\n");

    User user;

    user.log_in();

    Role defaultRole;

    ASSERT_EQ(user.getLogin(), "");
    ASSERT_EQ(user.getRole(), &defaultRole);
    // ASSERT_NE(output.find("Logged in as admin"), std::string::npos);
};

TEST(userTest, logOutTest) {
    InputSimulator input("Lara\n1234\n");

    User user;

    user.log_in();
    Logged logged;

    ASSERT_EQ(user.getLogin(), "Lara");
    ASSERT_EQ(user.getRole(), dynamic_cast<Role *>(&logged));

    Role defaultRole;
    user.log_out();
    ASSERT_EQ(user.getLogin(), "");
    ASSERT_EQ(user.getRole(), &defaultRole);
};

TEST(guestTest, gdefaultTest) {
    InputSimulator input("Tom\n23ab\nTom\n23ab\n");
    Guest guest;
    guest.sign_up();
    guest.getUser()->log_in();
    Logged logged;
    ASSERT_EQ(guest.getUser()->getLogin(), "Tom");
    ASSERT_EQ(guest.getUser()->getRole(), dynamic_cast<Role *>(&logged));
};

TEST(guestTest, takenLoginTest) {
    InputSimulator input("Lara\n23ab\nLara\n23ab\n");
    Guest guest;
    guest.sign_up();
    guest.getUser()->log_in();
    Role defaultRole;
    ASSERT_EQ(guest.getUser()->getLogin(), "");
    ASSERT_EQ(guest.getUser()->getRole(), &defaultRole);
};

TEST(loggedTest, ldefaultTest) {
    Logged logged;
    ASSERT_EQ(logged.getReviews().size(), 0);
};

// TEST(loggedTest, constructor2Test) {
//     Review review;
//     Logged logged(review);
//     ASSERT_EQ(logged.getReviews().size(), 1);
// };