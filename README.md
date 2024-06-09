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

### Strony

### Zarządzanie bazą danych

## Inne uwagi do wykonanie projektu