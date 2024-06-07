#include <gtest/gtest.h>

#include <fstream>

#include "film.h"
TEST(filmTest, constructTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
}

TEST(filmTest, gettersTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    ASSERT_EQ(f.getTitle(), "All Quiet on The Western Front");
    ASSERT_EQ(f.getYear(), 2022);
    ASSERT_EQ(f.getDesc(), "Famous anti war movie based on a novel");
}

TEST(filmTest, addReviewTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    f.addReview(
        Review(&f, 1, std::string("Tomek"), 7, std::string("Very good movie")));
    auto revs = f.getReviews();
    auto film = revs[0].getFilm();
    ASSERT_EQ(film->getTitle(), "All Quiet on The Western Front");
};

TEST(filmTest, ratingTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    f.addReview(
        Review(&f, 1, std::string("Tomek"), 7, std::string("Very good movie")));
    f.addReview(
        Review(&f, 1, std::string("Tomek"), 9, std::string("Very good movie")));
    ASSERT_EQ(f.getRating(), 8);
}

TEST(filmTest, eqOperatorTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Film f2(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {},
            "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    ASSERT_TRUE(f == f2);
}

TEST(filmTest, eqOperatorFalseTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama}, {},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Film f2(2, "Enemy at the gates", 2022, {film_genre::Drama}, {},
            "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    ASSERT_FALSE(f == f2);
}

TEST(filmTest, writeTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    f.addReview(
        Review(&f, 1, std::string("Tomek"), 7, std::string("Very good movie")));
    f.addReview(
        Review(&f, 2, std::string("Tomek"), 9, std::string("Very good movie")));
    std::ostringstream os;
    f.write(os);
    ASSERT_EQ(os.str(),
              "\"All Quiet on The Western Front\"\nRelease year: 2022  "
              "Runtime: 120\nRating: 8\nFamous anti war movie based on a "
              "novel\nDirector: Ich\nProducers: \n\nWriters: \n\nCast: \n1. "
              "Him - The other character\n2. Me - The main character\n");
}

TEST(reviewTest, constructTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
}

TEST(reviewTest, getFilmTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_EQ(*r.getFilm(), f);
}

TEST(reviewTest, getScoreTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_EQ(r.getScore(), 7);
}

TEST(reviewTest, eqOperatorTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    Review r2(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_TRUE(r == r2);
}

TEST(reviewTest, eqOperatornotEqTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    Review r2(&f, 2, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_FALSE(r == r2);
}

TEST(reviewTest, getContentTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    ASSERT_EQ(r.getContent(), "Very good movie");
}

TEST(reviewTest, writeTest) {
    Film f(1, "All Quiet on The Western Front", 2022, {film_genre::Drama},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120, {}, {}, "Ich");
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    std::ostringstream os;
    r.write(os);
    ASSERT_EQ(os.str(), "Tomek: 7\nVery good movie\n");
}

TEST(filmTest, inOperatorTest) {
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    // ASSERT_EQ(f.getID(), 19995);
    // ASSERT_EQ(f.getTitle(), "Avatar");
    // ASSERT_EQ
}

TEST(filmTest, csvConstructTest) {
    Film f(1, "Avatar", 2009, "['Action', 'Adventure']",
           "[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge]]", "Scifi Movie",
           {}, 162, "[[James Cameron, Screenplay]]",
           "[[James Cameron, Producer], [Jon Landau, Producer]]",
           "James Cameron");
    ASSERT_EQ(f.getID(), 1);
    ASSERT_EQ(f.getTitle(), "Avatar");
    ASSERT_EQ(f.getGenre(), std::vector<film_genre>(
                                {film_genre::Action, film_genre::Adventure}));
    std::map<std::string, std::string> expected1 = {
        {"CCH Pounder", "Moat"}, {"Giovanni Ribisi", "Selfridge"}};
    ASSERT_EQ(f.getCast(), expected1);
    ASSERT_EQ(f.getDesc(), "Scifi Movie");
    ASSERT_EQ(f.getYear(), 2009);
    ASSERT_EQ(f.getTime(), 162);
    ASSERT_EQ(f.getDir(), "James Cameron");
    std::map<std::string, std::string> expected2 = {
        {"James Cameron", "Screenplay"}};
    ASSERT_EQ(f.getWriters(), expected2);
    std::map<std::string, std::string> expected3 = {
        {"James Cameron", "Producer"}, {"Jon Landau", "Producer"}};
    ASSERT_EQ(f.getProducers(), expected3);
}

TEST(filmTest, outOperatorTest) {
    Film f(1, "All Quiet on The Western Front", 2022,
           {film_genre::Drama, film_genre::Action},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120,
           {{"Ja", "Prodcuer"}}, {{"Ty", "Writer"}}, "Ich");
    std::ostringstream os;
    os << f;
    std::string res = os.str();
    ASSERT_EQ(
        os.str(),
        "1;All Quiet on The Western Front;['Drama', 'Action'];2022;120;Famous "
        "anti war movie based on a novel;[[Him, The other character], [Me, The "
        "main character]];Ich;[[Ja, Prodcuer]];[[Ty, Writer]]");
}

TEST(filmTest, ultimateStreamTest) {
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    std::ostringstream os;
    os << f;
    ASSERT_EQ(os.str(), s);
}

TEST(reviewTest, outOperatorTest) {
    Film f;
    std::string s =
        R"(19995;Avatar;['Action', 'Adventure', 'Fantasy', 'Science Fiction'];2009;162;In the 22nd century, a paraplegic Marine is dispatched to the moon Pandora on a unique mission, but becomes torn between following orders and protecting an alien civilization.;[[CCH Pounder, Moat], [Giovanni Ribisi, Selfridge], [Joel David Moore, Norm Spellman], [Laz Alonso, \"Tsu'Tey\"], [Michelle Rodriguez, Trudy Chacon], [Sam Worthington, Jake Sully], [Sigourney Weaver, Dr. Grace Augustine], [Stephen Lang, Col. Quaritch], [Wes Studi, Eytukan], [Zoe Saldana, Neytiri]];James Cameron;[[James Cameron, Screenplay]];[[James Cameron, Producer], [Jon Landau, Producer], [Laeta Kalogridis, Executive Producer]])";
    std::istringstream is(s);
    is >> f;
    Review r(&f, 1, std::string("Tomek"), 7, std::string("Very good movie"));
    std::ostringstream os;
    os << r;
    ASSERT_EQ(os.str(), "1;Tomek;19995;7;Very good movie");
}

TEST(filmTest, addRoleTest) {
    Film f(1, "All Quiet on The Western Front", 2022,
           {film_genre::Drama, film_genre::Action},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120,
           {{"Ja", "Prodcuer"}}, {{"Ty", "Writer"}}, "Ich");
    f.addRole("Er", "Soldat");
    std::map<std::string, std::string> expected = {
        {"Me", "The main character"},
        {"Him", "The other character"},
        {"Er", "Soldat"}};
    ASSERT_EQ(f.getCast(), expected);
}

TEST(filmTest, delRoleTest) {
    Film f(1, "All Quiet on The Western Front", 2022,
           {film_genre::Drama, film_genre::Action},
           {{"Me", "The main character"}, {"Him", "The other character"}},
           "Famous anti war movie based on a novel", {}, 120,
           {{"Ja", "Prodcuer"}}, {{"Ty", "Writer"}}, "Ich");
    f.deleteRole("Me");
    std::map<std::string, std::string> expected = {
        {"Him", "The other character"}};
    ASSERT_EQ(f.getCast(), expected);
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
