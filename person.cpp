#include "person.h"

#include "film.h"
const std::string& Person::getName() const { return name; }

Date Person::getBirthDate() const { return birthDate; }

const std::vector<Actor::Role>& Actor::getRoles() const { return roles; }

void Actor::addRole(const std::string& character, const Film& film) {
    roles.emplace_back(character, film);  // TODO add sorted by id
}

void Actor::displayRoles(std::ostream& os) const {
    os << this->name << "'s roles: \n";
    for (const auto& role : roles) {
        os << "As " << role.character << " in \"" << role.film.getTitle()
           << "\"\n";
    }
}

const std::vector<const Film*>& Director::getFilms() const { return films; }

void Director::addFilm(const Film& film) { films.push_back(&film); }

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

void Producer::addJob(ProducerType ptype, const Film& film) {
    jobs.emplace_back(ptype, film);
}

void Producer::displayJobs(std::ostream& os) const {
    os << "Films produced by " << this->name << ":\n";
    for (const auto& job : jobs) {
        os << "\"" << job.film.getTitle() << "\"" << " (" << job.film.getYear()
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

void Writer::addJob(WriterType wtype, const Film& film) {
    jobs.emplace_back(wtype, film);
}

void Writer::displayJobs(std::ostream& os) const {
    os << "Films written by " << this->name << ":\n";
    for (const auto& job : jobs) {
        os << "\"" << job.film.getTitle() << "\"" << " (" << job.film.getYear()
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