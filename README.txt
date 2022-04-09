Nucuta Diana 314 CC 
Tema 1 SD

Am utilizat urmatoarele stive:
-o stiva stack pentru a retine toate formele textului
-o stiva comenzi pentru a retine comenzile
-o stiva (redoStack) care ne ajuta sa salvam ce se intampla cand dam undo

Pe masura ce citesc din fisier adaug fie in stiva de text, fie in stiva de comenzi,
am un icounter care ma ajuta sa identific cand se introduc comenzi sau text
Cand icount e par e text, cand e impar sunt comenzi.
Cand sunt comenzi am un switch mare, scot acel '\n' de la final de buffer si
bag comanda in switch (tin cont totusi doar de primul cuvant din comanda deoarece restul pot
fi parametrii ei). Fiecarei comenzi ii corespunde un numar, alfa.
De fiecare data cand aplic o comanda, salvez in stack textul si daca comanda e save
atunci toata stiva de text se sterge inafara de top-ul ei, adica ultima forma.
Prin comanda quit ok devine 1, deci nu se mai citeste nimic din fisier si se termina executia programului.
(textul se citea din fisier cat timp q era 0), se da pop la tot ce era in stiva de text deoarece este posibil
sa nu se fi dat save asa ca in stiva text sa existe formele nesalvate.
Dupa fiecare comanda aplicata salvez starea textului in stiva text.


