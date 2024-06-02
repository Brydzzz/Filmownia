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

std::vector<Actor::Role>::iterator Actor::findRole(const Film& film) {
    return findRole(Role("", film));
}

std::vector<Actor::Role>::iterator Actor::findRole(const Role& role) {
    auto it = std::lower_bound(roles.begin(), roles.end(), role);
    return it;
}

void Actor::addRole(const std::string& character, const Film& film) {
    Role newRole(character, film);
    auto it = findRole(newRole);
    if (it != roles.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a role for this film");
    } else {
        roles.insert(it, newRole);
    }
}

void Actor::deleteRole(const Film& film) {
    auto it = findRole(film);
    if (it != roles.end() && it->film->getID() == film.getID()) {
        roles.erase(it);
    }
}

void Actor::displayRoles(std::ostream& os) const {
    os << this->name << "'s roles: \n";
    for (const auto& role : roles) {
        os << "As " << role.character << " in \"" << role.film->getTitle()
           << "\"\n";
    }
}

const std::vector<const Film*>& Director::getFilms() const { return films; }

std::vector<const Film*>::iterator Director::findFilm(const Film& film) {
    auto it = std::lower_bound(films.begin(), films.end(), &film,
                               [](const Film* lhs, const Film* rhs) {
                                   return lhs->getTitle() < rhs->getTitle();
                               });
    return it;
}

void Director::addFilm(const Film& film) {
    auto it = findFilm(film);
    if (it != films.end() && (*it)->getID() == film.getID()) {
        throw std::invalid_argument("Film is already on the list");
    }
    films.insert(it, &film);
}

void Director::deleteFilm(const Film& film) {
    auto it = findFilm(film);
    if (it != films.end() && (*it)->getID() == film.getID()) {
        films.erase(it);
    }
}

void Director::displayFilms(std::ostream& os) const {
    os << "Films directed by " << this->name << ":\n";
    for (const auto& film : films) {
        os << "\"" << film->getTitle() << "\"" << " (" << film->getYear()
           << ")\n";
    }
}

std::vector<Producer::ProducerJob>::iterator Producer::findJob(
    const Film& film) {
    return findJob(ProducerJob(ProducerType::Producer, film));
}

std::vector<Producer::ProducerJob>::iterator Producer::findJob(
    const ProducerJob& job) {
    auto it = std::lower_bound(jobs.begin(), jobs.end(), job);
    return it;
}

const std::vector<Producer::ProducerJob>& Producer::getJobs() const {
    return jobs;
}

bool Producer::ProducerJob::operator<(const ProducerJob& other) const {
    return film->getTitle() < other.film->getTitle();
}

void Producer::addJob(ProducerType ptype, const Film& film) {
    ProducerJob newJob(ptype, film);
    auto it = findJob(newJob);

    if (it != jobs.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a job for this film");
    }
    jobs.insert(it, newJob);
}

void Producer::deleteJob(const Film& film) {
    auto it = findJob(film);
    if (it != jobs.end() && it->film->getID() == film.getID()) {
        jobs.erase(it);
    }
}

void Producer::displayJobs(std::ostream& os) const {
    os << "Films produced by " << this->name << ":\n";
    for (const auto& job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " ("
           << job.film->getYear() << ") as ";
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

std::vector<Writer::WriterJob>::iterator Writer::findJob(const Film& film) {
    return findJob(WriterJob(WriterType::Screenplay, film));
}

std::vector<Writer::WriterJob>::iterator Writer::findJob(const WriterJob& job) {
    auto it = std::lower_bound(jobs.begin(), jobs.end(), job);
    return it;
}

const std::vector<Writer::WriterJob>& Writer::getJobs() const { return jobs; }

bool Writer::WriterJob::operator<(const WriterJob& other) const {
    return film->getTitle() < other.film->getTitle();
}

void Writer::addJob(WriterType wtype, const Film& film) {
    WriterJob newJob(wtype, film);
    auto it = findJob(newJob);

    if (it != jobs.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a job for this film");
    }
    jobs.insert(it, newJob);
}

void Writer::deleteJob(const Film& film) {
    auto it = findJob(film);
    if (it != jobs.end() && it->film->getID() == film.getID()) {
        jobs.erase(it);
    }
}

void Writer::displayJobs(std::ostream& os) const {
    os << "Films written by " << this->name << ":\n";
    for (const auto& job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " ("
           << job.film->getYear() << ") - ";
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