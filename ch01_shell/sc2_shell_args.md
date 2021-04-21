## Argumente în shell și programe

### Introducere
În secțiunea precedentă am prezentat câteva exemple de comenzi simple. Pentru a avea un sistem cu o funcționalitate mult mai bogată, shell-ul folosește mai multe mijloace pentru a stabili datele de intrare și modul de funcționare pentru comenzile executate: argumente, variabile de mediu, fișiere, canale, semnale, valorile returnate la terminarea unui program. Aceste mijloace pot fi considerate ca un mod de comunicație între shell și un program, dar pot fi folosite de shell pentru a facilita comunicația între două programe. De asemenea programele pot să folosească aceste facilități oferite de sistemul de operare pentru a comunica direct între ele, fără intermediul shell-ului. În această secțiune vom descrie următoarele modul în care sunt folosite argumentele în shell și în programe scrise în limbajele Python și C.

Majoritatea comenzilor executate din shell acceptă și un set de valori, care în acest context se numesc argumente. Argumentele pentru o comandă executată din shell sunt într-un fel similare cu parametrii unei funcții în limbajele de programare Python sau C. Aceste argumente stabilesc de obicei datele de intrare și modul de funcționare pentru comanda executată.

În continuare reluăm câteva din exemplele de comenzi cu argumente folosite deja anterior:

 - `$ man whoami` - parametrul specifică numele comenzii pentru care se va afișa manualul de utilizare;
 - `$ cd ..` - parametrul specifică numele directorului care va deveni directorul curent, în acest caz directorul părinte (`..`);
 - `$ type pwd` - parametrul specifică numele comenzii pentru care vrem să aflăm tipul (intern/extern).
 - `$ chmod u+x posh.py` - în acest caz avem doi parametrii:
   - `u+x` - specifică noile drepturi de acces pentru fișier; în acest caz proprietarul fișierului - `u` (user) - va avea în plus dreptul de execuție (`x`);
   - `posh.py` - specifică numele fișierului pentru care se modifica drepturile de access.

### Comanda echo
Pentru a înțelege mai exact modul în care sunt pot fi folosite argumentele specificate în linia de comandă, vom folosi ca exemplu comanda `echo` și vom implementa această comandă în inițial în limbajul Python și apoi vom face o comparație cu limbajul C. Comanda `echo` scrie în fișierul standard de ieșire (care de obicei este ecranul) argumentele primite, de exemplu:

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

### Programul echo în Python
Pentru accesarea argumentelor din linia de comandă într-un program scris în limbajul Python este folosită variabila `argv` definită în modulul `sys`. Pentru exemplificare vom folosi următorul program salvat în fișierul `echo.py`.

```py {.line-numbers}
#!/usr/bin/env python3
import sys

print('Arguments are:', sys.argv)
```

Pentru executarea programului vom marca întâi fișierul ca fiind executabil:
```bash
$ chmod u+x echo.py
```

Acum putem să executăm programul în diverse moduri:
```bash
$ ./echo.py hello
Arguments are: ['./echo.py', 'hello']
./echo.py hello os20
Arguments are: ['./echo.py', 'hello', 'os20']
```

Rulând programul `echo.py`, observăm că variabila `sys.argv` este o listă, și că primul argument din această listă (elementul de la poziția 0) este numele programului. Pentru a replica mai exact funcționalitatea comenzii `echo`, vom modifica programul `echo.py` să tipărească exact valorile din lista `sys.argv`:

```py {.line-numbers}
#!/usr/bin/env python3
import sys
for i in range(1, len(sys.argv)):
    print(sys.argv[i])
```

Pentru a tipări toate argumentele pe aceeași linie, separate de spațiu, la fel cu comanda `echo`, va trebui să folosim parametrul cu nume `end` pentru funcția `print`, și în plus să tipărim o linie goală la sfârșit:

@import "echo/echo.py" {.line-numbers}

Ca și un detaliu care poate fi semnificativ în unele situații, această variantă a programului `echo.py`, va tipări un caracter spațiu în plus la sfârșitul liniei, față de comannda `echo` din sistemul de operare. Pentru verificare putem folosi redirectarea fișierului standard de ieșire, pe care o vom discuta în detaliu într-un capitol următor. Apoi putem verifica dimensiunile pentru cele două fișiere folosind comanda `ls`, și putem observa că diferența constă în dimensiunea fișierelor, datorită spațiul adițional de la sfârșit.

