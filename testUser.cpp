#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "admin.h"
#include "guest.h"
#include "logged.h"
#include "role.h"
#include "user.h"
// std::cin for testing purposes
class InputSimulator
{
    std::istringstream input;

public:
    InputSimulator(const std::string &data) : input(data)
    {
        std::cin.rdbuf(input.rdbuf());
    }
};

TEST(userTest, defaultTest)
{
    User user;
    ASSERT_EQ(user.getLogin(), "guest");
};

TEST(userTest, logAdminTest)
{
    InputSimulator input("Admin\n0000\n");

    User user;
    user.log_in();

    ASSERT_EQ(user.getLogin(), "Admin");
    ASSERT_EQ(user.getRole()->getName(), "admin");
};

TEST(userTest, logLoggedTest)
{
    InputSimulator input("Lara\n1234\n");

    User user;
    user.log_in();

    ASSERT_EQ(user.getLogin(), "Lara");
    ASSERT_EQ(user.getRole()->getName(), "logged");
};

TEST(userTest, logIncorrectTest)
{
    InputSimulator input("Lara\n5678\n");

    User user;

    user.log_in();

    ASSERT_EQ(user.getLogin(), "guest");
    ASSERT_EQ(user.getRole()->getName(), "guest");
    // ASSERT_NE(output.find("Logged in as admin"), std::string::npos);
};

TEST(userTest, logOutTest)
{
    InputSimulator input("Lara\n1234\n");

    User user;

    user.log_in();

    ASSERT_EQ(user.getLogin(), "Lara");
    ASSERT_EQ(user.getRole()->getName(), "logged");

    user.log_out();
    ASSERT_EQ(user.getLogin(), "guest");
    ASSERT_EQ(user.getRole()->getName(), "guest");
};

// uwaga ten test wymaga sprawdzenia czy w pliku z hasłami nie ma takiego uytkownika w razie potrzeby usunąć tą linię z pliku
TEST(guestTest, gdefaultTest)
{
    User *user;
    InputSimulator input("Tom\n23ab\nTom\n23ab\n");
    Guest guest(user);
    guest.sign_up();
    guest.getUser()->log_in();
    ASSERT_EQ(guest.getUser()->getLogin(), "Tom");
    ASSERT_EQ(guest.getUser()->getRole()->getName(), "logged");
};

TEST(guestTest, takenLoginTest)
{
    User *user;
    InputSimulator input("Lara\n23ab\nLara\n23ab\n");
    Guest guest(user);
    guest.sign_up();
    guest.getUser()->log_in();
    ASSERT_EQ(guest.getUser()->getLogin(), "guest");
    ASSERT_EQ(guest.getName(), "guest");
};

TEST(loggedTest, ldefaultTest)
{
    User *user;
    Logged logged(user);
    ASSERT_EQ(logged.getReviews().size(), 0);
};

// TEST(loggedTest, constructor2Test) {
//     Review review;
//     Logged logged(review);
//     ASSERT_EQ(logged.getReviews().size(), 1);
// };