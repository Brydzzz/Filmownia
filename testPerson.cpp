#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

#include "date.h"
#include "film.h"
#include "person.h"
TEST(person_test, constructor) {
    Person p(1, "Tomasz Smoleń", 21, 5, 2004);
    ASSERT_EQ(p.getName(), "Tomasz Smoleń");
    ASSERT_EQ(p.getId(), 1);
    ASSERT_EQ(p.getBirthDate().getDay(), 21);
    ASSERT_EQ(p.getBirthDate().getMonth(), 5);
    ASSERT_EQ(p.getBirthDate().getYear(), 2004);
}

TEST(person_test, constructor_date_object) {
    Date d(21, 5, 2004);
    Person p(1, "Tomasz Smoleń", d);
    ASSERT_EQ(p.getName(), "Tomasz Smoleń");
    ASSERT_EQ(p.getId(), 1);
    ASSERT_EQ(p.getBirthDate().getDay(), 21);
    ASSERT_EQ(p.getBirthDate().getMonth(), 5);
    ASSERT_EQ(p.getBirthDate().getYear(), 2004);
}

TEST(person_test, constructor_wrong_date) {
    ASSERT_THROW(Person(1, "Tomasz Smoleń", 32, 5, 2004), std::exception);
}

TEST(actor_test, constructor) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    ASSERT_EQ(a.getName(), "Emma Stone");
    ASSERT_EQ(a.getId(), 2);
    ASSERT_EQ(a.getBirthDate().getDay(), 6);
    ASSERT_EQ(a.getBirthDate().getMonth(), 11);
    ASSERT_EQ(a.getBirthDate().getYear(), 1988);
    ASSERT_EQ(a.getRoles().empty(), true);
}

TEST(actor_test, constructor_date_object) {
    Date d(6, 11, 1988);
    Actor a(2, "Emma Stone", d);
    ASSERT_EQ(a.getName(), "Emma Stone");
    ASSERT_EQ(a.getId(), 2);
    ASSERT_EQ(a.getBirthDate().getDay(), 6);
    ASSERT_EQ(a.getBirthDate().getMonth(), 11);
    ASSERT_EQ(a.getBirthDate().getYear(), 1988);
    ASSERT_EQ(a.getRoles().empty(), true);
}

TEST(person_test, equal_operator) {
    Person p(1, "Tomasz Smoleń", 21, 5, 2004);
    Actor a(2, "Emma Stone", 6, 11, 1988);
    ASSERT_EQ(a == p, false);
}

TEST(actor_test, constructor_csv) {
    Date d(6, 11, 1988);
    Actor a(2, "Emma Stone", d,
            "[[37735, Olive Penderghast], [1930, Gwen Stacy], [50646, Hannah "
            "Weaver]]");
    ASSERT_EQ(a.getName(), "Emma Stone");
    ASSERT_EQ(a.getId(), 2);
    ASSERT_EQ(a.getBirthDate().getDay(), 6);
    ASSERT_EQ(a.getBirthDate().getMonth(), 11);
    ASSERT_EQ(a.getBirthDate().getYear(), 1988);
    ASSERT_EQ(a.getRoles().size(), 3);
    std::stringstream ss;
    a.displayRoles(ss);
    ASSERT_EQ(ss.str(),
              "Emma Stone's roles: \nAs Hannah Weaver in \"Crazy, Stupid, "
              "Love.\"\nAs "
              "Olive Penderghast in \"Easy A\"\nAs Gwen Stacy in \"The Amazing "
              "Spider-Man\"\n");
}

TEST(actor_test, constructor_csv_2) {
    Date d(6, 11, 1988);
    Actor a(2, "Emma Stone", d,
            "[['37735', 'Olive Penderghast'], ['1930', 'Gwen Stacy'], "
            "['50646', 'Hannah "
            "Weaver']]");
    ASSERT_EQ(a.getName(), "Emma Stone");
    ASSERT_EQ(a.getId(), 2);
    ASSERT_EQ(a.getBirthDate().getDay(), 6);
    ASSERT_EQ(a.getBirthDate().getMonth(), 11);
    ASSERT_EQ(a.getBirthDate().getYear(), 1988);
    ASSERT_EQ(a.getRoles().size(), 3);
    std::stringstream ss;
    a.displayRoles(ss);
    ASSERT_EQ(ss.str(),
              "Emma Stone's roles: \nAs Hannah Weaver in \"Crazy, Stupid, "
              "Love.\"\nAs "
              "Olive Penderghast in \"Easy A\"\nAs Gwen Stacy in \"The Amazing "
              "Spider-Man\"\n");
}

