#include "person.h"

#include <algorithm>

#include "film.h"
const std::string& Person::getName() const { return name; }

const unsigned int Person::getId() const { return id; }

Date Person::getBirthDate() const { return birthDate; }

bool Person::operator==(const Person& other) { return id == other.id; }

const std::vector<Actor::Role>& Actor::getRoles() const { return roles; }

bool Actor::Role::operator<(const Role& other) const {
    return film->getTitle() < other.film->getTitle();
}

void Actor::addRole(const std::string& character, const Film& film) {
    Role newRole(character, film);
    auto it = std::lower_bound(roles.begin(), roles.end(), newRole);

    if (it != roles.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a role for this film");
    }
    roles.insert(it, newRole);
}

void Actor::displayRoles(std::ostream& os) const {
    os << this->name << "'s roles: \n";
    for (const auto& role : roles) {
        os << "As " << role.character << " in \"" << role.film->getTitle()
           << "\"\n";
    }
}

const std::vector<const Film*>& Director::getFilms() const { return films; }

void Director::addFilm(const Film& film) {
    auto it = std::lower_bound(films.begin(), films.end(), &film,
                               [](const Film* lhs, const Film* rhs) {
                                   return lhs->getTitle() < rhs->getTitle();
                               });
    if (it != films.end() && (*it)->getID() == film.getID()) {
        throw std::invalid_argument("Film is already on the list");
    }
    films.insert(it, &film);
}

void Director::displayFilms(std::ostream& os) const {
    os << "Films directed by " << this->name << ":\n";
    for (const auto& film : films) {
        os << "\"" << film->getTitle() << "\"" << " (" << film->getYear()
           << ")\n";
    }
}

const std::vector<Producer::ProducerJob>& Producer::getJobs() const {
    return jobs;
}

bool Producer::ProducerJob::operator<(const ProducerJob& other) const {
    return film->getTitle() < other.film->getTitle();
}

void Producer::addJob(ProducerType ptype, const Film& film) {
    ProducerJob newJob(ptype, film);
    auto it = std::lower_bound(jobs.begin(), jobs.end(), newJob);

    if (it != jobs.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a job for this film");
    }
    jobs.insert(it, newJob);
}

void Producer::displayJobs(std::ostream& os) const {
    os << "Films produced by " << this->name << ":\n";
    for (const auto& job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " (" << job.film->getYear()
           << ") as ";
        switch (job.ptype) {
            case ProducerType::ExecutiveProducer:
                os << "Executive Producer\n";
                break;
            default:
                os << "Producer\n";
                break;
        }
    }
}

const std::vector<Writer::WriterJob>& Writer::getJobs() const { return jobs; }

bool Writer::WriterJob::operator<(const WriterJob& other) const {
    return film->getTitle() < other.film->getTitle();
}

void Writer::addJob(WriterType wtype, const Film& film) {
    WriterJob newJob(wtype, film);
    auto it = std::lower_bound(jobs.begin(), jobs.end(), newJob);

    if (it != jobs.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a job for this film");
    }
    jobs.insert(it, newJob);
}

void Writer::displayJobs(std::ostream& os) const {
    os << "Films written by " << this->name << ":\n";
    for (const auto& job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " (" << job.film->getYear()
           << ") - ";
        switch (job.wtype) {
            case WriterType::Screenplay:
                os << "Screenplay\n";
                break;

            case WriterType::Story:
                os << "Story\n";
                break;
            default:
                os << "Writer\n";
                break;
        }
    }
}