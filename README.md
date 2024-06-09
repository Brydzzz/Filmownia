# Projekt PROI 2024L

## Skład zespołu

- Kinga Łukiewicz
- Brygida Silawko
- Tomasz Smoleń

## Temat Projektu

## Używanie programu

### Budowanie programu
W katalogu projektu wywołaj:
```bash
cmake -S . -B build
cmake --build build --target main
```
### Uruchomienie programu

```bash
(cd build && ./main)
```

### Przykładowe użycia

1. Przeglądanie bazy z poziomu gościa
![example 1 gif](./docs/example1.gif)
2. Dodawanie ocen jako zalogowany użytkowik
![example 2 gif](./docs/example2.gif)
3. Edycja bazy z poziomu admina
![example 3 gif](./docs/example3.gif)

## Testy jednostkowe

Należy zbudować wybrany test a następnie go uruchomić:
```bash
cmake --build build --target <wybrany test>
(cd build && ./<nazwa pliku wykonywalnego>)
```
np.
```bash
cmake --build build --target testPerson
(cd build && ./testPerson)
```
Dostępne testy:
- `testDate.cpp`
- `testFilm.cpp`
- `testPerson.cpp`
- `testUser.cpp`

## Klasy w programie

### Użytkownicy

### Film i recenzje

### Osoby

Klasa `Person` reprezentuje osobę i zawiera jej `id`, imię i nazwisko (`name`) oraz datę urodzenia (`birthDate`)
Po klasie `Person` dziedziczą:
- `Actor` - dodatkowy atrybut: `std::vector<Role> roles` - lista ról granych przez aktora, gdzie każda rola zawiera nazwę postaci i wskaźnik na film.
- `Director` - dodatkowy atrybut: `std::vector<Film *> films` - lista filmów wyreżyserowanych przez reżysera.
- `Producer` - dodatkowy atrybut: `std::vector<ProducerJob> jobs` - lista prac producenta, gdzie każda praca zawiera typ producenta i wskaźnik na film.
- `Writer` - dodatkowy atrybut: `std::vector<WriterJob> jobs` - lista prac scenarzysty, gdzie każda praca zawiera typ scenarzysty i wskaźnik na film.

Każda z osób ma metody na dodawanie lub usuwanie elementu z jej kolekcji, wyświetlanie informacji o niej oraz wyszukiwanie filmów, w których brała udział.

Klasy dziedziczące po `Person` są używane w celu wyświetlenia stron osób w głównym programie oraz łatwiejszej edycji bazy danych.

### Strony

### Zarządzanie bazą danych

## Inne uwagi do wykonanie projektu