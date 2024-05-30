#pragma once
#include <iostream>
#include <string>

#include "date.h"
#include "film.h"

class Person {
   protected:
    std::string name;
    Date birthDate;
    // TODO add id to person

   public:
    Person(const std::string& name, unsigned int day, unsigned int month,
           unsigned int year)
        : name(name), birthDate(day, month, year) {}

    const std::string& getName() const;
    Date getBirthDate() const;
    // method of reading from csv and saving to csv format
};

class Actor : public Person {
   private:
    struct Role {
        std::string character;
        const Film& film;

        Role(const std::string& character, const Film& film)
            : character(character), film(film) {}
    };
    std::vector<Role> roles = {}; //roles should be sorted by film id/name

   public:
    using Person::Person;
    const std::vector<Role>& getRoles() const;

    void addRole(const std::string& character,
                 const Film& film);  // TODO add mechanism for duplicates
    void displayRoles(std::ostream& os) const;
    void searchRole(unsigned int filmId);
};

class Director : public Person {
   private:
    std::vector<const Film*> films = {}; //should be sorted by id/name

   public:
    using Person::Person;

    const std::vector<const Film*>& getFilms() const;
    void addFilm(const Film& film);  // TODO add mechanism for duplicates
    void displayFilms(std::ostream& os) const;
};

enum class ProducerType { Producer, ExecutiveProducer };

class Producer : public Person {
   private:
    struct ProducerJob {
        ProducerType ptype;
        const Film& film;

        ProducerJob(ProducerType ptype, const Film& film)
            : ptype(ptype), film(film) {}
    };
    std::vector<ProducerJob> jobs = {}; // jobs should be sorted by film id/name

   public:
    using Person::Person;

    const std::vector<ProducerJob>& getJobs() const;
    void addJob(ProducerType ptype,
                const Film& film);  // TODO add mechanism for duplicates
    void displayJobs(std::ostream& os) const;
};

enum class WriterType { Screenplay, Story, Writer };

class Writer : public Person {
   private:
    struct WriterJob {
        WriterType wtype;
        const Film& film;

        WriterJob(WriterType wtype, const Film& film)
            : wtype(wtype), film(film) {}
    };
    std::vector<WriterJob> jobs = {}; // jobs should be sorted by film id/name

   public:
    using Person::Person;

    const std::vector<WriterJob>& getJobs() const;
    void addJob(WriterType wtype,
                const Film& film);  // TODO add mechanism for duplicates
    void displayJobs(std::ostream& os) const;
};
