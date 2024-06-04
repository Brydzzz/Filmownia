#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "admin.h"
#include "guest.h"
#include "logged.h"
#include "role.h"
#include "user.h"
#include "review.h"
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

// uwaga ten test wymaga pliku testowego testlogin.txt
TEST(guestTest, gdefaultTest)
{
    // reseting test file
    std::ofstream file;
    file.open("../testlogin.txt", std::ios::out); // Open in write mode
    if (!file.is_open())
    {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }
    else
    {
        file << "Lara" << " " << "1234"; // we can do that only because it's a test file
        file.close();
    }
    User user;
    InputSimulator input("Tom\n23ab\nTom\n23ab\n");
    Guest guest(&user);
    guest.getUser();
    guest.sign_up("../testlogin.txt");
    guest.getUser()->log_in("../testlogin.txt");
    ASSERT_EQ(guest.getUser()->getLogin(), "Tom");
    ASSERT_EQ(guest.getUser()->getRole()->getName(), "logged");
};

TEST(guestTest, takenLoginTest)
{
    User user;
    InputSimulator input("Lara\n23ab\nLara\n23ab\n");
    Guest guest(&user);
    guest.sign_up("../testlogin.txt");
    guest.getUser()->log_in("../testlogin.txt");
    ASSERT_EQ(guest.getUser()->getLogin(), "guest");
    ASSERT_EQ(guest.getName(), "guest");
};

TEST(loggedTest, ldefaultTest)
{
    User user;
    Logged logged(&user);
    ASSERT_EQ(logged.getReviews().size(), 0);
};

// TEST(loggedTest, constructor2Test)
// {
//     Review review;
//     Logged logged(review);
//     ASSERT_EQ(logged.getReviews().size(), 1);
// };