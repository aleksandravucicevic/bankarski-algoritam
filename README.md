# Bankarski algoritam (Banker's algorithm)
Program prikazuje način rada _Bankarskog algoritma_, koji omogućava upravljanje alokacijom resursa i sprečavanje zastoja (deadlock) u sistemima sa više procesa i resursa. 
Napisan je u C++ programskom jeziku i obezbjeđuje simulaciju dodjele resursa, provjeru sigurnog stanja i obradu zahtjeva procesa.

## Opis
Program simulira rad sistema sa više procesa i tipova resursa.  

Za svaki proces se čuvaju informacije o:
* maksimalnim potrebama (**maksimalno**)
* trenutno alociranim resursima (**alocirano**)
* preostalim potrebama (**potrebno**)
* dostupnim resursima u sistemu (**raspolozivo**)

Algoritam:
1. Učitavaju se podaci iz fajla
2. Provjerava se da li je sistem u sigurnom (stabilnom) stanju
3. Simuliraju se zahtjevi procesa za dodatnim resursima
4. Ispituje se da li bi zahtjev bio odobren bez ugrožavanja sigurnosti sistema

## Izlaz iz simulacije
Program ispisuje:
* Broj i nazive procesa i resursa
* Matrice **alokacije** i **maksimalnih zahtjeva**
* Listu zahtjeva
* Matricu **potreba**
* Da li je sistem u stabilnom stanju
* Da li su pojedinačni zahtjevi procesa odobreni ili odbijeni

## Primjer izvršavanja programa (za podaci.txt)
Broj procesa: 5  
Nazivi procesa: P0 P1 P2 P3 P4  
Broj resursa: 3  
Nazivi resursa: A B C  
Broj instanci po resursu: 10 5 7  
Vektor raspolozivosti: 3 3 2  
Matrica alokacija:  
0 1 0  
2 0 0  
3 0 2  
2 1 1  
0 0 2  

Matrica maksimalnih zahtjeva:  
7 5 3  
3 2 2  
9 0 2  
2 2 2  
4 3 3  

Lista zahtjeva:  
P1 1 1 2  
P2 3 0 0  
P4 3 3 1  

--- Rezultati simulacije ---  
Matrica potreba:  
7 4 3  
1 2 2  
6 0 0  
0 1 1  
4 3 1  
Sistem je u stabilnom stanju (P1->P3->P4->P0->P2).  
Zahtjev (P1, 1, 1, 2) ce biti odobren.  
Zahtjev (P2, 3, 0, 0) ce biti odobren.  
Zahtjev (P4, 3, 3, 1) nece biti odobren.  

# Autorska prava
© 2025 Aleksandra Vučićević

