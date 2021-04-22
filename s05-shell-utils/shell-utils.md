# Funcționalități utile în shell

## Caractere speciale în shell

Din exemplele rulate până acum observăm că separatorul pentru argumentele din linia de comandă este caracterul spațiu, iar pentru a confirma acest lucru putem încerca să folosim mai multe spații între argumente:

```sh
$ echo 1 2 3
1 2 3
$ echo 1   2   3
1 2 3
```

Caracterele speciale din shell sunt:
<code>&num; & * ? [ ] ( ) = | ^ ; < > &grave; $ ” ‚ \ ~ </code>

### Anularea caracterelor speciale
Pentru a anula caracterele speciale, se pot folosi următoarele moduri de deautorizare (escape):
 - apostrofuri (`'text'`) - anulează toate caracterele speciale
 - ghilimele (`"text"`) - anulează caracterele speciale, cu excepția `$`, `'` și `\`, dacă este urmat de unul din caracterele `$`, <code>&grave;</code> , `"`, `\` sau newline.
 - backslash (`\c`) - anulează caracterul special imediat următor sau elimnă caracterul `\n` la sfârșit de linie

##### Exemplu
```sh
$ echo '1   2   3'
1   2   3

$ echo '1   "2"   3'
1   "2"   3

$ echo 1   "2"   3
1 2 3

$ echo "1   2   3"
1   2   3

echo 1\ \ \ 2\ \ \ 3
1   2   3
```

```sh
$ echo ~
/home/student

$ echo "~"
~

$ echo '~'
~

$ echo \~
~
```

```sh
$ echo $HOME
/home/student

$ echo "$HOME"
/home/student

$ echo '$HOME'
$HOME

$ echo \$HOME
$HOME
```

```sh
$ echo "\""
"
$ echo "\> "
\>
```

### Șabloane pentru numele fișierelor
Caracterele `*` și `?` au funcționalitatea specială de a specifica un șablon pentru numele fișierelor. Părțile comenzilor care conțin aceste caractere vor fi substituite de shell cu toate fișierele care se potrivesc cu șablonul definit, astfel: `?` se potrivește cu un singur caracter, iar `*` se potrivește cu zero sau mai multe caractere.

```sh
$ touch test.c
$ touch test.h
$ touch test.py
$ echo *
$ echo test.?
```


## Redirectare, Pipes, Substituire

În această secțiune vor fi prezentate câteva facilități foarte importante din shell care ajută la executarea unor operații complexe compuse din operații mai simple. Aceste facilități sunt folosite pentru construirea unui sistem modular, în care programele nu au interdependințe, astfel încât complexitatea codului pentru programele individuale rămâne la un nivel mic.

### Redirectare
În mod implicit, majoritatea comenzilor UNIX utilizează tastatura ca fișier standard de intrare și ecranul ca fișier standard de ieșire. Interpretorul  de comenzi oferă posibilitatea de a stabili alte fișiere de intrare (input) și ieșire (output) care să fie atașate unui program care este rulat. Această facilitate este numită redirectare a fișierelor standard de intrare/ieșire (IO redirection).

Toate fișierele folosite de un program au atașat un identificator numeric (file descriptor). Fișierele standard au următoarele valori asociate ca identificatori:
- `0` – fișierul standard de intrare (`stdin`)
- `1` – fișierul standard de ieșire (`stdout`)
- `2` – fișierul standard de erori (`stderr`)

Sintaxa generală a unei comenzi care folosește redirectarea fișierelor standard este:
```sh
$ command <input >output
```
Pentru modificarea fișierelor de intrare/ieșire se folosesc următoarele expresii (shell-ul va detecta caracterele speciale):
- `<` - redirectarea fișierului standard de intrare
- `>` - redirectarea fișierului standard de ieșire cu suprascriere (dacă fișierul există, conținutul lui este șters);
- `>>` - redirectare fișierului standard de ieșire cu adăugare (conținutul fișierului NU este șters; informațiile noi sunt adăugate la sfârșitul fișierului);
- `2>` - redirectarea fișierului standard de erori, cu suprascriere
- `2>>` - redirectarea fișierului standard de erori, cu adăugare



