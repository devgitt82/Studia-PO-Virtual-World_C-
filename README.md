# Wirtualny Świat - wersja C++.

**Cel Projektu**
---
> Celem projektu jest implementacja prostego symulatora wirtualnego świata, który ma mieć charakter dwuwymiarowej tablicy o rozmiarach NxN (domyślnie 20x20). W świecie tym będą istniały proste formy życia o odmiennym zachowaniu. Każdy z organizmów zajmuje dokładnie jedno pole w tablicy, na każdym polu może znajdować się co najwyżej jeden organizm (w przypadku kolizji jeden z nich powinien zostać usunięty lub przesunięty).
Symulator ma mieć charakter turowy. W każdej turze wszystkie organizmy istniejące na świecie mają wykonać akcję stosowną do ich rodzaju. Część z nich będzie się poruszała (organizmy zwierzęce), część będzie nieruchoma (organizmy roślinne). W przypadku kolizji (jeden z organizmów znajdzie się na tym samym polu, co inny) jeden z organizmów zwycięża, zabijając (np. wilk) lub odganiając (np. żółw) konkurenta. Kolejność ruchów organizmów w turze zależy od ich inicjatywy. Pierwsze ruszają się zwierzęta posiadające najwyższą inicjatywę. W przypadku zwierząt o takiej samej inicjatywie o kolejności decyduje zasada starszeństwa (pierwszy rusza się dłużej żyjący). Zwycięstwo przy spotkaniu zależy od siły organizmu, choć będą od tej zasady wyjątki (patrz: Tabela 1). Przy równej sile zwycięża organizm, który zaatakował. Przy uruchomieniu programu na planszy powinno się pojawić po kilka sztuk przydzielonych studentowi zwierząt oraz roślin. Okno programu powinno zawierać pole, w którym wypisywane będą informacje o rezultatach walk, spożyciu roślin i innych zdarzeniach zachodzących w świecie.


**Zadanie  z przedmiotu Programowanie Obiektowe na trzecim semestrze studiów.**

---

**Wymagania**
---

> Należy utworzyć klasę Świat (Swiat) będącą kontenerem organizmów. <br>Powinna zawierać m.in. metody:<br><br>
> * wykonajTure()
> * rysujSwiat()<br><br>
> pola:
> * organizmy <br>
> Należy również utworzyć abstrakcyjną klasę Organizm. podstawowe pola:
> * siła
> * inicjatywa
* położenie (x,y) (należy zwrócić uwagę aby uniknąć możliwej redundancji - skoro obiekt organizm zawiera informację o swoim położeniu- nie powinna być ona powielona w klasie świat).
* świat - referencja do świata w którym znajduje się organizm<br>
> podstawowe metody:
* akcja() → określa zachowanie organizmu w trakcie tury,
* kolizja() → określa zachowanie organizmu w trakcie kontaktu/zderzenia z innym organizmem,
* rysowanie() → powoduje narysowanie symbolicznej reprezentacji organizmu.<br>

Klasa Organizm powinna być abstrakcyjna. Dziedziczyć po niej powinny dwie kolejne abstrakcyjne klasy: Roślina oraz Zwierzę.

W klasie Zwierze należy zaimplementować wspólne dla wszystkich/większości zwierząt zachowania, przede wszystkim:
•	podstawową formę ruchu w metodzie akcja() → każde typowe zwierze w swojej turze przesuwa się na wybrane losowo, sąsiednie pole,
•	rozmnażanie w ramach metody kolizja() → przy kolizji z organizmem tego samego gatunku nie dochodzi do walki, oba zwierzęta pozostają na swoich miejscach, koło nich pojawia się trzecie zwierze, tego samego gatunku.

Zaimplementuj 5 klas zwierząt (wilk, owca , jedno zwierze wymyślone przez Ciebie, 2 zwierzęta przydzielone na podstawie Twojego numeru indeksu lub inicjałów ). Rodzaje zwierząt definiuje poniższa tabela.

W klasie Roślina zaimplementuj wspólne dla wszystkich/większości roślin zachowania, przede wszystkim:
•	symulacja rozprzestrzeniania się rośliny w metodzie akcja() → z pewnym
prawdopodobieństwem każda z roślin może „zasiać” nową roślinę tego samego gatunku na losowym, sąsiednim polu.

Wszystkie rośliny mają zerową inicjatywę.


Zaimplementuj 3 klasy roślin (trawa oraz 2 rośliny przydzielone na podstawie Twojego numeru indeksu lub inicjałów). Rodzaje roślin definiuje poniższa tabela.

Stwórz klasę Świat zawierającą dwuwymiarową tablicę wskaźników na obiekty klasy Organizm. Zaimplementuj przebieg tury, wywołując metody akcja() dla wszystkich organizmów oraz kolizja() dla organizmów na tym
samym polu. Pamiętaj, że kolejność wywoływania metody akcja() zależy od inicjatywy (lub wieku, w przypadku równych wartości inicjatyw) organizmu.
Organizmy mają możliwość wpływania na stan świata. Dlatego istnieje konieczność przekazania metodom akcja() oraz kolizja() parametru określającego obiekt klasy Świat. Postaraj się, aby klasa Świat definiowała jako publiczne składowe tylko takie pola i metody, które są potrzebne
pozostałym obiektom aplikacji do działania. Pozostałą funkcjonalność świata staraj się zawrzeć w składowych prywatnych.

Wizualizację świata należy przeprowadzić w konsoli. Każdy organizm jest reprezentowany przez inny symbol ASCII. Naciśnięcie jednego z klawiszy powoduje przejście do kolejnej tury, wyczyszczenie konsoli i ponowne wypisanie odpowiednich symboli, reprezentujących zmieniony stan gry. Co najmniej jedna linia tekstu w konsoli przeznaczona jest na raportowanie wyników
zdarzeń takich jak jedzenie lub wynik walki.



