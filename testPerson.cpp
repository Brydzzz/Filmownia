#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

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

TEST(person_test, equal_operator) {
    Person p(1, "Tomasz Smoleń", 21, 5, 2004);
    Actor a(2, "Emma Stone", 6, 11, 1988);
    ASSERT_EQ(a == p, false);
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

TEST(director_test, constructor) {
    Director d(3, "Yorgos Lanthimos", 23, 9, 1973);
    ASSERT_EQ(d.getName(), "Yorgos Lanthimos");
    ASSERT_EQ(d.getBirthDate().getDay(), 23);
    ASSERT_EQ(d.getBirthDate().getMonth(), 9);
    ASSERT_EQ(d.getBirthDate().getYear(), 1973);
    ASSERT_EQ(d.getFilms().empty(), true);
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

TEST(director_test, add_film_same_title) {
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

TEST(producer_test, add_job_film_same_title) {
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