# ARGUMENTE ÎN LINIA DE COMANDĂ

## Introducere
În secțiunea precedentă am prezentat câteva exemple de comenzi simple. Pentru a avea un sistem cu o funcționalitate mult mai bogată, shell-ul folosește mai multe mijloace pentru a stabili datele de intrare și modul de funcționare pentru comenzile executate: argumente, variabile de mediu, fișiere, canale, semnale, valorile returnate la terminarea unui program. Aceste mijloace pot fi considerate ca un mod de comunicare între shell și un program anume, dar pot fi folosite de shell pentru a facilita comunicarea dintre două programe. De asemenea programele pot să folosească aceste facilități oferite de sistemul de operare pentru a comunica direct între ele, fără intermediul shell-ului. În această secțiune vom descrie următoarele modul în care sunt folosite argumentele în shell și în programe scrise în limbajele Python și C.

Majoritatea comenzilor executate din shell acceptă și un set de valori, care, în acest context se numesc argumente. Argumentele pentru o comandă executată din shell sunt într-un fel similare cu parametrii unei funcții în limbajele de programare Python sau C. Aceste argumente stabilesc de obicei datele de intrare și modul de funcționare pentru comanda executată.

În continuare reluăm câteva din exemplele de comenzi cu argumente folosite deja anterior (+ mai multe exemple).

