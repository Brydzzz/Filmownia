#include "person.h"

#include <algorithm>

#include "film.h"
#include "global.h"

extern std::vector<Film> flist;

const std::string &Person::getName() const { return name; }

const unsigned int Person::getId() const { return id; }

Date Person::getBirthDate() const { return birthDate; }

bool Person::operator==(const Person &other) { return id == other.id; }

const std::vector<Actor::Role> &Actor::getRoles() const { return roles; }

bool Actor::Role::operator<(const Role &other) const {
    return film->getTitle() < other.film->getTitle();
}

std::vector<Actor::Role>::iterator Actor::findRole(Film &film) {
    return findRole(Role("", film));
}

std::vector<Actor::Role>::iterator Actor::findRole(const Actor::Role &role) {
    auto it = std::lower_bound(roles.begin(), roles.end(), role);
    return it;
}

std::vector<Actor::Role> Actor::parseRoles(const std::string &content) {
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
        Film *film = nullptr;
        for (auto &f : flist) {  // using extern flist from global.h
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

void Actor::addRole(const std::string &character, Film &film) {
    Role newRole(character, film);
    auto it = findRole(newRole);
    if (it != roles.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a role for this film");
    } else {
        roles.insert(it, newRole);
    }
}

void Actor::deleteRole(Film &film) {
    auto it = findRole(film);
    if (it != roles.end() && it->film->getID() == film.getID()) {
        roles.erase(it);
    }
}

void Actor::displayActorInfo(std::ostream &os) const {
    os << name << '\n';
    os << "Birthdate: " << birthDate << '\n';
    if (!roles.empty()) {
        os << "Selected roles: \n";
        for (int i = 0; i < 5 && i < roles.size(); ++i) {
            os << "As " << roles[i].character << " in \""
               << roles[i].film->getTitle() << "\"\n";
        }
    }
}

void Actor::displayRoles(std::ostream &os) const {
    os << name << "'s roles: \n";
    for (const Actor::Role &role : roles) {
        os << "As " << role.character << " in \"" << role.film->getTitle()
           << "\"\n";
    }
}

std::ostream &operator<<(std::ostream &os, const Actor &actor) {
    os << std::to_string(actor.getId()) << ';';
    os << actor.getName() << ';';
    os << actor.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (const Actor::Role &role : actor.getRoles()) {
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

std::vector<Film *> Director::parseFilms(std::string content) {
    std::vector<Film *> films;
    std::istringstream iss(content);
    std::string filmIdStr;
    char firstBracket;
    iss >> firstBracket;
    if (firstBracket != '[') {
        throw std::invalid_argument("Wrong films format");
    }
    while (std::getline(iss, filmIdStr, ',')) {
        filmIdStr.erase(0, filmIdStr.find_first_not_of("\""));
        filmIdStr.erase(0, filmIdStr.find_first_not_of(","));
        filmIdStr.erase(0, filmIdStr.find_first_not_of("'"));

        if (filmIdStr.empty()) break;

        // Trim leading/trailing whitespace from filmIdStr
        filmIdStr.erase(filmIdStr.find_last_not_of(" ") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of(" "));

        // Trim leading/trailing single quote from filmIdStr
        filmIdStr.erase(filmIdStr.find_last_not_of("'") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of("'"));

        // Trim ']' from last element
        filmIdStr.erase(filmIdStr.find_last_not_of("]") + 1);

        if (filmIdStr.empty()) continue;

        unsigned int filmId = std::stoul(filmIdStr);
        Film *film = nullptr;
        for (auto &f : flist) {  // using extern flist from global.h
            if (f.getID() == filmId) {
                film = &f;
                break;
            }
        }
        if (film) {
            films.push_back(film);
        }
    }

    std::sort(films.begin(), films.end(), [](Film *lhs, Film *rhs) {
        return lhs->getTitle() < rhs->getTitle();
    });
    return films;
}

const std::vector<Film *> &Director::getFilms() const { return films; }

std::vector<Film *>::iterator Director::findFilm(Film &film) {
    auto it = std::lower_bound(
        films.begin(), films.end(), &film,
        [](Film *lhs, Film *rhs) { return lhs->getTitle() < rhs->getTitle(); });
    return it;
}

void Director::addFilm(Film &film) {
    auto it = findFilm(film);
    if (it != films.end() && (*it)->getID() == film.getID()) {
        throw std::invalid_argument("Film is already on the list");
    }
    films.insert(it, &film);
}

void Director::deleteFilm(Film &film) {
    auto it = findFilm(film);
    if (it != films.end() && (*it)->getID() == film.getID()) {
        films.erase(it);
    }
}

void Director::displayDirectorInfo(std::ostream &os) const {
    os << name << '\n';
    os << "Birthdate: " << birthDate << '\n';
    if (!films.empty()) {
        os << "Selected films: \n";
        for (int i = 0; i < 5 && i < films.size(); ++i) {
            os << "\"" << films[i]->getTitle() << "\"" << " ("
               << films[i]->getYear() << ")\n";
        }
    }
}
void Director::displayFilms(std::ostream &os) const {
    os << "Films directed by " << this->name << ":\n";
    for (Film *film : films) {
        os << "\"" << film->getTitle() << "\"" << " (" << film->getYear()
           << ")\n";
    }
}

std::ostream &operator<<(std::ostream &os, const Director &director) {
    os << std::to_string(director.getId()) << ';';
    os << director.getName() << ';';
    os << director.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (Film *film : director.getFilms()) {
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

std::vector<Producer::ProducerJob> Producer::parseFilms(std::string content) {
    std::vector<Producer::ProducerJob> jobs;
    std::istringstream iss(content);
    std::string job;

    while (std::getline(iss, job, ']')) {
        job.erase(0, job.find_first_not_of("\""));
        job.erase(0, job.find_first_not_of(","));
        job.erase(0, job.find_first_not_of(" "));
        job.erase(0, job.find_first_not_of("'"));
        job.erase(0, job.find_first_not_of("["));
        if (job.empty()) break;
        std::istringstream jobPair(job);
        std::string filmIdStr, producerType;
        std::getline(jobPair, filmIdStr, ',');
        std::getline(jobPair, producerType, ']');

        // Trim leading/trailing whitespace from filmIdStr and producerType
        filmIdStr.erase(filmIdStr.find_last_not_of(" ") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of(" "));
        producerType.erase(producerType.find_last_not_of(" ") + 1);
        producerType.erase(0, producerType.find_first_not_of(" "));

        // Trim leading/trailing single quote from filmIdStr and producerType
        filmIdStr.erase(filmIdStr.find_last_not_of("'") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of("'"));
        producerType.erase(producerType.find_last_not_of("'") + 1);
        producerType.erase(0, producerType.find_first_not_of("'"));
        ProducerType pt;
        if (producerType == "Producer") {
            pt = ProducerType::Producer;
        } else if (producerType == "Executive Producer") {
            pt = ProducerType::ExecutiveProducer;
        } else {
            continue;
        }
        if (filmIdStr.empty()) continue;
        if (producerType.empty()) continue;
        unsigned int filmId = std::stoul(filmIdStr);
        Film *film = nullptr;
        for (auto &f : flist) {  // using extern flist from global.h
            if (f.getID() == filmId) {
                film = &f;
                break;
            }
        }
        if (film) {
            jobs.emplace_back(pt, *film);
        }
    }
    std::sort(jobs.begin(), jobs.end());
    return jobs;
}

std::vector<Producer::ProducerJob>::iterator Producer::findJob(Film &film) {
    return findJob(ProducerJob(ProducerType::Producer, film));
}

std::vector<Producer::ProducerJob>::iterator Producer::findJob(const Producer::ProducerJob &job) {
    auto it = std::lower_bound(jobs.begin(), jobs.end(), job);
    return it;
}

const std::vector<Producer::ProducerJob> &Producer::getJobs() const {
    return jobs;
}

bool Producer::ProducerJob::operator<(const ProducerJob &other) const {
    return film->getTitle() < other.film->getTitle();
}

void Producer::addJob(ProducerType ptype, Film &film) {
    ProducerJob newJob(ptype, film);
    auto it = findJob(newJob);

    if (it != jobs.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a job for this film");
    }
    jobs.insert(it, newJob);
}

void Producer::deleteJob(Film &film) {
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

void Producer::displayJobs(std::ostream &os) const {
    os << "Films produced by " << this->name << ":\n";
    for (const ProducerJob &job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " ("
           << job.film->getYear() << ") as ";
        os << ptypeToString(job.ptype) << '\n';
    }
}

void Producer::displayProducerInfo(std::ostream &os) const {
    os << name << '\n';
    os << "Birthdate: " << birthDate << '\n';
    if (!jobs.empty()) {
        os << "Selected films: \n";
        for (int i = 0; i < 5 && i < jobs.size(); ++i) {
            os << "\"" << jobs[i].film->getTitle() << "\"" << " ("
               << jobs[i].film->getYear() << ")\n";
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Producer &producer) {
    os << std::to_string(producer.getId()) << ';';
    os << producer.getName() << ';';
    os << producer.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (const Producer::ProducerJob &job : producer.getJobs()) {
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

std::vector<Writer::WriterJob> Writer::parseFilms(std::string content) {
    std::vector<Writer::WriterJob> jobs;
    std::istringstream iss(content);
    std::string job;

    while (std::getline(iss, job, ']')) {
        job.erase(0, job.find_first_not_of("\""));
        job.erase(0, job.find_first_not_of(","));
        job.erase(0, job.find_first_not_of(" "));
        job.erase(0, job.find_first_not_of("'"));
        job.erase(0, job.find_first_not_of("["));
        if (job.empty()) break;
        std::istringstream jobPair(job);
        std::string filmIdStr, writerType;
        std::getline(jobPair, filmIdStr, ',');
        std::getline(jobPair, writerType, ']');

        // Trim leading/trailing whitespace from filmIdStr and writerType
        filmIdStr.erase(filmIdStr.find_last_not_of(" ") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of(" "));
        writerType.erase(writerType.find_last_not_of(" ") + 1);
        writerType.erase(0, writerType.find_first_not_of(" "));

        // Trim leading/trailing single quote from filmIdStr and writerType
        filmIdStr.erase(filmIdStr.find_last_not_of("'") + 1);
        filmIdStr.erase(0, filmIdStr.find_first_not_of("'"));
        writerType.erase(writerType.find_last_not_of("'") + 1);
        writerType.erase(0, writerType.find_first_not_of("'"));

        WriterType wt;
        if (writerType == "Screenplay") {
            wt = WriterType::Screenplay;
        } else if (writerType == "Story") {
            wt = WriterType::Screenplay;
        } else if (writerType == "Writer") {
            wt = WriterType::Writer;
        } else {
            continue;
        }
        if (filmIdStr.empty()) continue;
        if (writerType.empty()) continue;

        unsigned int filmId = std::stoul(filmIdStr);
        Film *film = nullptr;
        for (auto &f : flist) {  // using extern flist from global.h
            if (f.getID() == filmId) {
                film = &f;
                break;
            }
        }
        if (film) {
            jobs.emplace_back(wt, *film);
        }
    }
    std::sort(jobs.begin(), jobs.end());
    return jobs;
}

std::vector<Writer::WriterJob>::iterator Writer::findJob(Film &film) {
    return findJob(WriterJob(WriterType::Screenplay, film));
}

std::vector<Writer::WriterJob>::iterator Writer::findJob(const Writer::WriterJob &job) {
    auto it = std::lower_bound(jobs.begin(), jobs.end(), job);
    return it;
}

const std::vector<Writer::WriterJob> &Writer::getJobs() const { return jobs; }

bool Writer::WriterJob::operator<(const WriterJob &other) const {
    return film->getTitle() < other.film->getTitle();
}

void Writer::addJob(WriterType wtype, Film &film) {
    WriterJob newJob(wtype, film);
    auto it = findJob(newJob);

    if (it != jobs.end() && it->film->getID() == film.getID()) {
        throw std::invalid_argument("There is already a job for this film");
    }
    jobs.insert(it, newJob);
}

void Writer::deleteJob(Film &film) {
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

void Writer::displayJobs(std::ostream &os) const {
    os << "Films written by " << this->name << ":\n";
    for (const auto &job : jobs) {
        os << "\"" << job.film->getTitle() << "\"" << " ("
           << job.film->getYear() << ") - ";
        os << wtypeToString(job.wtype) << '\n';
    }
}

void Writer::displayWriterInfo(std::ostream &os) const {
    os << name << '\n';
    os << "Birthdate: " << birthDate << '\n';
    if (!jobs.empty()) {
        os << "Selected films: \n";
        for (int i = 0; i < 5 && i < jobs.size(); ++i) {
            os << "\"" << jobs[i].film->getTitle() << "\"" << " ("
               << jobs[i].film->getYear() << ")\n";
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Writer &writer) {
    os << std::to_string(writer.getId()) << ';';
    os << writer.getName() << ';';
    os << writer.getBirthDate() << ';';
    std::stringstream ss;
    ss << '[';
    for (const Writer::WriterJob &job : writer.getJobs()) {
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