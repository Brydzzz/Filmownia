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
## Page
Wszystkie strony dziedziczą po klasie Page, która ma zdefiniowane wirtualne metody:
- showOptions() do drukowania możliwych opcji
- print() do drukowania informacji specyficznych dla każdej strony
- nextAction() do wybierania co chcemy zrobić dalej w programie
- doAction() który egzekwuje to co wybraliśmy w nextAction()

## StartPage
Pozwala nam zalogować się albo się zarejestrować,  zobaczyć naszą stronę użytkownika (jeśli jesteśmy zalogowani) albo wejść do strony wyszkiwania.

## UserPage
Wyświetla recenzje naszego użytkownika, pozwala je też usunąć.

## BrowsePage
Pozwala na wyszukiwanie Filmów, albo osób (Actor, Director, Producer, Writer), i przy każdym wyszukiwaniu współpracuje z DatabaseManager

## FilmPage
Przedstawia informacje o filmie, pozwala na przejscie do stron osób powiązanych z filmem, oraz dodanie recenzji jeśli jesteśmy zalogowani.

## AddReviewPage
Służy do obsługi dodawania recenzji.

## Actor/Producer/Writer Page
Przedstawiają informacje o osobach, które reprezentują. Jeśli jesteśmy adminem dodatkowo pozwalają na dodanie roli/pracy albo jej usunięcie.




### Zarządzanie bazą danych
Klasa DatabaseManager zajmuje się działaniem na naszych plikach .csv. Najważniejsze metody to:
- personSearch(), która jest szablonem i wyszukuje dany typ osoby w odpowiedniej bazie danych
- movieSearch() które przeszukuje baze danych filmu
- replaceLine() która z wykorzystaniem pliku temp.txt edytuje wybraną bazę danych

## Inne uwagi do wykonanie projektu