La aproape orice comanda avem mai multe optiuni pentru a o apela, in cazul in care nu cunoastem comanda, sau ceva nu este in regula o sa consultam documentatia din linux (fie cu comanda `man`, de la manual, fie cautand pe internet in documentatia oficiala pentru un format mai curat).

 - `$ man` - comanda man este utilizata pentru a afisa documentatia parametrului/comenzii trimise prin linia de comanda;
	- ex: `$ man whoami` - afiseaza documentatia comenzi whoami;
 	- ex: `$ man getline` - o sa afiseze documentatia, in terminal, a functiei getline(functie din C);
 - `$ cd` - cd, sau change directory, este o comanda din Linux, sau in alte sisteme de tip Unix, folosita sa schimbe directorul curent;
 	- ex: `$ cd ..` - directorul curent o sa fie directorul parinte;
 	- ex: `$ cd ~/Downloads` - directorul curent o sa fie setat in folderul Downloads;
 - `$ type` - comanda type afiseaza tipul comenzii parsat prin linia de comanda; 
 	- ex: `$ type pwd` - o sa afiseze, in terminal, type-ul lui pwd care este o comanda din shell; 
 	- ex: `$ type type` - tip-ul type-ului este o functie preconstruita din shell;
 - `$ chmod` - comanda chmod, mai precis modul de editare/modificare, ne permita sa modificam permisiunile de acces ale fisierelor si folderelor.
  	- ex: `$ chmod u+x` - în acest caz proprietarul fișierului - `u` (user) - va avea în plus dreptul de execuție (`x`);
	- Comanda `chmod` poate fi utilizata si sa revoce permisiunile unui file/directory;
  	- ex: `$ chmod u-rx exemple.txt` - da remove la permisunile de read si write pentru user;
   - `posh.py` - specifică numele fișierului pentru care se modifica drepturile de access.
 - `$ ls` - comanda ls, list directory, va lista directoarele si fisierele din directorul curent.
 	- ex: (daca pe desktop avem 3 fisiere cat.c cp.c test.c si efectuam comanda) `$ ls Desktop` - va afisa numele(cu tot cu numele extensiilor) fisierelor din directorul "Desktop", in cazul acesta va afisa in terminal `cat.c cp.c test.c`;
 	- daca un director este gol(blank) si se executa comanda `$ ls` nu se va afisa nimic;
 - `$ cat` - cat, concatenate, aceasta comanda afiseaza continutlui unui fisier, poate si combina mai multe fisiere (sintaxa generala `cat "lista de fisiere"`);
 	- ex: (daca avem in fisierul exemplu.txt textul "Astazi o sa cante Travis") `$ cat exemplu.txt` - va afisa continutul fisierului exemplu.txt, "Astazi o sa cante Travis";
 - `$ mkdir` - mkdir, sau make directory, este comanda prin care creeam directoare (sintaxa generala este `mkdir "nume director"`);
 	- ex: (directorul curent este Desktop-ul) `$ mkdir teme` - in directorul Desktop s-a creat folderul teme;
 - `$ touch` - comanda touch creeaza file goale (sintaxa generala: `touch "nume fisier"`);
 	- ex: (directorul curent este Desktop-ul) `$ touch r.txt` creeaza in directorul Desktop fisierul r.txt;
 - `$ history` - arata istoricul comenzilor executate;
 	- ex: `$ history` - o sa afiseze comenziile precedente;
 - `$ head` - arata primele 10 linii dintr-un fisier (sintaxa generala : `head "file name"`);
 	- ex: (Avem in fisierul num.txt primele 10 de numere prime daca efectuam `head num.txt` va afisa tot continutul fisierului(acelasi format de afisare gasit in fisierul sursa);
 	- ex: `$ head -1 num.txt` va afisa doar 2 (vezi documentatia pentru parametrii);
 - `$ tail` - tail este reverse-ul lui comenzii `head`, afiseala ultimele 10 linii din fisier;
 	- ex: `$ tail -2 num.txt` va afisa ultimele 2 numere prime din fisierul sursa;
 - `$ pwd` - comanda `pwd` da display la path-ul directorului curent;
 	- ex: (cd Desktop) `$pwd` - o sa afiseze calea absoluta, in cazul nostru /home/user/Desktop;
 - `$ who` - comanda `who` afiseaza user-ul logat la momentul dat, cat si ora de la care a fost logat pe system;
 - `$ top` - comanda `top` afiseaza o lista cu procesele desfasurate in background, echivalentul Task Manager de pe Windows (consultati documentatia pentru mai multe informatii);
 - `$ clear` - comanda `clear` "goleste" output-ul din terminal;
## Comanda echo
Pentru a înțelege mai exact modul în care sunt pot fi folosite argumentele specificate în linia de comandă, vom folosi ca exemplu comanda `echo` și vom implementa această comandă în inițial în limbajul Python și apoi vom face o comparație cu limbajul C. Comanda `echo` scrie în fișierul standard de ieșire (care de obicei este ecranul) argumentele primite:

Syntaxa generala pentru comanda `echo` este `echo "argumentele de input"` (pentru mai multe detalii consultati documentatia), mai jos aveti cateva exemple:

```shellsession
$ echo hello
hello

$ echo hello os20
hello os20

$ echo hello again os20!
hello again os20!

$ echo ubuntu linux
ubuntu linux

$ echo linus torvalds
linus torvalds

$ echo ana are mere
ana are mere
```

## Programul echo în Python
Pentru accesarea argumentelor din linia de comandă într-un program scris în limbajul Python este folosită variabila `argv` definită în modulul `sys`. Pentru exemplificare vom folosi următorul program salvat în fișierul `echo.py`.

```py
#!/usr/bin/env python3
import sys # importam biblioteca sys pentru a putea parsa argumentele din linia de comanda

print('Arguments are:', sys.argv)
```

Pentru executarea programului vom marca întâi fișierul ca fiind executabil:
```bash
$ chmod u+x echo.py # dam permisiunea userului de a executa ('x') fisierul
```

Acum putem să executăm programul în diverse moduri:
```bash
$ ./echo.py hello
Arguments are: ['./echo.py', 'hello']

$ ./echo.py hello os20
Arguments are: ['./echo.py', 'hello', 'os20']

$ ./echo.py Palantir Snap Robinhood Citadel 
Arguments are ['./echo.py', 'Palantir', 'Snap', 'Robinhood', 'Citadel']
```

Executand programul `echo.py`, observăm că variabila `sys.argv` este o listă, și că primul argument din această listă (elementul de la poziția 0) este numele programului. Pentru a replica mai exact funcționalitatea comenzii `echo`, vom modifica programul `echo.py` să tipărească exact valorile din lista `sys.argv`:

```py
#!/usr/bin/env python3
import sys
for i in range(1, len(sys.argv)):
    print(sys.argv[i])
```

Pentru a tipări toate argumentele pe aceeași linie, separate de spațiu, la fel cu comanda `echo`, va trebui să folosim parametrul cu nume `end` pentru funcția `print`, și în plus să tipărim o linie goală la sfârșit:

[echo](echo/echo.py ':include :type=code')

Ca și un detaliu care poate fi semnificativ în unele situații, această variantă a programului `echo.py`, va tipări un caracter spațiu în plus la sfârșitul liniei, față de comanda `echo` din sistemul de operare. Pentru verificare putem folosi redirectarea fișierului standard de ieșire, pe care o vom discuta în detaliu într-un capitol următor. Apoi putem verifica dimensiunile pentru cele două fișiere folosind comanda `ls`, și putem observa că diferența constă în dimensiunea fișierelor, datorită spațiul adițional de la sfârșit.

```bash
$ echo hello os20! > echo1
$ ./echo.py hello os20! > echo2
$ ls -l
```
Sau un approach mai algoritmic, parcurgem array-ul sys.argv pana la penultimul element, iar ultimul element il afisam individual, inafara for-ului:

```py
#!/usr/bin/env python3
import sys
for i in range(1, len(sys.argv) - 1):
    print(sys.argv[i], end = ' ')
print(sys.argv[len(sys.argv) - 1])
```

## Programul echo în C
În limbajul C, argumentele pentru program sunt accesibile prin cei doi parametrii ai funcței `main`:
 - `int argc`: specifică numărul de parametrii din linia de comandă (este inclus și numele programului care este primul argument);
 	- ex: (presupunem ca avem compilat un fisier sub numele "exemplu") "./exemplu 123 -41121 ana" - pentru acestea argc va avea valoarea 4;
 - `char* argv[]`: este un array de string-uri care conține argumentele din linia de comandă.
 	- ex: (presupunem ca avem compilat un fisier sub numele "exemplu") "./exemplu test 1 2 3 4 5 6" - pentru acestea argv = {"test", "1", "2", "3", "4", "5", "6"}, o lista de string-uri;
Pentru exemplificare vom include și varianta în limbajul C a programului `echo.py`.

[echo](echo/echo.c ':include :type=code')

Pentru compliare și rulare folosim următoarele comenzi în shell:
```
$ gcc -W -Werror -o echo echo.c // gcc este compilatorul standard pt a compila code in C
$ ./echo hello os20
```

Versiunea fara un spatiu in plus:

```c
#include <stdio.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc - 1; i++) {
        printf("%s ", argv[i]);
    }
    printf("%s", argv[argc - 1]);
    printf("\n");
}
```

Pentru referință, puteți găsi o versiune oficială a codului în limbajul C pentru comanda `echo` la adresa https://github.com/coreutils/coreutils/blob/master/src/echo.c.

## Program pentru calcularea logaritmilor
Ca un exemplu adițional vom considera și un program care calculează logaritmul în baza 2 pentru un număr, specificat ca argument în linia de comandă.

Vom salva versiunea inițială a programului în fișierul `loga.c`:

```c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* str = argv[1];
    long n = strtol(str, NULL, 10);
    printf("%f\n", log2(n));
    return 0;
}
```

Pentru a converti argumentul primit de program dintr-un string într-un număr vom folosi funcția `strtol` declarată în fișierul header `stdlib.h` (linia 7), iar pentru calcularea rezultatului vom folosi funcția `log2` (linia 8) declarată în fișierul header `math.h`.

Pentru compilare vom folosi o comandă similară cu cea folosită pentru programul `echo.c`:
```bash
$ gcc -Wall -Werror -o loga loga.c
```

Dar această comandă nu funcționează corect, ci afișează eroarea următoare:
```
loga.c:(.text+0x55): undefined reference to `log2'
collect2: error: ld returned 1 exit status
```
Aceasta este o eroare produsă de link editor și este semnalat faptul că nu a fost găsit codul pentru funcția `log2`. Pentru a rezolva problema, trebuie să instruim programul de link editare să includă și codul din biblioteca `math` în procesul de creare a programului executabil. Pentru aceasta vom include opțiunea `-lm`, unde `-l` are semnificația de `library` (adică faptul că se va  căuta cod pentru funcțiile folosite într-o bibliotecă), iar `m` este o prescurtare de la `math` și specifică biblioteca în care se face căutarea codului necesar. Atenție, această opțiune trebuie să apară după fișierul `.c` care include apelurile de bibliotecă.
```bash
$ gcc -Wall -Werror -o loga loga.c -lm
```

Acum putem folosi programul compilat:
``` bash
$ ./loga 1024
10.000000
```

Acest program simplu conține și câteva probleme, de exemplu o eroare apare in momentul când executăm programul fără argumente:
```bash
$ ./loga
Segmentation fault (core dumped)
```
Această problemă apare deoarece elementul `argv[1]` are valoarea `NULL`, iar acestă valoare este folosită de funcția `strtol`, care va încerca să citească date de la o adresă de memorie invalidă (adresa 0).

În continuare vom transcrie programul `loga` în limbajul Python, și vom analiza modul în care se manifestă această problemă în programul `loga.py`:

[loga](loga/loga.py ':include :type=code')

La execuție apare următoarea eroare:
```bash
$ ./loga.py
Traceback (most recent call last):
  File "./loga.py", line 5, in <module>
    str = sys.argv[1]
IndexError: list index out of range
```

În acest caz problema este detectată mai devreme, la linia 5, în momentul când încercăm să accesăm elementul de la indexul 1 din lista `sys.argv`, iar programul este terminat forțat. În acest moment putem să observăm că în limbajul Python, la accesarea unui element dintr-o listă, se face și o validare suplimentară pentru a asigura faptul că indexul are o valoare validă, adică este mai mare sau egal cu zero și mai mic strict decât lungimea listei. Deoarece un array în limbajul C este doar o zonă de memorie care conține elementele array-ului și nu conține în plus numărul de elemente din array, nu se poate face automat aceeași verificare și în limbajul C. Deoarece lungimea array-ului este de obicei stocată separat (acest lucru fiind responsabilitata programatorului), această verificare trebuie inclusă explicit în limbajul C, în cazurile în care este necesară. În unele cazuri acest mod de funcționare poate produce erori subtile: deoarece se pot citi date invalide fără ca această problemă să fie detectată, ceea ce mai târziu va cauza rezultate incorecte. În plus, costul pentru verificările adiționale efectuate în Python este bine tolerat de procesoarele cu o arhitectură modernă folosind tehnici de predicție (în engleză: branch prediction https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array).

O problema mai complexa ar fi calcularea logaritmului in baza a din b, primit din linia de comanda (pentru doar doua argumente, fisierul executabil si o valoare, vom calcula logaritm in baza 2 din b) cu toate validarile posibil pe inputul parsat din linia de comanda.

Code-ul in C este urmatoru:

```c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool checkValide(char *arg) { //verificam caractere
    int numOfDots = 0, numOfChars = 0;

    for (int i = 0; i < strlen(arg); ++i) {
        if (isdigit(arg[i])) {
            numOfChars++;
        } else {
            if (arg[i] == '.') {
                ++numOfDots;
            }
        }
    }

    return numOfChars + numOfDots == strlen(arg) && (numOfDots == 1 || numOfDots == 0); //numar real pozitiv adica poate sa admita un character '.' cel mult
}

bool validate(int argc, char **argv) {
    if (!(2 <= argc && argc <= 3)) { // mai multi parametrii = eroare
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        if (!checkValide(argv[i])) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char **argv) {
  if (!validate(argc, argv)) { // true - parametrii corecti, false - parametrii nu sunt numere reale pozitive
        fprintf(stderr, "Parametrii incorecti\n");
        exit(1);
    }

    switch (argc) {
        case 2: //pentru un singur numar
            printf("%.6f\n", log(atof(argv[1])) / log(2));
            break;
        case 3: //pentru doua numere
            printf("%.6f\n", log(atof(argv[1])) / log(atof(argv[2])));
            break;
    }
    return 0;
}
```
## Radicalul in C

Implementati programul `sqrt.c` care va primi din linia de comanda un singur parametru, un intreg pe 4 bytes, returnati valoarea radicalului, intreg (de ordin 2 din acest intreg).

```c
#include <stdio.h>
#include <stdlib.h>

void getSquareRoot(int32_t num) {
    int32_t i;
    for (i = 1; i * i <= num; i++);
    printf("valoarea radicalului este = %d\n", i - 1);
}

int32_t fromStringToInt32(char *inputString) {
    int32_t newNum = 0;
    for (int32_t i = 0; inputString[i]; i++) { 
        newNum = newNum * 10 + (inputString[i] - '0'); 
    }
    return newNum;
}

int main(int argc, char **argv) {
    getSquareRoot(fromStringToInt32(argv[1]));
}
```
Complexitatea programului anterior este O(sqrt(N)) unde N este numarul din care vrem sa computam square root-ul;

## Exerciții

1. Implementati programul `sqrt.c` care va primi din linia de comanda un singur parametru, un intreg pe 4 bytes, returnati valoarea radicalului (de ordin 2 din acest intreg).
	
	1.5. Implementati `sqrt.c` cu o complexitate in timp de O(LogN) (Hint: Cautare binara).
 
2. Modificați programul `echo.py` astfel încât să nu tipărească spațiul adițional la sfârșit.

3. Faceți modificările necesare în programul `loga` pentru terminarea programului să fie normală (nu forțată de sistemul de operare) și să producă mesaje corespunzătoare în cazul în care linia de comandă nu este corectă.

4. Adăugați posibilitatea de a calcula logaritmul în orice bază atunci când programul `loga` primește 2 argumente, în acest caz primul argument fiind considerat baza, iar al doilea valoarea pentru care se calculează logaritmul.

5. Adăugați o validare că argumentele pentru programul `loga` sunt ambele numere întregi pozitive. (Se poate folosi fie funcția `strtol` sau o verificare că toate caracterele dintr-un string sunt cifre).

6. În mod similar cu programul `loga` implementați programul `expo` care calculează funcția exponențială, cu baza implicită 2, atunci când nu este speicificată și baza ca argument.

7. Realizați un program care calculează aria următoarelor forme geometrice, în funcție numărul de argumente primite în linia de comandă reprezentând dimensiunile formei:
    - aria cercului (1 argument - raza);
    - aria dreptunghiului (2 argumente - lungime, lățime)
    - aria triunghiului (3 argumente - lungimile laturilor)

8. Realizați un convertor de unitati de masură care poate funcționa ca în exemplele următoare (puteți găsi o listă cu unitățile de măsură imperiale la adresa: https://en.wikipedia.org/wiki/Imperial_units#Mass_and_weight):

    - `conv 5 m to inch`
    - `conv 2.2 kg to lb`
    - `conv 10 l to gallons`

------
Andrei Bozantan, 2020
[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