##### Exemplu: redirectarea fișierului standard de ieșire
```sh
$ cat test.c >test2.c
```
Listarea se face în fișierul `p2.c`, în loc să se facă pe ecran. Shell-ul va deschide fișierul `p2.c` astfel încât i se atribuie file descriptorul 1, și conținutul existent în fișierul `p2.c` este șters, iar dacă fișierul nu există, este creat.

```sh
$ echo Hello > hello.txt
$ cat music.mp3 > /dev/audio
```

##### Exemplu: redirectarea fișierului standard de erori
Pentru redirectare fișierului standard de erori se folosește sintaxa `2>` sau `2>>`:
```sh
$ ls "missing file"
ls: cannot access 'missing file': No such file or directory

$ ls "missing file" 2> /tmp/err.log

$ cat /tmp/err.log
ls: cannot access 'missing file': No such file or directory

$ ls "missing file" 2>> /tmp/err.log

$ cat /tmp/err.log
ls: cannot access 'missing file': No such file or directory
ls: cannot access 'missing file': No such file or directory

$ ls "missing file" 2> /dev/null
```

### Pipes
Redirectarea se poate realiza și folosind caracterul `|` folosind sintaxa:
```sh
$ prog1 | prog2
```

În această situație `prog1` și `prog2` sunt lansate simultan în execuție, ieșirea de la `prog1` fiind utilizată ca intrare pentru `prog2`. De obicei, `prog2` așteaptă până când `prog1` produce un element (o linie); cu alte cuvinte, `prog2` NU așteaptă până la finalizarea `prog1` pentru a începe procesarea. Pentru a realiza acestă funcționalitate, `prog1` și `prog2` folosesc un fișier temporar comun, numit pipe (conductă), care nu este parte din file sistem (nu este scris pe disc).
Comanda `prog1 | prog2` este aproximativ echivalentă cu comenzile:
```sh
$ prog1 > /tmp/file
$ prog2 < /tmp/file
$ rm /tmp/file
```

##### Exemplu
```sh
$ ls –l ~/*.c | grep "Jan 1"
```
Această comandă va afișa fișierele cu extensia `.c` care au fost modificate ultima dată în data de 1 ianuarie. Comanda este aproximativ echivalentă cu:

```sh
$ ls –l ~/*.c >tmp/file
$ grep "Jan 1" /tmp/file
$ rm /tmp/file
```

### Substituire procese
O altă funcționalitate mai puțin cunoscută este substituirea proceselor (process substitution):
```sh
$ prog1 <(prog2)
```
Această comandă va executa `prog2` și va salva fișierul standard de ieșire al acestei comenzi într-un fișier temporar, iar apoi va substitui `<(prog2)` cu numele acestui fișier temporar. Această funcționalitate este utilă atunci când comenzile așteaptă ca informațiile de intrare să fie disponibile în fișiere de pe disc, în loc de fișierul standard de intrare `stdin`.

##### Exemplu
```sh
$ paste <(wc -lw test.c | cut -d' ' -f1-3) <(ls -l test.c)
```
Această comandă va adăuga numărul de linii și cuvinte din fișierul `test.c`, ca informații adiționale în rezultatul comenzii `ls -l test.c`.

```sh
$ diff <(ls dir1) <(ls dir2)
```
Această comandă va afișa diferențele dintre fișierele din directoarele `dir1` și `dir2`.

### Substituire comenzi
În anumite situații dorim ca rezultatele scrise de o comandă în fișierul standard de ieșire să fie transferate ca argumente pentru altă comandă. Acest lucru poate fi realizat folosind substituirea comenzilor (command substitution):
```sh
$ prog1 $(prog2)
```
##### Exemplu
```sh
paste  <(seq $(wc -l test.c | cut -d' '  -f1)) test.c
```
Această comandă va afișa fișierul `test.c` având fiecare linie numerotată astfel:
- se numără liniile folosind comanda `wc`;
- se păstrează doar numărul de linii din rezultatul afișat de comanda `wc`, folosind comanda `cut`;
- se crează o secvența de numere de la `1` la numărul de linii, folosind comanda `seq`;
- folosind comanda `paste` se împerechează liniile afișate de comanda `seq` cu liniile din fișierul `test.c` specificat la sfârșitul liniei ca al doilea argument al comenzii `paste`.

