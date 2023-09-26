# Wirtualny Ścwiat - wersja C++.

**Cel Projektu**
---
Celem projektu jest implementacja prostego symulatora wirtualnego świata, który ma mieć charakter dwuwymiarowej tablicy o rozmiarach NxN (domyślnie 20x20). W świecie tym będą istniały proste formy życia o odmiennym zachowaniu. Każdy z organizmów zajmuje dokładnie jedno pole w tablicy, na każdym polu może znajdować się co najwyżej jeden organizm (w przypadku kolizji jeden z nich powinien zostać usunięty lub przesunięty).
Symulator ma mieć charakter turowy. W każdej turze wszystkie organizmy istniejące na świecie mają wykonać akcję stosowną do ich rodzaju. Część z nich będzie się poruszała (organizmy zwierzęce), część będzie nieruchoma (organizmy roślinne). W przypadku kolizji (jeden z organizmów znajdzie się na tym samym polu, co inny) jeden z organizmów zwycięża, zabijając (np. wilk) lub odganiając (np. żółw) konkurenta. Kolejność ruchów organizmów w turze zależy od ich inicjatywy. Pierwsze ruszają się zwierzęta posiadające najwyższą inicjatywę. W przypadku zwierząt o takiej samej inicjatywie o kolejności decyduje zasada starszeństwa (pierwszy rusza się dłużej żyjący). Zwycięstwo przy spotkaniu zależy od siły organizmu, choć będą od tej zasady wyjątki (patrz: Tabela 1). Przy równej sile zwycięża organizm, który zaatakował. Przy uruchomieniu programu na planszy powinno się pojawić po kilka sztuk przydzielonych studentowi zwierząt oraz roślin. Okno programu powinno zawierać pole, w którym wypisywane będą informacje o rezultatach walk, spożyciu roślin i innych zdarzeniach zachodzących w świecie.


**Zadanie  z przedmiotu Programowanie Obiektowe na trzecim semestrze studiów.**

---

**Wejście**
---

Na wejściu programu zostanie podana liczba zamówień (nie będzie większa niż 100000) oraz zamówienia w postaci par a b (każde w osobnej linii (0 ≤ a < b < 2000000000).

**Wyjście**
---
    
Na wyjściu należy wypisać minimalną liczbę taśm potrzebnych do zrealizowania zamówienia oraz te zamówienia, których anulowanie zmniejszy liczbę wymaganych taśm. Zamówienia powinny być uporządkowane względem numeru początkowego, oraz numeru końcowego (w przypadku takich samych numerów początkowych).

**Przykłady**
---


**Wejście**
<code>
6
0 10
1 9
2 8
3 7
4 6
5 5
</code>

**Wyjście**
<code>
6
0 10
1 9
2 8
3 7
4 6
5 5
</code>

---

**Wejście**
<code>
10
0 10
11 12
9 12
8 13
12 13
1 2
3 4
5 6
1 3
4 6
</code>

**Wyjście**
<code>
4
8 13
9 12
11 12
12 13
</code>
