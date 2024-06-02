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
    Person(unsigned int id, const std::string& name, unsigned int day,
           unsigned int month, unsigned int year)
        : id(id), name(name), birthDate(day, month, year) {}

    const std::string& getName() const;
    const unsigned int getId() const;
    Date getBirthDate() const;
    bool operator==(const Person& other);
    // TODO method of reading from csv and saving to csv format
};

class Actor : public Person {
   private:
    struct Role {
        std::string character;
        const Film* film;

        Role(const std::string& character, const Film& film)
            : character(character), film(&film) {}

        bool operator<(const Role& other) const;
    };
    std::vector<Role> roles = {};

   public:
    using Person::Person;
    const std::vector<Role>& getRoles() const;

    void addRole(const std::string& character, const Film& film);
    void deleteRole(const Film& film);
    void displayRoles(std::ostream& os) const;
};

class Director : public Person {
   private:
    std::vector<const Film*> films = {};

   public:
    using Person::Person;

    const std::vector<const Film*>& getFilms() const;
    void addFilm(const Film& film);
    void displayFilms(std::ostream& os) const;
};

enum class ProducerType { Producer, ExecutiveProducer };

class Producer : public Person {
   private:
    struct ProducerJob {
        ProducerType ptype;
        const Film* film;

        ProducerJob(ProducerType ptype, const Film& film)
            : ptype(ptype), film(&film) {}

        bool operator<(const ProducerJob& other) const;
    };
    std::vector<ProducerJob> jobs = {};

   public:
    using Person::Person;

    const std::vector<ProducerJob>& getJobs() const;
    void addJob(ProducerType ptype, const Film& film);
    void deleteJob(const Film& film);
    void displayJobs(std::ostream& os) const;
};

enum class WriterType { Screenplay, Story, Writer };

class Writer : public Person {
   private:
    struct WriterJob {
        WriterType wtype;
        const Film* film;

        WriterJob(WriterType wtype, const Film& film)
            : wtype(wtype), film(&film) {}

        bool operator<(const WriterJob& other) const;
    };
    std::vector<WriterJob> jobs = {};

   public:
    using Person::Person;

    const std::vector<WriterJob>& getJobs() const;
    void addJob(WriterType wtype, const Film& film);
    void deleteJob(const Film& film);
    void displayJobs(std::ostream& os) const;
};
