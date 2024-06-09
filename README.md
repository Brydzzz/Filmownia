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
## Film
Reprezentuje Film i zawiera wszystko najważniejsze informacje, których chcielibyśmy się dowiedzieć o danej produkcji. Posiada możliwość "zrzucania się" do formatu kompatybilnego z naszymi plikami csv, oraz konstruktor kompatybilny z tymże formatem.
Posiada też getRating(), które oblicza średnia ocene z recenzji, oraz write(), ktory w estetyczny sposób wyrzuca na strumień wyjściowy informacje o filmie.

## Review
Reprezentuje recenzję, ktora trzyma pointer na film, który opisuje. Oprócz tego też zawiera metode write(), do zrzucania informacji na strumień wyjściowy.

### Osoby

### Strony

### Zarządzanie bazą danych

## Inne uwagi do wykonanie projektu