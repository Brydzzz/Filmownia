#include "person.h"

#include <algorithm>

#include "film.h"
#include "global.h"

extern std::vector<Film> flist;

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

std::vector<Actor::Role> Actor::parseRoles(const std::string& content) {
    std::vector<Actor::Role> roles;
    std::istringstream iss(content);
    std::string role;

    while (std::getline(iss, role, ']')) {
        role.erase(0, role.find_first_not_of("\""));
        role.erase(0, role.find_first_not_of(","));
        role.erase(0, role.find_first_not_of(" "));
        role.erase(0, role.find_first_not_of("'"));
        role.erase(0, role.find_first_not_of("["));
        if (role.empty()) break;
        std::istringstream rolePair(role);
        std::string filmIdStr, character;
        std::getline(rolePair, filmIdStr, ',');
        std::getline(rolePair, character, ']');

        // Trim leading/trailing whitespace from filmIdStr and character
        filmIdStr.erase(filmIdStr.find_last_not_of(" ") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of(" "));
        character.erase(character.find_last_not_of(" ") + 1);
        character.erase(0, character.find_first_not_of(" "));

        // Trim leading/trailing single quote from filmIdStr and character
        filmIdStr.erase(filmIdStr.find_last_not_of("'") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of("'"));
        character.erase(character.find_last_not_of("'") + 1);
        character.erase(0, character.find_first_not_of("'"));

        if (filmIdStr.empty()) continue;
        if (character.empty()) continue;
        unsigned int filmId = std::stoul(filmIdStr);
        const Film* film = nullptr;
        for (const auto& f : flist) {  // using extern flist from global.h
            if (f.getID() == filmId) {
                film = &f;
                break;
            }
        }
        if (film) {
            roles.emplace_back(character, film);
        }
    }

    std::sort(roles.begin(), roles.end());
    return roles;
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
    for (const Actor::Role& role : roles) {
        os << "As " << role.character << " in \"" << role.film->getTitle()
           << "\"\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Actor& actor) {
    os << std::to_string(actor.getId()) << ';';
    os << actor.getName() << ';';
    os << actor.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (const Actor::Role& role : actor.getRoles()) {
        ss << '[';
        ss << role.film->getID() << ", " << role.character << ']' << ", ";
    }
    std::string result = ss.str();
    if (result.size() < 2) {
        return os << "[]";
    } else {
        result.resize(result.size() - 2);  // remove extra ", "
        result += ']';
        return os << result;
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
    for (const Film* film : films) {
        os << "\"" << film->getTitle() << "\"" << " (" << film->getYear()
           << ")\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Director& director) {
    os << std::to_string(director.getId()) << ';';
    os << director.getName() << ';';
    os << director.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (const Film* film : director.getFilms()) {
        ss << film->getID() << ", ";
    }
    std::string result = ss.str();
    if (result.size() < 2) {
        return os << "[]";
    } else {
        result.resize(result.size() - 2);  // remove extra ", "
        result += ']';
        return os << result;
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

std::string ptypeToString(ProducerType ptype) {
    switch (ptype) {
        case ProducerType::ExecutiveProducer:
            return "Executive Producer";
            break;
        default:
            return "Producer";
            break;
    }
}

void Producer::displayJobs(std::ostream& os) const {
    os << "Films produced by " << this->name << ":\n";
    for (const ProducerJob& job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " ("
           << job.film->getYear() << ") as ";
        os << ptypeToString(job.ptype) << '\n';
    }
}

std::ostream& operator<<(std::ostream& os, const Producer& producer) {
    os << std::to_string(producer.getId()) << ';';
    os << producer.getName() << ';';
    os << producer.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (const Producer::ProducerJob& job : producer.getJobs()) {
        ss << '[';
        ss << job.film->getID() << ", " << ptypeToString(job.ptype) << ']'
           << ", ";
    }
    std::string result = ss.str();
    if (result.size() < 2) {
        return os << "[]";
    } else {
        result.resize(result.size() - 2);  // remove extra ", "
        result += ']';
        return os << result;
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

std::string wtypeToString(WriterType wtype) {
    switch (wtype) {
        case WriterType::Screenplay:
            return "Screenplay";
            break;

        case WriterType::Story:
            return "Story";
            break;
        default:
            return "Writer";
            break;
    }
}

void Writer::displayJobs(std::ostream& os) const {
    os << "Films written by " << this->name << ":\n";
    for (const auto& job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " ("
           << job.film->getYear() << ") - ";
        os << wtypeToString(job.wtype) << '\n';
    }
}

std::ostream& operator<<(std::ostream& os, const Writer& writer) {
    os << std::to_string(writer.getId()) << ';';
    os << writer.getName() << ';';
    os << writer.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (const Writer::WriterJob& job : writer.getJobs()) {
        ss << '[';
        ss << job.film->getID() << ", " << wtypeToString(job.wtype) << ']'
           << ", ";
    }
    std::string result = ss.str();
    if (result.size() < 2) {
        return os << "[]";
    } else {
        result.resize(result.size() - 2);  // remove extra ", "
        result += ']';
        return os << result;
    }
}