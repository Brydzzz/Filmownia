#include <gtest/gtest.h>
#include "user.h"
#include <sstream>
#include <iostream>

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
    User<std::string> user;
    ASSERT_EQ(user.getLogin(), "");
    ASSERT_EQ(user.getType(), "");
};

TEST(userTest, logAdminTest)
{
    InputSimulator input("Admin\n0000\n");

    User<std::string> user;
    user.log();

    ASSERT_EQ(user.getLogin(), "Admin");
    ASSERT_EQ(user.getType(), "admin");
};
TEST(userTest, logLoggedTest)
{
    InputSimulator input("Lara\n1234\n");

    User<std::string> user;
    user.log();

    ASSERT_EQ(user.getLogin(), "Lara");
    ASSERT_EQ(user.getType(), "logged");
};

TEST(userTest, logIncorrectTest)
{
    InputSimulator input("Lara\n5678\n");

    User<std::string> user;

    user.log();

    ASSERT_EQ(user.getLogin(), "");
    ASSERT_EQ(user.getType(), "");
    // ASSERT_NE(output.find("Logged in as admin"), std::string::npos);
};

TEST(userTest, logOutTest)
{
    InputSimulator input("Lara\n1234\n");

    User<std::string> user;

    user.log();

    ASSERT_EQ(user.getLogin(), "Lara");
    ASSERT_EQ(user.getType(), "logged");

    user.logout();
    ASSERT_EQ(user.getLogin(), "");
    ASSERT_EQ(user.getType(), "");
};