Desigur această operație se poate realiza mult mai simplu folosind comanda `nl`.
```sh
nl -ba test.c
```

## Variabile de mediu în shell

### Definirea și utilizarea variabilelor
Ca și în alte limbaje de programare, în shell se pot defini variabile. Prin convenție, numele variabilelor sunt scrise cu majuscule, pentru a evita confuzia cu numele programelor executabile care sunt scrise cu minuscule. Șablonul pentru numele variabilelor este același ca în limbajul C: un identificator care începe cu o literă, și eventual urmat apoi de un șir de mai multe caractere de tipul literă, cifră sau underscore (`_`).

Principala limitare a shell-ului, care îl face nepractic pentru scrierea de programe mari, constă în faptul că există un singur tip de date, şirul de caractere, deci valorea unei variabile shell este un şir arbitrar de caractere.

Pentru definirea unei variablie se folosește instrucțiunea de atribuire:
```sh
$ VARIABILA=valoare
```

Atenție, nu se folosesc spații în stânga și dreapta caracterului `=`. O comandă care include spații, de forma: `$ VARIABILA    =  valoare` va avea semnificația de a executa un program numit `VARIABILA`, având 2 argumente: `=` și `valoare`.

Pentru a citi (folosi) valoarea unei variabile, se va prefixa numele variabilei cu caracterul `$`, de exemplu:
```sh
$ echo $VARIABILA
```

Pentru ca variabilele definite în shell pot fi accesate și de alte programe se folosește comanda `export`:
```sh
$ export VARIABILA
```

Pentru a anulare vizibilitatea variabilei din alte programe se folosește comanda:
```sh
$ export –n VARIABILA
```

##### Exemple
Comanda `env` este folosită pentru a rula o altă comandă într-un environment (mediu) modificat (vezi `man env`). Dacă o rulăm fără argumente, va afișa toate variabilele de mediu. Folosind comanda `env` putem verifica experimental modul în care sunt accesibile variabilele de mediu în programele executate de către shell și modul de funcționare al comenzii `export`.

```sh
$ V="corona virus"

$ echo $V
corona virus

$ env | grep ^V=

$ export V
$ env | grep ^V=
V=coronavirus

$ export -n V
$ env | grep ^V=

$ echo $V
corona virus
```

### Variabile importante în shell
Shell-ul însuşi foloseşte unele variabile pentru nevoile sale interne. Schimbând valoarea acestor variabile putem afecta modul său de funcționare.

Variabila internă `PWD` este directorul curent.
```sh
$ echo $PWD
```

Variabila numită `PS1` este chiar prompt-ul.
```sh
$ echo $PS1
$ PS1=Hello:
Hello:
```

Exemple de alte variabile interne:
```sh
$ echo $BASH_VERSION
$ echo $HOME
$ echo $SHELL
$ echo $USER
$ echo $RANDOM
```

### Variabila PATH

Pentru a executa o comanda, shell-ul va verifica dacă numele programului care trebuie executat este specificat ca o cale absolută sau relativă, iar în caz afirmativ, shell-ul va lansa programul executabil specificat prin calea respectivă. În caz contrar, shell-ul va încerca să identifice comanda cu una din comenzile interne care pot fi interpretate direct de către shell. Dacă nu e vorba de o comandă internă, atunci fișierul executabil este căutat într-o listă de directoare care este specificată prin variabila de mediu `PATH`, în care directoarele sunt separate prin caracterul ’:’.
```sh
 echo $PATH
```

Pentru a executa un program aflat în directorul curent, care nu se află în `PATH`, trebuie să specificăm explicit o cale către el. De aceea, folosim o comandă care specifică o cale relativă către fișierul din directorul curent:
```sh
./program
```

### Alte exemple
Experimente cu variabile de mediu și caractere speciale în shell.
```sh
$ V=corona virus
virus: command not found

#rezolvare - escape chars - similar cu limbajul C
$ V=corona\ virus

$ V="corona virus"

$ V='corona virus'

$ V=corona$virus
$ echo $V
corona
#rezolvare - escape chars
$ V=corona\$virus
```

<!--
### ENV VARS in C / Python

