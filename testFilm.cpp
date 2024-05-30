#include <gtest/gtest.h>
#include <fstream>
#include "film.h"
TEST(filmTest, constructTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
}

TEST(filmTest, gettersTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    ASSERT_EQ(f.getTitle(), "All Quiet on The Western Front");
    ASSERT_EQ(f.getYear(), 2022);
    ASSERT_EQ(f.getDesc(), "Famous anti war movie based on a novel");
}

TEST(filmTest, addReviewTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    f.addReview(Review(&f, 1, std::string("Tomek"), 7, std::string("Very good movie")));
    auto revs = f.getReviews();
    auto film = revs[0].getFilm();
    ASSERT_EQ(film->getTitle(), "All Quiet on The Western Front");
};

TEST(filmTest, ratingTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    f.addReview(Review(&f, 1, std::string("Tomek"), 7, std::string("Very good movie")));
    f.addReview(Review(&f, 1, std::string("Tomek"), 9, std::string("Very good movie")));
    ASSERT_EQ(f.getRating(), 8);
}

TEST(filmTest, eqOperatorTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Film f2(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    ASSERT_TRUE(f == f2);
}

TEST(filmTest, eqOperatorFalseTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Film f2(2, "Enemy at the gates", 2022, {film_genre::Drama}, {}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    ASSERT_FALSE(f == f2);
}

TEST(filmTest, writeTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    f.addReview(Review(&f, 1, std::string("Tomek"), 7, std::string("Very good movie")));
    f.addReview(Review(&f, 2, std::string("Tomek"), 9, std::string("Very good movie")));
    std::ostringstream os;
    f.write(os);
    ASSERT_EQ(os.str(), "\"All Quiet on The Western Front\"\n2022  120\n8\nFamous anti war movie based on a novel\n1. Him - The other character\n2. Me - The main character\n");
}

TEST(reviewTest, constructTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
}

TEST(reviewTest, getFilmTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_EQ(*r.getFilm(), f);
}

TEST(reviewTest, getScoreTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_EQ(r.getScore(), 7);
}

TEST(reviewTest, eqOperatorTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    Review r2(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_TRUE(r == r2);
}

TEST(reviewTest, eqOperatornotEqTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    Review r2(&f, 2, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_FALSE(r == r2);
}

TEST(reviewTest, getContentTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_EQ(r.getContent(), "Very good movie");
}

TEST(reviewTest, outOperatorTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    std::ostringstream os;
    os << r;
    ASSERT_EQ(os.str(), "7\nVery good movie\n");
}

TEST(filmTest, inOperatorTest)
{
    Film f;
    std::string s = R"(19995;Avatar;"['Action', 'Adventure', 'Fantasy', 'Science Fiction']";2009;162;"In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.";"[['Sam Worthington', 'Jake Sully'], ['Zoe Saldana', 'Neytiri'], ['Sigourney Weaver', 'Dr. Grace Augustine'], ['Stephen Lang', 'Col. Quaritch'], ['Michelle Rodriguez', 'Trudy Chacon'], ['Giovanni Ribisi', 'Selfridge'], ['Joel David Moore', 'Norm Spellman'], ['CCH Pounder', 'Moat'], ['Wes Studi', 'Eytukan'], ['Laz Alonso', ""Tsu'Tey""]]";James Cameron;"[['James Cameron', 'Writer'], ['James Cameron', 'Screenplay']]";"[['James Cameron', 'Producer'], ['Jon Landau', 'Producer'], ['Laeta Kalogridis', 'Executive Producer']]")";
    std::istringstream is(s);
    is >> f;
}

TEST(filmTest, outOperatorTest)
{
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama, film_genre::Action}, {{"Me", "The main character"}, {"Him", "The other character"}}, "Famous anti war movie based on a novel", {}, 120, {{"Ja", "Prodcuer"}}, {{"Ty", "Writer"}}, "Ich");
    std::ostringstream os;
    os << f;
    std::string res = os.str();
}

TEST(filmTest, ultimateStreamTest)
{
    Film f;
    std::string s = R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;"[['Sam Worthington', 'Jake Sully'], ['Zoe Saldana', 'Neytiri'], ['Sigourney Weaver', 'Dr. Grace Augustine'], ['Stephen Lang', 'Col. Quaritch'], ['Michelle Rodriguez', 'Trudy Chacon'], ['Giovanni Ribisi', 'Selfridge'], ['Joel David Moore', 'Norm Spellman'], ['CCH Pounder', 'Moat'], ['Wes Studi', 'Eytukan'], ['Laz Alonso', ""Tsu'Tey""]]";James Cameron;[['James Cameron', 'Writer'], ['James Cameron', 'Screenplay']];[['James Cameron', 'Producer'], ['Jon Landau', 'Producer'], ['Laeta Kalogridis', 'Executive Producer']])";
    std::istringstream is(s);
    is >> f;
    std::ostringstream os;
    os << f;
    ASSERT_EQ(os.str(), s);
}

// TEST(filmTest, hugeLoadingTest)
// {
//     std::vector<Film> list;
//     std::ifstream input("movies.csv");
//     if (!input.is_open())
//     {
//         FAIL() << "Unable to open file movies.csv";
//     }
//     std::string row;
//     getline(input, row, '\n');
//     while (getline(input, row, '\n'))
//     {
//         Film f;
//         std::istringstream(row) >> f;
//         list.push_back(f);
//     }
// }
