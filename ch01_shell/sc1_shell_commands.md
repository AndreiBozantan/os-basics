@import "../os.less"

## Comenzi în shell


### Introducere

Interpretorul de comenzi (sau shell în engleză) este un program (aplicație), similar cu orice alt program care îl folosim, scris de noi sau de altcineva. Principala sarcină a shell-ului este de a interacționa cu utilizatorul cu scopul rulării altor programe, și de a facilita comunicarea programelor între ele, folosind diverse mecanisme (argumente, semnale, canale, fișiere).

Shell-ul este un foarte bun exemplu de aplicație cu un design reușit, care permite ca programele rulate din shell să fie complet independente între ele, ceea ce ajuta la crearea unui sistem modular (în engleză [decoupling](https://en.wikipedia.org/wiki/Coupling_(computer_programming))). Pentru a realiza interacțiunea dintre mai multe programe folosind shell-ul, nu mai este neapărat necesar ca un program oarecare să știe ce face un alt program. Doar noi, ca utilizatori, folosim anumite informații despre fiecare program pentru a combina rezultatele lor, cu scopul de a realiza o acțiune mai complexă. Puteți să vedeți un reportaj interesant realizat la AT&T în 1982, despre versiunile inițiale ale shell-ului UNIX pe YouTube.
[<img src="https://i.ytimg.com/vi/tc4ROCJYbm0/sddefault.jpg" alt="AT&T UNIX 1982" width="200"/>](https://www.youtube.com/watch?v=tc4ROCJYbm0)

Pentru a executa comenzile utilizatorului shell-ul execută următoarele operații iterativ:

1. Citește din fișierul de intrare (de la tastatură).
2. Procesează textul citit și determină comanda (sau aplicația) care trebuie rulată.
3. Construiește un context de execuție (environment): argumente, director curent, variabile de mediu (ex. `$HOME`, `$PATH`).
4. lansează programul (sau comanda) în acest context de execuție.
5. Așteaptă terminarea execuției comenzii.
6. Repetă operațiile începând de la punctul 1.
 
În continuare vom folosi interpretorul de comenzi `bash` pentru a exemplifica interacțiunea dintre utilizatori, aplicații și sistemul de operare. Pentru a încerca exemplele de mai jos și pentru a rezolva exercițiile, puteți să folosiți Google Cloud Shell https://ssh.cloud.google.com/.


### Comenzi

Termenul **comandă** este folosit in mod generic pentru a indica orice program sau activitate lansate in execuție folosind un shell. Pentru a înțelege mai exact modul în care funcționează un shell vom face în continuare și o distincție într comenzi interne și externe.

#### Comenzi externe

Comenzile externe sunt programe independente care sunt disponibile în sistemul de fișiere. De exemplu câteva **comenzi externe** simple care sunt incluse de obicei cu sistemele de operare de tip UNIX sunt:
  - `uname` - afișează informații despre sistem
  - `date` - afișează sau modifică data sistemului
  - `whoami` - afișează utilizatorul curent
  - `man` - afișează manualul de utilizare pentru o comandă dată


##### Exemplu utilizare comenzi externe

```sh
$ uname
Linux
$ date
Tue Jan 19 03:14:08 GMT 2038
$ whoami
student
$ man
What manual page do you want?
$ man whoami
WHOAMI(1)

NAME
       whoami - print effective userid
```

#### Comenzi interne

**Comenzile interne** sunt funcționalități implementate direct în shell, și sunt de oicei folosite pentru a afla sau modifica detalii despre starea internă a acestuia. În continuare sunt enumerate câteva comenzi interne:
  - `help` - afișează informații utile despre utilizarea shell-ului
  - `history` - afșează o listă cu comenzile executate anterior
  - `exit` - închide aplicația shell (terminarea programului shell)
  - `cd` (**c**hange **d**irectory) - modifică directorul curent
  - `pwd` (**p**rint **w**orking **d**irectory) - afișează directorul curent

##### Exemplu utilizare comenzi interne

```sh
$ pwd
/home/student
$ cd ..
$ pwd
/home
$ cd 
$ pwd
/home/student
```
#### Comanda type

Pentru a determina dacă o comandă este externă sau internă folosim comanda internă `type` care va afișa tipul comenzii.

##### Exemplu utilizare comanda type

```sh
$ type pwd
pwd is a shell builtin
$ type mv
mv is /bin/mv
$ type uname
uname is hashed (/bin/uname)
```

Mesajele afișate de comanda type au următoarea semnificație:
Mesaj | Semnificație
------|-------------
`pwd is a shell builtin` | comanda `pwd` este internă (builtin).
`mv is /bin/mv` | comanda `mv` este externă și locația ei în sistemul de fișiere este `/bin/mv`.
`uname is hashed (/bin/uname)` | comanda `uname` este externă și locația ei în sistemul de fișiere este `/bin/uname`;<br /> în plus, locația comenzii este salvată intern în memorie de către shell, astfel încât, în momentul când comanda `uname` va fi rulată din nou, shell-ul nu va mai căuta locația ei în sistemul de fișiere.

### Exemplu funcționare shell

Pentru a înțelege mai multe detalii despre modul de funcționare a unui shell vom folosi ca exemplu un program Python care realizează operații similare cu interpretorul de comenzi `bash`. Pentru a realiza programul vom folosi editorul preferat și salvăm codul într-un fișier numit `posh.py` (**po**wer **sh**ell).

Pentru început vom afișa un *prompt* și vom citi o *comandă* de la tastatură (linia 1). În loc să executăm comanda o tipărim pe ecran (linia 2).

```python {.line-numbers}
s = input("> ")
print(s)
```

Pentru a executa programul vom introduce următoarea comandă in interpretorul de comenzi `bash`:
```sh
$ python3 posh.py
```

În continuare vom adăuga o buclă infinită, pentru ca shell-ul nostru să reia ciclul după procesarea unei comenzi.

```python {.line-numbers highlight=1}
while (True):
  s = input("> ")
  print(s)
```

În acest moment programul nostru rulează la infinit, și pentru a-l opri trebuie să folosim combinația de taste `Ctrl-C`, care în general oprește un program curent din shell în mod forțat. Pentru ca programul nostru să se termine în mod normal, vom adăuga prima comandă, `exit`.

```python {.line-numbers highlight=4-5}
while (True):
  s = input("> ")
  print(s)
  if s == "exit":
    exit()
```

Următoarele comenzi implementate sunt:
- `version`: afișează versiunea shell-ului;
- `help`: afișează comenzile recunosute.

```python {.line-numbers highlight=7-8}
VERSION="0.1"
while (True):
  s = input("> ")
  print(s)
  if s == "exit":
    exit()
  elif s == "version":
    print(VERSION)
  elif s == "help":
    print("exit version help")
```

În continuare vom adăuga un mesaje de eroare, pentru cazul când comanda nu este recunoscută de shell, și în plus, nu mai afișăm comanda citită de la tastatură pe ecran.

@import "posh/posh0.py" {.line-numbers highlight=10-11}

În continuare, pentru a face programul mai ușor de modificat în viitor, de exemplu când adăugăm noi comenzi, vom înlocui șirul de instructiuni `if` cu un dicționar, un idiom des folosit în Python. 
La linia 19 este citită o comandă de la tastatură, iar apoi, la linia 20, folosind funcția `get` vom căuta comanda respectivă în dicționarul cu comenzi `commands` definit la liniile 11-15.
Dicționarul `commands` asociază pentru fiecare nume de comandă, o funcție care implementează comanda respectivă și care va fi apelată la linia 24, pentru a executa comanda.

@import "posh/posh1.py" {.line-numbers }

Observație, comenzile definite mai sus în `posh` sunt echivalente cu comenzile interne din `bash`.

După această modificare, pentru a adăuga o nouă comandă internă vom proceda astfel: adăugăm un nou element în dicționarul `commands`, format din numele comenzii și funcția care va fi apelată pentru execuția comenzii, iar apoi scriem codul pentru funcția respectivă.

O altă observație este că am modificat comanda `help` să tipărească cheile din dicționar, astfel încât atunci când vom adăuga comenzi noi, nu mai e nevoie să facem modificări și în comanda help.

### Execuția programelor script în shell

Pentru a putea executa mai facil programul `posh.py` pe linia 1 am adăugat un comentariu special care începe cu caracterele `#!`, care se numește [shebang](https://en.wikipedia.org/wiki/Shebang_(Unix)).

```sh
#!/usr/bin/env python3
```

Când un fișier text care conține un shebang este folosit ca o comandă în shell, acest fișier va fi executat de shell folosind programul specificat după shebang. De obicei acest program este un interpretor de programe script (bash, python, node, etc.). 
În plus, pentru a putea executa programul Python fișierul `posh.py` trebuie să fie marcat ca executabil, folosind comanda:
```sh
$ chmod u+x posh.py
```
Acum vom putea executa programul `posh.py` astfel:
```sh
./posh.py
```

În mod similar putem să scriem fișiere script care conțin comenzi `bash`. De exemplu, putem scriem următoarele mai multe comenzi în fișierul text `sinfo`.

```sh
#!/bin/bash
date
uname
whoami
```

Apoi marcăm fișierul `sinfo` ca fiind executabil.

```sh
$ chmod u+x sinfo
```

Acum putem să executăm scriptul `sinfo` astfel:

```sh
$ ./sinfo
Tue Jan 19 03:14:08 GMT 2038
Linux
student
```


### Exerciții
1. Modificați comanda `exit` astfel încât să fie cerută o confirmare pentru terminarea programului (utilizatorul trebuie să confirme sau să anuleze folosind opțiunile yes/no sau y/n).

2. Modificați comanda `help` astfel încât să afișeze doar numele comenzilor, câte una pe o linie, după modelul de mai jos:
```
help
version
exit
```

3. Adăugați comanda `history` care afișează comenzile executate anterior, similar cu comanda `history` din `bash`.

4. Realizați un script `bash` numit `posh` care să execute programul Python `posh.py`.

5. Încercați să traduceți programul `posh.py` în limbajul `C` (tip: https://en.wikipedia.org/wiki/Function_pointer#Example_in_C)


------
Andrei Bozantan, 2020 
[![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

