# SISTEMUL DE FIȘIERE


## Generalități
Sistemul de fișiere UNIX are o structură arborescentă compusă din două categorii principale de obiecte: fișiere (file) și cataloage/directoare/dosare (folder/directory), având la bază un director denumit root. Directoarele reprezintă noduri interioare ale arborelui și fișierele sunt frunze ale arborelui. Toate fișierele și directoarele sunt caracterizate prin nume, care trebuie să fie unic relativ la părintele direct, literele mici și mari fiind considerate caractere distincte.

Un sistem de fișiere este stocat pe un dispozitive de stocare a datelor, de exemplu: HDD, SSD, USB stick. Un dispozitiv de stocare poate fi partiționat (împărțit) în mai multe partiții (secțiuni), astfel încât, pe fiecare partiție se va putea stoca un alt sistem de fișiere. De asemenea, mai multe dispozitive de stocare pot fi combinate într-un dispozitiv virtual pentru a stoca un singur sistem de fișiere mai mare, de exemplu folosind tehnologia RAID (în hardware). Există și tipuri de sisteme de fișiere care oferă nativ posibilitatea de a folosi mai multe dispozitive: zfs (Sun/Oracle), btrfs.

În sistemele UNIX (și Windows) există posibilitatea de a „lipi” (în engleză mount) un sistem de fișiere într-un alt sistem de fișiere.
Sistemele de operare pe bază de Unix adesea incud programe și unelte ce asistă în procesul de „lipire” (mounting) și îi furnizează noi funcționalități. Unele dintre aceste strategii au fost numite “auto-mounting” drept reprezentare a scopului lor.

Structura fișierelor nu este impusă de sistemul de operare: orice fișier este văzut ca un șir (flux) de bytes (în engleză stream) și este responsabilitatea programelor să gestioneze interpretarea corectă acestui flux. În principiu există două mari categorii de fișiere folosite în mod direct de utilizatori: fișiere text și binare. Directoarele sunt în esență tot fișiere, dar structura lor internă este cunoscută și gestionată de sistemul de operare, care le folosește pentru a realiza structura ierarhică a sistemului de fișiere.

O cale (în engleză path) este un drum între două noduri din arborele corespunzător sistemului de fișiere. În sistemul de operare și programe, calea este reprezentată printr-un text (șir de caractere), obținut prin concatenarea în ordine a numelor obiectelor din acest drum, separate prin caracterul **`/`**. Pentru a accesa informațiile dintr-un fișiere/director programele vor specifica calea în unul din formatele următoare:
- Calea absolută – calea de la directorul root până la obiectul dat. O cale absolută începe întotdeauna cu caracterul **`/`**.
- Calea relativă: se obține prin specificarea unui drum de la un director considerat ca fiind directorul curent, către obiectul dat; în calea relativă, numele **`..`** specifică directorul părinte.

Directorul curent este notat cu numele **`.`** iar directorul `home`, care este directorul curent implicit la pornirea shell-ului se notează prescurtat cu **`~`** în comenzile shell.

Extensia fișierului este partea care apare după caracterul punct, dacă acesta este prezentă.

Fișierele și directoarele care au un nume care începe cu caracterul punct sunt considerate fișiere și directoare ascunse, și de obicei ele conțin date pentru configurarea programelor, de ex. `~/.bashrc` conține informații pentru configurarea shell-ului.


## Rolul sistemului de fișiere
Principalul rol al sistemului de fișiere este de a abstractiza și standardiza procesul de acces la dispozitivele de stocare pentru utlizatori și pentru programele rulate de utilizator. De exemplu într-un program folosim aceleași funcții pentru a accesa datele de pe un HDD sau de pe un SSD, deși modul lor de funcționare este complet diferit. Dacă programele ar lucra direct cu hardware-ul, atunci când înlocuim un HDD cu un SSD, ar trebui să facem rost de actualizări la toate programele. În plus și alte dispozitive din sistem sunt abstractizate prin conceptul de fișier, de exemplu ecranul și tastatura.