install ipython:
    sudo apt-get update -y
    sudo apt-get install -y ipython

os.environ
os.environ.get
os.environ['USER']

penv.c

Folosire în program C:
char* getenv(const char* name)
-->


<!--
## Valoarea returnată de aplicație
```
$ echo $?
```

Exit codes can be used to conditionally execute commands using && (and operator) and || (or operator). Commands can also be separated within the same line using a semicolon ;. The true program will always have a 0 return code and the false command will always have a 1 return code. Let’s see some examples

```sh
$ false || echo "Oops, fail"
# Oops, fail

$ true || echo "Will not be printed"
#

$ true && echo "Things went well"
# Things went well

$ false && echo "Will not be printed"
#

$ false ; echo "This will always run"
# This will always run
```
-->


## Execuția comenzilor în shell

După explicațiile oferite pentru diverse funcționalități oferite de shell pentru execuția comenzilor, putem face un foarte scurt rezumat și despre modul în care shell-ul le îndeplinește.

Pentru procesarea unei comenzi și construirea contextului de execuție shell-ul execută următoarele acțiuni:
- Împarte linia de comandă în cuvinte și detectează caracterele speciale.
- Stabilește fișierele de intrare și ieșire.
- Substituie variabilele de mediu.
- Substituie comenzile.
- Expandează numele de fișiere.

De exemplu, dacă dorim să vedem toate fișierele text (.txt) care le-am modificat în data de 1 ianuarie:
```sh
$ ls –l $HOME/*.txt | grep "Jan 1"
```

Operațiile executate de shell sunt:
- Se împarte linia în cuvinte: `ls`, `-l`, `$HOME/*.txt`, `|`, `grep`, `"Jan 1"`;
- Stabilește fișierele de intrare ieșire: recunoaște caracterul pentru redirectarea fișierelor de I/O: `|`; ieșirea `ls` devine intrarea pentru `grep`;
- Recunoaște variabila de mediu `$HOME` care desemnează directorul home al utilizatorului curent, și o înlocuiește cu valoarea ei;
- Recunoaște șabloanele pentru specificarea numelor de fișiere (`*.txt`) și le expandează într-o listă de fișiere care sunt trimise ca argumente către program;
- Se rulează cele două programe: `ls` și `grep`.


## Exemplu: comanda xargs

Comanda `xargs` este folosită pentru a executa o comandă dată folosind ca argumente textul citit din fișierul standard de intrare. Această comandă este utilă în diverse situații.

- Transferul rezultatelor unui program ca argumente pentru alt program:
    ```sh
    $ find -name "*.c" | xargs grep fopen
    ```

- Citirea argumentelor pentru un program dintr-un fișier:
    ```sh
    $ xargs ls -l <files.txt
    ```

- Execuția unui program de mai multe ori:
    ```sh
    $ seq 5 | xargs -i echo Hello!
    ```

    ```sh
    $ seq 5 | xargs -i echo Hello {}!
    ```

În continuare vom prezenta implementarea unei variante simplificate a comenzii `xargs`.

#### xargs în Python

[xargs](xargs/xargs.py ':include')

<!--
## Exemplu: comanda tee
```sh
command | tee file
```

This pattern (which includes the tee command) redirects the standard output of the command to a file and overwrites its contents. Then, it displays the redirected output in the terminal. It creates a new file if the file does not already exist.

In the context of this pattern, tee is typically used to view a program’s output while simultaneously saving it to a file.

```sh
wc /etc/magic | tee magic_count.txt
```

This pipes the counts for characters, lines, and words in the magic file (used by the Linux shell to determine file types) to the tee command, which then splits wc’s output in two directions, and sends it to the terminal display and the magic_count.txt file. For the tee command, imagine the letter T. The bottom part of the letter is the initial data, and the top part is the data being split in two different directions (standard output and the terminal).

Multiple pipes can be used to redirect output across multiple commands and/or filters.
-->


## Exemplu: MinMaxPrime
O mare parte din programele realizate în industria software primesc date de intrare generate de către alte programe, nu direct de la un utilizator. Acest fapt ajută enorm la automatizarea unor opearații complexe, astfel încât volumul de muncă depus de oameni este redus, la fel ca și probabilitatea de a introduce erori umane.