TEST(actor_test, constructor_csv_empty_roles) {
    Date d(6, 11, 1988);
    Actor a(2, "Emma Stone", d, "[]");
    ASSERT_EQ(a.getName(), "Emma Stone");
    ASSERT_EQ(a.getId(), 2);
    ASSERT_EQ(a.getBirthDate().getDay(), 6);
    ASSERT_EQ(a.getBirthDate().getMonth(), 11);
    ASSERT_EQ(a.getBirthDate().getYear(), 1988);
    ASSERT_EQ(a.getRoles().empty(), true);
}

TEST(actor_test, add_role) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    ASSERT_EQ(a.getRoles().empty(), true);
    Film f1(1, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    ASSERT_EQ(a.getRoles().size(), 1);
    Film f2(
        2, "Poor Things", 2024, {film_genre::Comedy}, {},
        "Brought back to life by an unorthodox scientist, a young woman runs "
        "off with a lawyer on a whirlwind adventure across the continents.",
        {}, 144, {}, {}, "");
    a.addRole("Bella Baxter", f2);
    ASSERT_EQ(a.getRoles().size(), 2);
}

TEST(actor_test, add_role_duplicate) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    Film f1(1, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    Film f2(
        2, "Poor Things", 2024, {film_genre::Comedy}, {},
        "Brought back to life by an unorthodox scientist, a young woman runs "
        "off with a lawyer on a whirlwind adventure across the continents.",
        {}, 144, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    a.addRole("Bella Baxter", f2);
    ASSERT_THROW(a.addRole("Mia Dola", f1), std::exception);
}

TEST(actor_test, add_role_check_if_alphabetically) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    Film f1(1, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    Film f2(
        2, "Poor Things", 2024, {film_genre::Comedy}, {},
        "Brought back to life by an unorthodox scientist, a young woman runs "
        "off with a lawyer on a whirlwind adventure across the continents.",
        {}, 144, {}, {}, "");
    Film f3(78, "Cruella", 2021, {film_genre::Comedy}, {},
            "In 1970s London amidst the punk rock revolution, a young grifter "
            "named Estella is determined to make a name for herself with her "
            "designs. She befriends a pair of young thieves who appreciate her "
            "appetite for mischief, and together they are able to build a life "
            "for themselves on the London streets.",
            {}, 144, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    a.addRole("Bella Baxter", f2);
    a.addRole("Estella / Cruella", f3);
    std::stringstream ss;
    a.displayRoles(ss);
    ASSERT_EQ(ss.str(),
              "Emma Stone's roles: \nAs Estella / Cruella in \"Cruella\"\nAs "
              "Mia Dolan in \"La La Land\"\nAs Bella "
              "Baxter in \"Poor Things\"\n");
}

TEST(actor_test, delete_role) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    Film f1(1, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    Film f2(
        2, "Poor Things", 2024, {film_genre::Comedy}, {},
        "Brought back to life by an unorthodox scientist, a young woman runs "
        "off with a lawyer on a whirlwind adventure across the continents.",
        {}, 144, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    a.addRole("Bella Baxter", f2);
    ASSERT_EQ(a.getRoles().size(), 2);
    a.deleteRole(f1);
    ASSERT_EQ(a.getRoles().size(), 1);
}

TEST(actor_test, delete_role_not_in_roles) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    Film f1(1, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    Film f2(
        2, "Poor Things", 2024, {film_genre::Comedy}, {},
        "Brought back to life by an unorthodox scientist, a young woman runs "
        "off with a lawyer on a whirlwind adventure across the continents.",
        {}, 144, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    ASSERT_EQ(a.getRoles().size(), 1);
    a.deleteRole(f2);
    ASSERT_EQ(a.getRoles().size(), 1);
}

TEST(actor_test, display_roles) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    ASSERT_EQ(a.getRoles().empty(), true);
    Film f1(1, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    ASSERT_EQ(a.getRoles().size(), 1);
    Film f2(
        2, "Poor Things", 2024, {film_genre::Comedy}, {},
        "Brought back to life by an unorthodox scientist, a young woman runs "
        "off with a lawyer on a whirlwind adventure across the continents.",
        {}, 144, {}, {}, "");
    a.addRole("Bella Baxter", f2);
    ASSERT_EQ(a.getRoles().size(), 2);
    std::stringstream ss;
    a.displayRoles(ss);
    ASSERT_EQ(ss.str(),
              "Emma Stone's roles: \nAs Mia Dolan in \"La La Land\"\nAs Bella "
              "Baxter in \"Poor Things\"\n");
}

TEST(actor_test, display_info) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    Film f1(1, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    Film f2(
        2, "Poor Things", 2024, {film_genre::Comedy}, {},
        "Brought back to life by an unorthodox scientist, a young woman runs "
        "off with a lawyer on a whirlwind adventure across the continents.",
        {}, 144, {}, {}, "");
    a.addRole("Bella Baxter", f2);
    std::stringstream ss;
    a.displayActorInfo(ss);
    ASSERT_EQ(ss.str(),
              "Emma Stone\nBirthdate: 1988-11-06\nSelected roles: \nAs Mia "
              "Dolan in \"La La Land\"\nAs Bella Baxter in \"Poor Things\"\n");
}

TEST(actor_test, display_info_no_roles) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    std::stringstream ss;
    a.displayActorInfo(ss);
    ASSERT_EQ(ss.str(), "Emma Stone\nBirthdate: 1988-11-06\n");
}

TEST(actor_test, operator_out) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    Film f1(123, "La La Land", 2017, {film_genre::Drama}, {}, "Masterpiece", {},
            128, {}, {}, "");
    Film f2(36, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");
    Film f3(4789, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    a.addRole("Mia Dolan", f1);
    a.addRole("Abigail", f2);
    a.addRole("Bella Baxter", f3);
    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(),
              "2;Emma Stone;1988-11-06;[[123, Mia Dolan], [4789, Bella "
              "Baxter], [36, Abigail]]");
}

TEST(actor_test, operator_out_no_roles) {
    Actor a(2, "Emma Stone", 6, 11, 1988);
    std::stringstream ss;
    ss << a;
    ASSERT_EQ(ss.str(), "2;Emma Stone;1988-11-06;[]");
}

TEST(director_test, constructor) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    ASSERT_EQ(d.getName(), "Yorgos Lanthimos");
    ASSERT_EQ(d.getBirthDate().getDay(), 23);
    ASSERT_EQ(d.getBirthDate().getMonth(), 9);
    ASSERT_EQ(d.getBirthDate().getYear(), 1973);
    ASSERT_EQ(d.getFilms().empty(), true);
}

TEST(director_test, constructor_csv) {
    Date date(30, 7, 1970);
    Director d(3, "Christopher Nolan", date,
               "[49026, 155, 157336, 27205, 272, 320, 1124, 77]");
    ASSERT_EQ(d.getName(), "Christopher Nolan");
    ASSERT_EQ(d.getBirthDate().getDay(), 30);
    ASSERT_EQ(d.getBirthDate().getMonth(), 7);
    ASSERT_EQ(d.getBirthDate().getYear(), 1970);
    ASSERT_EQ(d.getFilms().size(), 8);
}

TEST(director_test, constructor_csv_2) {
    Date date(30, 7, 1970);
    Director d(
        3, "Christopher Nolan", date,
        "['49026', '155', '157336', '27205', '272', '320', '1124', '77']");
    ASSERT_EQ(d.getName(), "Christopher Nolan");
    ASSERT_EQ(d.getBirthDate().getDay(), 30);
    ASSERT_EQ(d.getBirthDate().getMonth(), 7);
    ASSERT_EQ(d.getBirthDate().getYear(), 1970);
    ASSERT_EQ(d.getFilms().size(), 8);
}

TEST(director_test, constructor_csv_invalid_film_str) {
    Date date(30, 7, 1970);
    ASSERT_THROW(
        Director d(
            3, "Christopher Nolan", date,
            "'49026', '155', '157336', '27205', '272', '320', '1124', '77']"),
        std::exception);
}

TEST(director_test, constructor_csv_empty_films) {
    Date date(30, 7, 1970);
    Director d(3, "Christopher Nolan", date, "[]");
    ASSERT_EQ(d.getName(), "Christopher Nolan");
    ASSERT_EQ(d.getBirthDate().getDay(), 30);
    ASSERT_EQ(d.getBirthDate().getMonth(), 7);
    ASSERT_EQ(d.getBirthDate().getYear(), 1970);
    ASSERT_EQ(d.getFilms().size(), 0);
}

TEST(director_test, add_film) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    ASSERT_EQ(d.getFilms().empty(), true);
    Film f1(3, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");
    d.addFilm(f1);
    ASSERT_EQ(d.getFilms().size(), 1);
    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f2);
    ASSERT_EQ(d.getFilms().size(), 2);
}

TEST(director_test, add_film_duplicate) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    Film f1(3, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");
    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f1);
    d.addFilm(f2);
    ASSERT_THROW(d.addFilm(f1), std::exception);
}