Un alt rol al sistemului de fișiere este acela de a gestiona accesul simultan al mai multor aplicații la dispozitivele de stocare (virtualizare), astfel încât executarea operațiilor se face într-un mod eficient care asigură și corectitudinea rezultatelor. De exemplu, câteva din funcționalitățile oferite de anumite sisteme de fișiere sunt: detecția și corecția erorilor, criptarea datelor, arhivarea datelor, istoricul modificărilor.
De asemenea sistemul de fișiere asigură și protecția datelor între diferite aplicații și între diferiți utilizatori ai sistemului. De exemplu, un utilizator obișnuit nu poate modifica fișierele sistemului de operare, sau fișierele altui utilizator.
Sistemele de operare bazate pe Unix (Unix-like) creează un sistem de fișiere virtual, care face ca toate fișierele prezente pe toate dispozitivele de stocare să pară că există într-o singulă ierarhie. Astfel, în acele sisteme, există un singur director root și fiecare fișier ce există în sistem este localizat sub acesta. Sistemele pe bază de Unix pot folosi și un disk RAM sau resursă partajată în rețea (network shared resource) ca director root.

Avantajele ale unui sistem orientat pe fișiere (în special într-o bază de date mai mare) sunt:
1.	Posibilitatea de backup:
-	Este posibilă realizarea mai rapidă și automatizată a creării unei copii de rezervă a bazelor de date stocate într-un sistem de fișiere.
-	Sistemele informatice furnizează funcționalități ce servesc  acest scop. Este posibil dezvoltarea aplicațiilor software specifice pentru eficientizarea procesului de backup.
2.	Caracterul compact:
-	Există posibilitatea stocării în mod compact a datelor.
3.	Accesarea datelor:
-	Sistemele informatice furnizează tehnici avansate de accesare a datelor stocate în fișiere într-un mod ușor și eficient.
4.	Editarea:
-	Este ușor să edităm orice informație stocată în computere sub formă de fișiere
-	Aplicații specifice (programe de editare) pot fi folosite pentru acest scop.
5.	Accesul de la distanță:
-	În sistemele informatice este posibil să accesăm informațiile de la distanță.
-	Astfel, pentru a accesa informații nu e necesar ca un utilizator să rămână prezent la locația în care sunt păstrate fizic datele.
6.	Distribuirea:
-	Informațiile stocate în cadrul unui sistem de fișiere pot fi distribuite între multipli utilizatori în același timp.
Dezavantaje ale unui sistem orientat pe fișiere:
1.	Redundanța datelor:
-	Este posibil ca aceeași informație să fie duplicată în diferite fișiere. Acest lucru duce la redundanța datelor și rezultă irosirea memoriei de stocare.
2.	Inconsistența datelor:
-	Din cauza redundanței datelor, este posibil ca datele să nu fie consistente.
Ex: versiuni diferite ale aceluiași fișier în mai multe locuri.
3.	Dificultatea accesării datelor:
-	Accesarea datelor nu este convenabilă și eficientă în sistemul de fișiere.
Ex: trebuie parcurge multe dosare și sub-dosare
4.	Limitările distribuirii datelor:
-	Datele sunt împrăștiate în diferite fișiere. De asemenea, diferite fișiere pot avea diferite formate și pot fi stocate amestecat în dosare.
5.	Probleme de integritate a datelor:
-	Integritatea datelor se referă la faptul că informațiile din baza de date sunt și corecte și consistente. 
6.	Probleme de atomicitate:
-	Orice operație dintr-o bază de date/ sistem de fișiere trebuie să fie atomică. Astfel, aceasta trebuie să se întâmple în întregime sau deloc.
Ex: Dacă în timpul mutării unui fișier dintr-o zonă de stocare în alta apare vreo eroare sau întrerupere forțată, fișierul în cauză poate fi pierdut.
7.	Anomalii de acces simultan:
-	Multiplii utilizatori au permisiunea de a accesa simultan fișiere. Acest lucru este posibil pentru o mai bună performanță și timp de răspuns mai scurt. 
8.	Probleme de securitate:
-	Bazele de date are trebui să fie accesibile utilizatorilor într-un mod limitat.
-	Fiecare utilizator ar trebui să aibă acces strict la datele de care are nevoie. 




