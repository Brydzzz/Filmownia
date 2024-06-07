#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "admin.h"
#include "guest.h"
#include "logged.h"
#include "review.h"
#include "role.h"
#include "user.h"
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
    ASSERT_EQ(user.getLogin(), "guest");
};

TEST(userTest, logAdminTest) {
    InputSimulator input("Admin\n0000\n");

    User user;
    user.log_in();

    ASSERT_EQ(user.getLogin(), "Admin");
    ASSERT_EQ(user.getRole()->getName(), "admin");
};

TEST(userTest, logLoggedTest) {
    InputSimulator input("Lara\n1234\n");

    User user;
    user.log_in();

    ASSERT_EQ(user.getLogin(), "Lara");
    ASSERT_EQ(user.getRole()->getName(), "logged");
};

TEST(userTest, logIncorrectTest) {
    InputSimulator input("Lara\n5678\n");

    User user;

    user.log_in();

    ASSERT_EQ(user.getLogin(), "guest");
    ASSERT_EQ(user.getRole()->getName(), "guest");
    // ASSERT_NE(output.find("Logged in as admin"), std::string::npos);
};

TEST(userTest, logOutTest) {
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
TEST(guestTest, gdefaultTest) {
    // reseting test file
    std::ofstream file;
    file.open("../testlogin.txt", std::ios::out);  // Open in write mode
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    } else {
        file << "Lara" << " "
             << "1234";  // we can do that only because it's a test file
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

TEST(guestTest, takenLoginTest) {
    User user;
    InputSimulator input("Lara\n23ab\nLara\n23ab\n");
    Guest guest(&user);
    guest.sign_up("../testlogin.txt");
    guest.getUser()->log_in("../testlogin.txt");
    ASSERT_EQ(guest.getUser()->getLogin(), "guest");
    ASSERT_EQ(guest.getName(), "guest");
};

TEST(loggedTest, ldefaultTest) {
    User user;
    Logged logged(&user);
    ASSERT_EQ(logged.getReviews().size(), 0);
};

TEST(loggedTest, constructor2Test) {
    User user;
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    Review review(&f, 1, "Tomek", 4, "Good");
    Logged logged(&user, review);
    ASSERT_EQ(logged.getReviews().size(), 1);
};

TEST(loggedTest, constructor3Test) {
    User user;
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    std::vector<Review> reviews;
    Review review1(&f, 1, "Tomek", 4, "Good");
    Review review2(&f, 2, "Adam", 1, "Bad");
    reviews.push_back(review1);
    reviews.push_back(review2);
    Logged logged(&user, reviews);
    ASSERT_EQ(logged.getReviews().size(), 2);
};

TEST(loggedTest, setReviewsTest) {
    User user;
    Logged logged(&user);
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    std::vector<Review> reviews;
    Review review1(&f, 1, "Tomek", 4, "Good");
    Review review2(&f, 2, "Adam", 1, "Bad");
    reviews.push_back(review1);
    reviews.push_back(review2);
    logged.setReviews(reviews);
    ASSERT_EQ(logged.getReviews().size(), 2);
};

TEST(loggedTest, addReviewTest) {
    User user;
    Logged logged(&user);
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    Review review1(&f, 1, "Tomek", 4, "Good");
    logged.add_review(review1);
    ASSERT_EQ(logged.getReviews().size(), 1);
};

TEST(loggedTest, deleteReviewTest) {
    User user;
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    std::vector<Review> reviews;
    Review review1(&f, 1, "Tomek", 4, "Good");
    Review review2(&f, 2, "Adam", 1, "Bad");
    reviews.push_back(review1);
    reviews.push_back(review2);
    Logged logged(&user, reviews);
    ASSERT_EQ(logged.getReviews().size(), 2);
    logged.delete_review(review1);
    ASSERT_EQ(logged.getReviews().size(), 1);
};