TEST(director_test, add_film_films_with_the_same_title) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    Film f1(17, "Poor Things", 2001, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f1);
    d.addFilm(f2);
    ASSERT_EQ(d.getFilms().size(), 2);
}

TEST(director_test, delete_film) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    Film f1(3, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");
    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f1);
    d.addFilm(f2);
    ASSERT_EQ(d.getFilms().size(), 2);
    d.deleteFilm(f2);
    ASSERT_EQ(d.getFilms().size(), 1);
    ASSERT_EQ(d.getFilms()[0], &f1);
}

TEST(director_test, delete_film_film_not_in_films) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    Film f1(3, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");
    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f1);
    ASSERT_EQ(d.getFilms().size(), 1);
    d.deleteFilm(f2);
    ASSERT_EQ(d.getFilms().size(), 1);
    ASSERT_EQ(d.getFilms()[0], &f1);
}

TEST(director_test, display_films) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    ASSERT_EQ(d.getFilms().empty(), true);
    Film f1(3, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");

    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f1);
    d.addFilm(f2);
    std::stringstream ss;
    d.displayFilms(ss);
    ASSERT_EQ(ss.str(),
              "Films directed by Yorgos Lanthimos:\n\"Poor "
              "Things\" (2024)\n\"The Favourite\" (2018)\n");
}