## Organizarea sistemului de fișiere în Linux
Pentru organizarea și denumirea primelor niveluri de directoare în sistemele de fișiere UNIX s-a adoptat o convenție, care este urmată în mod aproximativ de sistemele compatibile. Câteva din aceste directoare și fișiere standard sunt:
- `/dev` – fișiere care corespund perifericelor din calculator: ecran, tastatură, imprimante, discuri, mouse, USB; ex: `/dev/hda`, `/dev/sda`, /`dev/sda0`, `/dev/stdin`, `/dev/stdout`.
- `/bin` – conține fișiere binare executabile: principalele comenzi ale sistemului (ex. bash, ls, find)
- `/lib` – conține biblioteci (colecții de funcții) ale sistemului de operare, care pot fi folosite în alte programe
- `/etc` – fișiere pentru administrarea sistemului: informații de configurare
- `/etc/passwd` – este un fișier care conține informații despre utilizatorii sistemului: username, parola (criptată), directorul home, interpretorul de comenzi implicit
- `/var/log` – fișiere log (jurnal) ale sistemului, în care se înregistrează evenimentele petrecute în sistem; intrare/ieșire din sesiune (conectarea la sistem), erori.
- `/mnt` – punctul de montare temporară a unor sisteme de fișiere externă (ex. stick USB)
- `/opt` – conține module opționale din sistemul UNIX
- `/home` – conține directoarele home ale utilizatorilor; fiecare utilizator creat are și un director home, care este și directorul curent implicit la pornirea shellului.


## Comenzi de lucru cu sistemul de fișiere
<!-- https://tldr.ostera.io/mv -->

### pwd, cd
`$ pwd`
Afișează calea curentă (print working directory).

`$ cd [nume_director]`
Schimbă directorul curent, trecând în cel specificat. (implicit: în directorul personal (home directory) al utilizatorului). La fel ca și în DOS/Windows, `.` denotă directorul curent, iar `..` directorul părinte.
Numele `~` se referă la directorul "home" (directorul personal) al utilizatorului curent.

### ls
`$ ls [lista nume]`
Listează (afișează numele și detaliile) pentru obiectele specificate în listă; pentru directoarele specificate, se va afișa lista de fișiere și directoare care sunt descendeți direcți; în mod implicit (dacă nu este specificat niciun nume), se afișează descendenții din directorul curent.
Opțiuni:
`-l` - (long) afișează informații detaliate;
`-a` - (all) afișează și fișierele ascunse;
`-R` - procesează sub-directoarele în mod recursiv;

<!--
d (directory)
c (character device)
l (symlink)
p (named pipe)
s (socket)
b (block device)
D (door)
- (regular file) -->


### mkdir, rmdir
`$ mkdir nume_director`
Creează un director cu numele dat.

`$ rmdir nume_director`
Șterge directorul indicat (acesta trebuie să fie gol).


### cp, mv, rm
`$ cp [opțiuni] fișier1 fișier2`
Face o copie a lui `fişier1`, cu numele `fişier2`.

`cp [opțiuni] fișier1 fișier2 fișier_n dir`
Copiază fișierele indicate în directorul dir. Opțiuni:
`-i` (interactiv): întreabă înainte de a suprascrie;
`-r` (recursiv): copiază toate fișierele și subdirectoarele din directorul sursă indicat.

`$ mv [opțiuni] fișier1 fișier2`
Redenumește `fişier1`, ca `fişier2`.

