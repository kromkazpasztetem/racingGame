#Gra Wyścigowa
Prosta gra napisana w języku C, z użyciem bilbioteki CSFML i narzędzia CMake. 
Auta przemieszczają się o modyfikacje wektora, który powstaje przez kliknięcie myszką
 w wyznaczonym obszarze wokół samochodu. W razie wypadnięcia z trasy ich "szybkość" 
(długość wektora) jest znacznie zmniejszana.
##Opis modułów
###main
Wywołanie modułu odpowiedzialego za okno startowe, okno gry i okno pożegnalne oraz
przekazywanie numeru wybranego toru i informacji o wygranej jednego z graczy.
###windowManager
Funkcje ułatwiające obsługę okien:
* zdefiniowanie struktury z parametrami okna
* tworzenie pustego okna w danym rozmiarze, z tłem i tytułem i zwrócenie struktury z parametrami okna
* tworzenie obrazka (sprite) z tekstury w pliku
###welcomeWindow
Tworzy okno startowe gry z wyborem toru. Zamyka się po wyborze.
###gameWindow
Tworzy okno, w którym odbywa się gra.
* wczytywanie mapy toru z pliku bitowego
* obsługa kliknięcia
* obliczanie nowego wektora
* sprawdzanie, czy auto dojechało do mety
* zmiana pozycji samochodzików i ich wektorów po kliknięciu, obrót w kierunku wektora
* rysowanie aut, wektorów i okręgów
###geometry
Funkcje tworzące wektory i okręgi oraz proste funkcje matematyczne.
* zaokrąglanie liczby typu `float` do typu całkowitego `int`
* wartość bezwzględna typu `float`
* kwadrat liczby typu `float`
* tworzenie okręgu
* tworzenie grotu wektora
* tworzenie linii pomiędzy dwoma punktami
* sprawdzanie czy punkt należy do kształtu
* sprawdzanie czy dwa odcinki się przecinają
###goodbyeWindow
Okno pożegnalne gry z informacją, który gracz wygrał. Zamyka się po kliknięciu.