TEST(director_test, display_info) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    Film f1(3, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");

    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f1);
    d.addFilm(f2);
    std::stringstream ss;
    d.displayDirectorInfo(ss);
    ASSERT_EQ(ss.str(),
              "Yorgos Lanthimos\nBirthdate: 1973-09-23\n"
              "Selected films: \n\"Poor "
              "Things\" (2024)\n\"The Favourite\" (2018)\n");
}

TEST(director_test, display_info_no_films) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    std::stringstream ss;
    d.displayDirectorInfo(ss);
    ASSERT_EQ(ss.str(), "Yorgos Lanthimos\nBirthdate: 1973-09-23\n");
}

TEST(director_test, operator_out) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    Film f1(3, "The Favourite", 2018, {film_genre::Drama}, {},
            "England, early 18th century. The close relationship between Queen "
            "Anne and Sarah Churchill is threatened by the arrival of Sarah's "
            "cousin, Abigail Hill, resulting in a bitter rivalry between the "
            "two cousins to be the Queen's favourite.",
            {}, 120, {}, {}, "");

    Film f2(4, "Poor Things", 2024, {film_genre::Comedy}, {},
            "Brought back to life by an unorthodox scientist, a young woman "
            "runs "
            "off with a lawyer on a whirlwind adventure across the continents.",
            {}, 144, {}, {}, "");
    d.addFilm(f1);
    d.addFilm(f2);
    std::stringstream ss;
    ss << d;
    ASSERT_EQ(ss.str(), "3;Yorgos Lanthimos;1973-09-23;[4, 3]");
}

TEST(director_test, operator_out_n_films) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    std::stringstream ss;
    ss << d;
    ASSERT_EQ(ss.str(), "3;Yorgos Lanthimos;1973-09-23;[]");
}

TEST(producer_test, constructor) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    ASSERT_EQ(p.getName(), "Kevin Feige");
    ASSERT_EQ(p.getBirthDate().getDay(), 2);
    ASSERT_EQ(p.getBirthDate().getMonth(), 6);
    ASSERT_EQ(p.getBirthDate().getYear(), 1973);
    ASSERT_EQ(p.getJobs().empty(), true);
}