Pentru a exemplifica automatizarea operațiilor, vom considera un program care acceptă datele de intrare în mod interactiv, direct de la un utilizator, și îl vom transforma într-o formă în care datele de intrare vor putea fi ușor generate de alte programe. Apoi vom demonstra cum transferul automatizat al datelor între programe, folosind câteva din funcționalitățile oferite de shell prezentate anterior.

Problema care încercăm să o rezolvăm este: realizați un program care găsește numărul prim minim și numărul prim maxim dintr-un șir de numere naturale.

### MinMaxPrime - versiunea inițială

În versiunea inițială datele sunt citite în mod interactiv, de la tastatură (fișierul standard de intrare). Programul afișează un meniu, iar apoi utilizatorul va alege diverse opțiuni pentru a executa operațiile de citire a datelor de intrare și calculare a rezultatelor.

[minmaxprime0](minmaxprime/MinMaxPrime0.c ':include')


### MinMaxPrime - versiunea modificată
Pentru a facilita comunicarea cu alte programe (transferul automatizat al datelor), vom modifica modul de citirea a datelor de intrare. În acest sens vom renunța la partea de interactivitate cu utilizatorul. De asemenea după citirea datelor din fișierul standard de intrare, se va trece direct la calcularea și afișarea rezultatelor, fără a cere alte confirmări de la utilizator.

[minmaxprime1](minmaxprime/MinMaxPrime.c ':include')


### Utilizarea programului modificat
Vom compila programul și vom denumi fișierul executabil `mmp`.
```sh
$ gcc -Wall -o mmp MinMaxPrime.c
```

După aceste modificări, putem folosi redirectarea fișierului standard de intrare pentru a citi secvența de numere dintr-un fișier de pe disc, în loc de a citi secvența de la tastatură, de fiecare dată când vrem să testăm programul.

```sh
$ ./mmp <num.txt
```

În cazul în care datele de intrare conțin erori, acestea vor fi afișate pe ecran împreună cu rezultatele. Dacă dorim să procesăm rezultatele cu un alt program, putem folosi redirectarea fișierului standard de erori.
```sh
$ ./mmp <num.txt 2>err.txt
$ ./mmp <num.txt 2>/dev/null
```

În continuare, pentru a testa programul cu șiruri mai lungi de numere, putem folosi comanda `seq` pentru a genera un fișier cu secvența de numere.
```sh
seq 50 >num.txt
$ ./mmp <num.txt
```

De asemenea putem simplifica procesul de testare folosind două comenzi conectate folosind un pipe:
```sh
$ seq 50 | ./mmp
```

Vom folosi redirectarea cu adăugare (în loc de suprascriere), pentru a genera o secvența de numere mai complexă.
```sh
$ seq 20 30 >num.txt; seq 10 15 >>num.txt; seq 42 49 >>num.txt; seq -7 -2 >>num.txt;
$ ./mmp <num.txt
```

Această operație poate fi realizată și folosind facilitatea de substituire a proceselor:
```sh
$ cat <(seq 20 30) <(seq 10 15) <(seq 42 49) <(seq -7 -2) | ./mmp
```

Pentru a genera un set aleator de date de intrare putem folosi comanda `shuf`, care generează o permutare aleatoare a liniilor pe care le citește din fișierul standard de intrare.
```sh
$ cat <(seq 20 30) <(seq 10 15) <(seq 42 49) <(seq -7 -2) | shuf | ./mmp
```

Putem de asemenea să automatizăm complet testarea programului folosind comanda `diff`, dacă știm în avans numerele prime minim și maxim dintr-un interval.
```sh
diff <(seq 50 100 | shuf | ./mmp) <(echo 53 99) && echo "OK"
```


### Exerciții
1. Implementați programul `xargs` în limbajul `C`. Folosiți un array cu dimensiune dinamică, în care adăugarea elementelor pe ultima poziție are ordin de complexitate constant amortizat, `O(1)` (programul va realiza aceleași operații cu varianta Python).

2. Modificați programul `mmp` pentru a elimina limitarea numărului maxim de elemente procesate.

3. Încercați să optimzați performanța programului (folosiți comanda `time`).