`$ mv [opțiuni] fișier1 fișier2 fișier_n dir`
Mută fișierele indicate în directorul `dir`. Opțiuni:
`-i` (interactiv): întreabă înainte de a suprascrie. (Un catalog e mutat implicit împreună cu întreg conținutul, deci opțiunea `-r` nu mai apare, spre deosebire de copiere).

`$ rm [opțiuni] nume_fișier`
Șterge fișierul specificat. Opțiuni:
`-i` (interactiv) solicită confirmare;
`-f` forțează (fără confirmare);
`-r` șterge recursiv tot conținutul directorului indicat.

### find
`$ find director [opțiuni] [condiţie]`
Se caută în directoarele date și în subdirectoarele lor fișierele care satisfac condiție.
Exemplu:
`$ find / –name "*tmp*"` afișează toate fișierele care conțin `tmp` în nume în directorul root.

### du, df
`$ du [opțiuni] [fișier]`
Afișează dimensiunea unui fișier sau director. Fără argumente rulează recursiv peste directorul curent. Opțiuni:
`-s` suma dimensiunilor pentru argumentele date;
`-h` human readable

`$ df [opțiuni]`
Afișează spațiul liber și folosit pentru fiecare sistem de fișiere montat.

### Diverse
`touch [fișier...]`
Modifică data ultimei modificări pentru fișierele specificate, sau crează fișierele, dacă acestea nu există.

`$ od [opțiuni] fișier`
Afișează conținutul fișierului în diferite formate: octal, hexa, …


## Comenzi pentru procesarea fișierelor text

În UNIX există numeroase comenzi pentru prelucrarea fișierelor text, ceea ce este ușor de explicat prin modul în care a decurs dezvoltarea sistemului de operare în primii ani: o parte din fondurile obținute pentru dezvoltarea sistemului s-au justificat prin includerea de facilități pentru prelucrarea unor informații sub formă de text (biblioteca de brevete a companiei). Pe de altă parte sistemul a fost considerat întotdeauna și ca un sistem de dezvoltare de programe, unde procesarea textelor este importantă. În plus, înaintea apariției interfețelor grafice, toată comunicarea dintre om și calculator era în mod text.

<!-- https://tldr.ostera.io/ -->

### cat
`$ cat [filename...]`
Afișează conținutul fișierelor specificate.

### head
Programul head afișează primele linii dintr-un fișier (antetul):
`$ head [-n] [filename...]`
În absența unor nume de fișiere, fișierul standard de intrare este copiat în fișierul standard (ce scriem de la tastatură este afișat pe ecran). Opțiunea –n, unde n este un număr întreg precizează numărul de linii afișate (valoarea implicită este 10).

### tail
Programul tail (sfârșit, coadă) afișează ultima porțiune dintr-un fișier:
`$ tail [optiuni] [filename...].`
Opțiuni:
- -n – afișează ultimele n linii din fișier (valoarea
implicită este 10)
- -c numără caractere în loc de linii
- -f se repetă operațiunea de citire până la întreruperea
programului.

<!--
### more
-->

<!--
### less
-->

### wc
`$ wc –[lwc] [filename...]`
Programul `wc` (word count) determină numărul de linii, cuvinte și caractere dintr-un fișier. În absența numelor de fișiere se consideră implicit fișierul standard de intrare. Se consideră un cuvânt un șir de caractere delimitat de spațiu, tab sau newline. Prin opțiuni se specifică dacă se dorește numărul de linii (l), cuvinte (w) sau caractere (c). Dacă sunt folosite mai multe fișiere se afișează și un total.

<!-- `$ find -name *.c | wc -l` -->

### grep
`$ grep [optiuni] sablon_text [filename...]`
Este un program utilizat pentru căutarea în fișiere text, a porțiunilor care corespund cu un șablon furnizat, care poate să fie și o expresie regulată.
```
$ grep pop /etc/passwd
$ grep s67 orar.txt
```