TEST(producer_test, add_job) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    ASSERT_EQ(p.getJobs().empty(), true);
    Film f1(3, "The Avengers", 2012, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    Film f2(
        4, "Iron Man", 2008, {film_genre::Action}, {},
        "After being held captive in an Afghan cave, billionaire engineer Tony "
        "Stark creates a unique weaponized suit of armor to fight evil.",
        {}, 126, {}, {}, "");
    p.addJob(ProducerType::Producer, f1);
    ASSERT_EQ(p.getJobs().size(), 1);
    p.addJob(ProducerType::Producer, f2);
    ASSERT_EQ(p.getJobs().size(), 2);
}

TEST(producer_test, add_job_duplicate) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    Film f1(3, "The Avengers", 2012, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    Film f2(
        4, "Iron Man", 2008, {film_genre::Action}, {},
        "After being held captive in an Afghan cave, billionaire engineer Tony "
        "Stark creates a unique weaponized suit of armor to fight evil.",
        {}, 126, {}, {}, "");
    p.addJob(ProducerType::Producer, f1);
    p.addJob(ProducerType::Producer, f2);
    ASSERT_THROW(p.addJob(ProducerType::ExecutiveProducer, f1), std::exception);
}

TEST(producer_test, add_job_films_with_the_same_title) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    ASSERT_EQ(p.getJobs().empty(), true);
    Film f1(3, "The Avengers", 2012, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    Film f2(
        4, "Iron Man", 2008, {film_genre::Action}, {},
        "After being held captive in an Afghan cave, billionaire engineer Tony "
        "Stark creates a unique weaponized suit of armor to fight evil.",
        {}, 126, {}, {}, "");
    Film f3(8, "The Avengers", 2034, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    p.addJob(ProducerType::Producer, f1);
    ASSERT_EQ(p.getJobs().size(), 1);
    p.addJob(ProducerType::Producer, f2);
    ASSERT_EQ(p.getJobs().size(), 2);
    p.addJob(ProducerType::Producer, f3);
    ASSERT_EQ(p.getJobs().size(), 3);
}

TEST(producer_test, delete_job) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    ASSERT_EQ(p.getJobs().empty(), true);
    Film f1(3, "The Avengers", 2012, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    Film f2(
        4, "Iron Man", 2008, {film_genre::Action}, {},
        "After being held captive in an Afghan cave, billionaire engineer Tony "
        "Stark creates a unique weaponized suit of armor to fight evil.",
        {}, 126, {}, {}, "");
    p.addJob(ProducerType::Producer, f1);
    p.addJob(ProducerType::Producer, f2);
    ASSERT_EQ(p.getJobs().size(), 2);
    p.deleteJob(f2);
    ASSERT_EQ(p.getJobs().size(), 1);
}

TEST(producer_test, delete_job_job_not_in_jobs) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    ASSERT_EQ(p.getJobs().empty(), true);
    Film f1(3, "The Avengers", 2012, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    Film f2(
        4, "Iron Man", 2008, {film_genre::Action}, {},
        "After being held captive in an Afghan cave, billionaire engineer Tony "
        "Stark creates a unique weaponized suit of armor to fight evil.",
        {}, 126, {}, {}, "");
    p.addJob(ProducerType::Producer, f1);
    ASSERT_EQ(p.getJobs().size(), 1);
    p.deleteJob(f2);
    ASSERT_EQ(p.getJobs().size(), 1);
}

TEST(producer_test, display_jobs) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    ASSERT_EQ(p.getJobs().empty(), true);
    Film f1(3, "The Avengers", 2012, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    Film f2(
        4, "Iron Man", 2008, {film_genre::Action}, {},
        "After being held captive in an Afghan cave, billionaire engineer Tony "
        "Stark creates a unique weaponized suit of armor to fight evil.",
        {}, 126, {}, {}, "");
    p.addJob(ProducerType::Producer, f1);
    p.addJob(ProducerType::ExecutiveProducer, f2);
    std::stringstream ss;
    p.displayJobs(ss);
    ASSERT_EQ(ss.str(),
              "Films produced by Kevin Feige:\n\"Iron Man\" (2008) as "
              "Executive Producer\n\"The Avengers\" (2012) as Producer\n");
}

TEST(producer_test, operator_out) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    Film f1(3, "The Avengers", 2012, {film_genre::Action}, {},
            "When an unexpected enemy emerges and threatens global safety and "
            "security, Nick Fury, director of the international peacekeeping "
            "agency known as S.H.I.E.L.D., finds himself in need of a team to "
            "pull the world back from the brink of disaster. Spanning the "
            "globe, a daring recruitment effort begins!",
            {}, 143, {}, {}, "");
    Film f2(
        4, "Iron Man", 2008, {film_genre::Action}, {},
        "After being held captive in an Afghan cave, billionaire engineer Tony "
        "Stark creates a unique weaponized suit of armor to fight evil.",
        {}, 126, {}, {}, "");
    p.addJob(ProducerType::Producer, f1);
    p.addJob(ProducerType::ExecutiveProducer, f2);
    std::stringstream ss;
    ss << p;
    ASSERT_EQ(
        ss.str(),
        "4;Kevin Feige;1973-06-02;[[4, Executive Producer], [3, Producer]]");
}