```bash
$ echo hello os20! > echo1
$ ./echo.py hello os20! > echo2
$ ls -l
```

### Programul echo în C
În limbajul C, argumentele pentru program sunt accesibile prin cei doi parametrii ai funcței `main`:
 - `int argc`: specifică numărul de parametrii din linia de comandă (este inclus și numele programului care este primul argument);
 - `char* argv[]`: este un array de string-uri care conține argumentele din linia de comandă.
Pentru exemplificare vom include și varianta în limbajul C a programului `echo.py`.

<!-- @import "echo/echo.c" {.line-numbers} -->
[echo/echo.c](echo/echo.c ':include :type=code')

Pentru compliare și rulare folosim următoarele comenzi în shell:
```
$ gcc -Wall -Werror -o echo echo.c
$ ./echo hello os20
```

Pentru referință, puteți găsi o versiune oficială a codului în limbajul C pentru comanda `echo` la adresa https://github.com/coreutils/coreutils/blob/master/src/echo.c.

### Program pentru calcularea logaritmilor
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

@import "loga/loga.py" {.line-numbers}

La execuție apare următoarea eroare:
```bash
$ ./loga.py
Traceback (most recent call last):
  File "./loga.py", line 5, in <module>
    str = sys.argv[1]
IndexError: list index out of range
```

În acest caz problema este detectată mai devreme, la linia 5, în momentul când încercăm să accesăm elementul de la indexul 1 din lista `sys.argv`, iar programul este terminat forțat. În acest moment putem să observăm că în limbajul Python, la accesarea unui element dintr-o listă, se face și o validare suplimentară pentru a asigura faptul că indexul are o valoare validă, adică este mai mare sau egal cu zero și mai mic strict decât lungimea listei. Deoarece un array în limbajul C este doar o zonă de memorie care conține elementele array-ului și nu conține în plus numărul de elemente din array, nu se poate face automat aceeași verificare și în limbajul C. Deoarece lungimea array-ului este de obicei stocată separat (acest lucru fiind responsabilitata programatorului), această verificare trebuie inclusă explicit în limbajul C, în cazurile în care este necesară. În unele cazuri acest mod de funcționare poate produce erori subtile: deoarece se pot citi date invalide fără ca această problemă să fie detectată, ceea ce mai târziu va cauza rezultate incorecte. În plus, costul pentru verificările adiționale efectuate în Python este bine tolerat de procesoarele cu o arhitectură modernă folosind tehnici de predicție (în engleză: branch prediction https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array).



### Exerciții

1. Modificați programul `echo.py` astfel încât să nu tipărească spațiul adițional la sfârșit.

2. Faceți modificările necesare în programul `loga` pentru terminarea programului să fie normală (nu forțată de sistemul de operare) și să producă mesaje corespunzătoare în cazul în care linia de comandă nu este corectă.

3. Adăugați posibilitatea de a calcula logaritmul în orice bază atunci când programul `loga` primește 2 argumente, în acest caz primul argument fiind considerat baza, iar al doilea valoarea pentru care se calculează logaritmul.

4. Adăugați o validare că argumentele pentru programul `loga` sunt ambele numere întregi pozitive. (Se poate folosi fie funcția `strtol` sau o verificare că toate caracterele dintr-un string sunt cifre).

5. În mod similar cu programul `loga` implementați programul `expo` care calculează funcția exponențială, cu baza implicită 2, atunci când nu este speicificată și baza ca argument.

6. Realizați un program care calculează aria următoarelor forme geometrice, în funcție numărul de argumente primite în linia de comandă reprezentând dimensiunile formei:
    - aria cercului (1 argument - raza);
    - aria dreptunghiului (2 argumente - lungime, lățime)
    - aria triunghiului (3 argumente - lungimile laturilor)

7. Realizați un convertor de unitati de masură care poate funcționa ca în exemplele următoare (puteți găsi o listă cu unitățile de măsură imperiale la adresa: https://en.wikipedia.org/wiki/Imperial_units#Mass_and_weight):

    - `conv 5 m to inch`
    - `conv 2.2 kg to lb`
    - `conv 10 l to gallons`

------
Andrei Bozantan, 2020
[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