### sort
Sortează un fișier text. Fișierul este împărțit în coloane după prin separatorul specificat (-t, sau implicit caracterele blanc). Sunt specificate apoi coloanele care vor fi sortate.

<!--
### shuf
-->

<!--
### cut
-->

<!--
### paste
-->

<!--
### nl
- number lines
-->

<!--
### tr
-->

<!--
### SED
Stream editor – este de obicei folosit pentru a înlocui o
porțiune de text dintr-o linie cu un alt text:
`sed s/Unix/UNIX/g f1`
-->


<!-- https://missing.csail.mit.edu/2020/data-wrangling/ -->


## Drepturi de acces
Protecția accesului la fișiere într-un sistem cu mai mulți utilizatori este un aspect important. În Unix, sistemul de fișiere conține ca informații adiționale asociate fiecărui fișier și director un identificator utilizator și un identificator de grup al proprietarului. Fiecare utilizator primește un număr specific, numit număr de identificare (ID). În momentul în care este creat un fișier el este asociat cu ID-ul utilizatorului care l-a creat. Fiecare conține în i-node-ul asociat trei seturi de câte trei biți. Seturile corespund proprietarului, grupului din care face parte proprietarul (grupul) și celorlalți utilizatori din sistem (alții). Pentru fiecare dintre aceștia există dreptul de citire (Read), de scriere (Write) și de execuție (Execute). Dreptul precizează unui proces operațiile (citire, scriere, execuție) pe care acesta le poate efectua asupra unui fișier. Pentru fișiere obișnuite semnificația drepturilor este evidentă. Pentru directoare dreptul de citire înseamnă drept de consultare (de afișare) a directorului (este permisă comanda ls). Dreptul de scriere înseamnă că în acest director se pot crea noi fișiere, șterge fișiere, se poate monta un sistem de fișiere se pot adaugă sau șterge legături.

<!-- This gives us a bunch more information about each file or directory present. First, the d at the beginning of the line tells us that missing is a directory. Then follow three groups of three characters (rwx). These indicate what permissions the owner of the file (missing), the owning group (users), and everyone else respectively have on the relevant item. A - indicates that the given principal does not have the given permission. Above, only the owner is allowed to modify (w) the missing directory (i.e., add/remove files in it). To enter a directory, a user must have “search” (represented by “execute”: x) permissions on that directory (and its parents). To list its contents, a user must have read (r) permissions on that directory. For files, the permissions are as you would expect. Notice that nearly all the files in /bin have the x permission set for the last group, “everyone else”, so that anyone can execute those programs. -->

Comanda `chmod atr [fișier]...` modifică drepturile de acces pentru fișierele și/sau directoarele specificate. Argumentul `atr` va conține o combinație de forma: `[u|g|o]   [+|-|=]   [r|w|x|s|t]`, unde elementele indeividuale au semnificația explicată în continuare.

Categorie utilizator:
- `u` – proprietarul (user)
- `g` – grupul (group)
- `o` - restul utilizatorilor (others)
- `a` - u+g+o

Tipul operației:
- `+` adaugă permisiune
- `-` șterge permisiune
- `=` atribuie permisiune exactă

Permisiuni:
- `r` – Read
- `w` – Write
- `x` - eXecute

<!-- chown -->

## Exemplu sisteme de fișiere

1. Creare virtual hard drive (file container) - sparse file
```bash
$ truncate --size 100M virtual-disk.img
$ ls -alh
$ du virtual-disk.img
```

2. Creare sistem de fișiere
```bash
$ mkfs --type ext4 d.img
$ ls -alh
$ du virtual-disk.img
```

3. Creare director pentru montare file-system
```bash
$ mkdir ~/vhd
```

4. Montare sistem de fișiere
```bash
$ sudo mount -t auto -o loop virtual-disk.img ~/vhd/
```

5. Demontare sistem de fișiere
```bash
sudo umount ~/vhd
```