TEST(producer_test, operator_out_no_jobs) {
    Producer p(4, "Kevin Feige", 2, 6, 1973);
    std::stringstream ss;
    ss << p;
    ASSERT_EQ(ss.str(), "4;Kevin Feige;1973-06-02;[]");
}

TEST(writer_test, constructor) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    ASSERT_EQ(w.getName(), "Jon Spaihts");
    ASSERT_EQ(w.getBirthDate().getDay(), 4);
    ASSERT_EQ(w.getBirthDate().getMonth(), 2);
    ASSERT_EQ(w.getBirthDate().getYear(), 1970);
    ASSERT_EQ(w.getJobs().empty(), true);
}

TEST(writer_test, add_job) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    ASSERT_EQ(w.getJobs().empty(), true);
    Film f1(5, "Dune", 2021, {film_genre::SciFi}, {},
            "Paul Atreides, a brilliant and gifted young man born into a great "
            "destiny beyond his understanding, must travel to the most "
            "dangerous planet in the universe to ensure the future of his "
            "family and his people.",
            {}, 155, {}, {}, "");
    Film f2(
        6, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    w.addJob(WriterType::Screenplay, f1);
    ASSERT_EQ(w.getJobs().size(), 1);
    w.addJob(WriterType::Writer, f2);
    ASSERT_EQ(w.getJobs().size(), 2);
}

TEST(writer_test, add_job_duplicate) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    Film f1(5, "Dune", 2021, {film_genre::SciFi}, {},
            "Paul Atreides, a brilliant and gifted young man born into a great "
            "destiny beyond his understanding, must travel to the most "
            "dangerous planet in the universe to ensure the future of his "
            "family and his people.",
            {}, 155, {}, {}, "");
    Film f2(
        6, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    w.addJob(WriterType::Screenplay, f1);
    w.addJob(WriterType::Writer, f2);
    ASSERT_EQ(w.getJobs().size(), 2);
    ASSERT_THROW(w.addJob(WriterType::Screenplay, f1), std::exception);
}
TEST(producer_test, constructor_csv) {
    Date d(1, 10, 2005);
    Producer p(3, "Brygida Silawko", d,
               "[[19995, Producer], [285, Executive Producer]");
    ASSERT_EQ(p.getName(), "Brygida Silawko");
    ASSERT_EQ(p.getId(), 3);
    ASSERT_EQ(p.getBirthDate().getDay(), 1);
    ASSERT_EQ(p.getBirthDate().getMonth(), 10);
    ASSERT_EQ(p.getBirthDate().getYear(), 2005);
    std::stringstream ss;
    p.displayJobs(ss);
    ASSERT_EQ(ss.str(),
              "Films produced by Brygida Silawko:\n\"Avatar\" (2009) as "
              "Producer\n\"Pirates of the Caribbean: At World's End\" (2007) "
              "as Executive Producer\n");
}

