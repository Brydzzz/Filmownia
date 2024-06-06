#pragma once
#include <iostream>
#include <string>

#include "date.h"
#include "film.h"

class Person {
   protected:
    std::string name;
    Date birthDate;
    unsigned int id;

   public:
    Person(unsigned int id, const std::string &name, unsigned int day,
           unsigned int month, unsigned int year)
        : id(id), name(name), birthDate(day, month, year) {}
    Person(unsigned int id, const std::string &name, Date date)
        : id(id), name(name), birthDate(date) {}

    const std::string &getName() const;
    const unsigned int getId() const;
    Date getBirthDate() const;
    bool operator==(const Person &other);
    // TODO method of reading from csv and saving to csv format
};

class Actor : public Person {
   private:
    struct Role {
        std::string character;
        const Film *film;

        Role(const std::string &character, const Film &film)
            : character(character), film(&film) {}

        Role(const std::string &character, const Film *film)
            : character(character), film(film) {}

        bool operator<(const Role &other) const;
    };
    std::vector<Role> roles = {};
    std::vector<Role>::iterator findRole(const Film &film);
    std::vector<Role>::iterator findRole(const Role &role);
    std::vector<Role> parseRoles(const std::string &content);

   public:
    using Person::Person;

    // ctor for data from csv
    Actor(unsigned int id, const std::string &name, Date date,
          std::string roles)
        : Person(id, name, date), roles(parseRoles(roles)) {}

    const std::vector<Role> &getRoles() const;
    void addRole(const std::string &character, const Film &film);
    void deleteRole(const Film &film);
    void displayActorInfo(std::ostream &os) const;
    void displayRoles(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Actor &actor);
};

class Director : public Person {
   private:
    std::vector<const Film *> films = {};
    std::vector<const Film *>::iterator findFilm(const Film &film);
    std::vector<const Film *> parseFilms(std::string content);  // TODO
                                                                // parseFilms

   public:
    using Person::Person;

    // ctor for data from csv
    Director(unsigned int id, const std::string &name, Date date,
             std::string films)
        : Person(id, name, date), films(parseFilms(films)) {}

    const std::vector<const Film *> &getFilms() const;
    void addFilm(const Film &film);
    void deleteFilm(const Film &film);
    void displayDirectorInfo(std::ostream &os) const;
    void displayFilms(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Director &director);
};

enum class ProducerType { Producer, ExecutiveProducer };
std::string ptypeToString(ProducerType ptype);

class Producer : public Person {
   private:
    struct ProducerJob {
        ProducerType ptype;
        const Film *film;

        ProducerJob(ProducerType ptype, const Film &film)
            : ptype(ptype), film(&film) {}

        bool operator<(const ProducerJob &other) const;
    };
    std::vector<ProducerJob> jobs = {};
    std::vector<ProducerJob>::iterator findJob(const Film &film);
    std::vector<ProducerJob>::iterator findJob(const ProducerJob &job);
    std::vector<ProducerJob> parseFilms(std::string content);

   public:
    using Person::Person;
    Producer(unsigned int id, const std::string &name, Date date,
             std::string jobs)
        : Person(id, name, date), jobs(parseFilms(jobs)) {}
    const std::vector<ProducerJob> &getJobs() const;
    void addJob(ProducerType ptype, const Film &film);
    void deleteJob(const Film &film);
    void displayJobs(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Producer &producer);
};

enum class WriterType { Screenplay, Story, Writer };
std::string wtypeToString(WriterType wtype);

class Writer : public Person {
   private:
    struct WriterJob {
        WriterType wtype;
        const Film *film;

        WriterJob(WriterType wtype, const Film &film)
            : wtype(wtype), film(&film) {}

        bool operator<(const WriterJob &other) const;
    };
    std::vector<WriterJob> jobs = {};
    std::vector<WriterJob>::iterator findJob(const Film &film);
    std::vector<WriterJob>::iterator findJob(const WriterJob &job);
    std::vector<WriterJob> parseFilms(std::string content);

   public:
    using Person::Person;
    Writer(unsigned int id, const std::string &name, Date date,
           std::string jobs)
        : Person(id, name, date), jobs(parseFilms(jobs)) {}
    const std::vector<WriterJob> &getJobs() const;
    void addJob(WriterType wtype, const Film &film);
    void deleteJob(const Film &film);
    void displayJobs(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Writer &writer);
};