TEST(writer_test, add_job_films_with_the_same_title) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    ASSERT_EQ(w.getJobs().empty(), true);
    Film f1(5, "Dune", 2021, {film_genre::SciFi}, {},
            "Paul Atreides, a brilliant and gifted young man born into a great "
            "destiny beyond his understanding, must travel to the most "
            "dangerous planet in the universe to ensure the future of his "
            "family and his people.",
            {}, 155, {}, {}, "");
    Film f2(
        6, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    Film f3(
        22, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    w.addJob(WriterType::Screenplay, f1);
    w.addJob(WriterType::Writer, f2);
    w.addJob(WriterType::Writer, f3);
    ASSERT_EQ(w.getJobs().size(), 3);
}

TEST(writer_test, delete_job) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    ASSERT_EQ(w.getJobs().empty(), true);
    Film f1(5, "Dune", 2021, {film_genre::SciFi}, {},
            "Paul Atreides, a brilliant and gifted young man born into a great "
            "destiny beyond his understanding, must travel to the most "
            "dangerous planet in the universe to ensure the future of his "
            "family and his people.",
            {}, 155, {}, {}, "");
    Film f2(
        6, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    w.addJob(WriterType::Screenplay, f1);
    w.addJob(WriterType::Writer, f2);
    ASSERT_EQ(w.getJobs().size(), 2);
    w.deleteJob(f2);
    ASSERT_EQ(w.getJobs().size(), 1);
}

TEST(writer_test, delete_job_job_not_in_jobs) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    ASSERT_EQ(w.getJobs().empty(), true);
    Film f1(5, "Dune", 2021, {film_genre::SciFi}, {},
            "Paul Atreides, a brilliant and gifted young man born into a great "
            "destiny beyond his understanding, must travel to the most "
            "dangerous planet in the universe to ensure the future of his "
            "family and his people.",
            {}, 155, {}, {}, "");
    Film f2(
        6, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    w.addJob(WriterType::Screenplay, f1);
    ASSERT_EQ(w.getJobs().size(), 1);
    w.deleteJob(f2);
    ASSERT_EQ(w.getJobs().size(), 1);
}

TEST(writer_test, constructor_csv) {
    Date d(1, 10, 2005);
    Writer w(3, "Brygida Silawko", d, "[[50646, Writer], [2454, Screenplay]");
    ASSERT_EQ(w.getName(), "Brygida Silawko");
    ASSERT_EQ(w.getId(), 3);
    ASSERT_EQ(w.getBirthDate().getDay(), 1);
    ASSERT_EQ(w.getBirthDate().getMonth(), 10);
    ASSERT_EQ(w.getBirthDate().getYear(), 2005);
    std::stringstream ss;
    w.displayJobs(ss);
    ASSERT_EQ(ss.str(),
              "Films written by Brygida Silawko:\n\"Crazy, Stupid, Love.\" "
              "(2011) - Writer\n\"The Chronicles of Narnia: Prince Caspian\" "
              "(2008) - Screenplay\n");
}

TEST(writer_test, display_jobs) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    ASSERT_EQ(w.getJobs().empty(), true);
    Film f1(5, "Dune", 2021, {film_genre::SciFi}, {},
            "Paul Atreides, a brilliant and gifted young man born into a great "
            "destiny beyond his understanding, must travel to the most "
            "dangerous planet in the universe to ensure the future of his "
            "family and his people.",
            {}, 155, {}, {}, "");
    Film f2(
        6, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    w.addJob(WriterType::Screenplay, f1);
    w.addJob(WriterType::Writer, f2);
    std::stringstream ss;
    w.displayJobs(ss);
    ASSERT_EQ(ss.str(),
              "Films written by Jon Spaihts:\n\"Dune\" (2021) - "
              "Screenplay\n\"Passengers\" (2016) - Writer\n");
}

TEST(writer_test, operator_out) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    Film f1(5, "Dune", 2021, {film_genre::SciFi}, {},
            "Paul Atreides, a brilliant and gifted young man born into a great "
            "destiny beyond his understanding, must travel to the most "
            "dangerous planet in the universe to ensure the future of his "
            "family and his people.",
            {}, 155, {}, {}, "");
    Film f2(
        6, "Passengers", 2016, {film_genre::Romance}, {},
        "A spacecraft traveling to a distant colony planet and transporting "
        "thousands of people has a malfunction in its sleep chambers. As a "
        "result, two passengers are awakened 90 years early.",
        {}, 116, {}, {}, "");
    w.addJob(WriterType::Screenplay, f1);
    w.addJob(WriterType::Writer, f2);
    std::stringstream ss;
    ss << w;
    ASSERT_EQ(ss.str(),
              "5;Jon Spaihts;1970-02-04;[[5, Screenplay], [6, Writer]]");
}

TEST(writer_test, operator_out_no_jobs) {
    Writer w(5, "Jon Spaihts", 4, 2, 1970);
    std::stringstream ss;
    ss << w;
    ASSERT_EQ(ss.str(), "5;Jon Spaihts;1970-02-04;[]");
}