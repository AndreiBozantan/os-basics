# API fișiere în limbajul C

## Operații cu descriptori fișiere

### fopen
```c
FILE* fopen(const char* filename, const char* mode)
```
Deschide fișierul specificat prin parametrul `filename`, pentru a efectua operațiile specificate prin parametrul `mode`. Returnează un `file descriptor` care se utilizează pentru efectuarea operațiilor de scriere și citire în fișier. În caz de eroare returnează `NULL`.


`mode`
- `"r"` - (read) se deschide fișierul pentru citire; fișierul trebuie să existe;

- `"w"` - (write) creează un fișier gol pentru scriere; dacă fișierul există conținutul lui este șters

- `"a"` - (append) - deschide fișierul pentru scriere, și îl creeaza dacă nu există; poziția curentă este setată la finalul fișierului

- `"r+"` - deschide fișierul pentru scriere și citire; fișierul trebuie să existe

- `"w+"` - creează un fișier gol pentru scriere și citire

- `"a+"` - deschide fișierul pentru citire și adăugare

### fclose
```c
int fclose(FILE* stream)
```
Închide fișierul și eliberează resursele alocate. Înainte de închidere se apelează și `fflush(stream)`.

### fflush
```c
int fflush(FILE* stream)
```
Goleșete buffer-ul de memorie asociat fișierului specificat scriind toate informațiile din acest buffer pe disk.

### freopen
```c
FILE* freopen(const char* filename,
              const char* mode,
              FILE* stream)
```

Funcția `freopen` este echivalentă cu următoarea secvență:
```c
fclose(stream)
stream = fopen(filename, mode);
return stream;
```

##### Exemplu

```c
#include <stdio.h>

int main () {
   FILE *fp;
   printf("Hello\n");
   fp = freopen("file.txt", "w+", stdout);
   printf("OS19\n");
   fclose(fp);
   return(0);
}
```


## Funcții IO mod text

### fgetc, fputc
```c
int fgetc(FILE* stream)
```
Citește următorul caracter din fișierul specificat și avanseaza poziția curentă din fișier. Returnează caracterul citit (`unsigned byte`) sau `EOF` (-1) la sfârșitul fișierului sau în caz de eroare

```c
 int fputc(int c, FILE* stream)
```
Scrie caracterul `c` în fișierul specificat și avansează poziția curentă din fișier. Returnează caracterul scris, sau `EOF` în caz de eroare.

### fgets, fputs
```c
char* fgets(char* str, int count, FILE* stream );
int fputs( const char* str, FILE* stream );
```

### getline
```c
ssize_t getline(char** lineptr, size_t* n, FILE* stream);
```

### fprintf, fscanf
```c
fprintf(FILE* stream, const char* format, ...)
```
- scrie valori în fișierul specificat în format text, folosind șablonul specificat prin parametrul `format`

```c
fscanf(FILE* stream, const char* format, ...)
```
- citește valori din fișierul specificat, folosind șablonul specificat prin parametrul `format`


## Funcții IO mod binar
```c
size_t fread(void* p, size_t s, size_t n, FILE* f)
```
Citește date din fișierul specificat și le stochează în buffer-ul `p`.

- `p` - pointer la o zonă de memorie, cu o dimensiune minimă de `s * n` bytes
- `s` - specifică dimensiunea în bytes pentru fiecare element care va fi citit
- `n` - specifică numărul de elemente care vor fi citite

- `fread` returnează numărul de elemente citite cu succes din fișier
- valoarea returnată poate fi diferită de parametrul `n`, dacă citirea a ajuns la sfârșitul fișierului sau dacă s-a produs o eroare.

```c
size_t fwrite(const void* p, size_t s, size_t n, FILE* f)
```
Scrie în fișierul specificat datele care sunt stocate în buffer-ul `p`.

- `p` - pointer la o zonă de memorie, cu o dimensiune minimă de `s * n` bytes
- `s` - dimensiunea în bytes pentru fiecare element care va fi scris în fișier
- `n` - numărul de elemente care vor fi scrise în fișier

- `fwrite` returnează numărul de elemente scrise cu succes în fișier
- valoarea returnată poate fi diferită de parametrul `n`, dacă s-a produs o eroare.


## Funcții deplasare poziție

```c
int fseek(FILE* stream, long int offset, int pos)
```
Modifică poziția curentă din fișier.

 - `offset` - numărul de bytes cu care va fi deplasată poziția curentă

 - `pos` - poate avea următoarele valori
     - `SEEK_SET` - parametrul `offset` specifică o valoare relativă la începutul fișierului
     - `SEEK_CUR` - parametrul `offset` specifică o valoare relativă la poziția curentă din fișier
     - `SEEK_END` - parametrul `offset` specifică o valoare relativă la sfârșitul fișierului

```c
long int ftell(FILE* stream)
```
Returnează poziția curentă din fișier.


## Exemple

### Exemplu: comanda cat
[cat](text/cat.c ':include')

### Exemplu: comanda wc
[wc](text/wc.c ':include')

### Exemplu: dimensiune fișier
[fsize](fsapi/fsize.c ':include')

### Exemplu: comanda cp în mod text
[cpt](fsapi/cpt.c ':include')

### Exemplu: comanda cp
Descrieți problemele din implementarea următoare programului `cp`.

[cp](fsapi/cp.c ':include')

### Exemplu: afișare detalii fișiere
Următorul program afișează dimensiunea în pixeli a imaginilor salvate în format `png`.

[lsd](lsd/lsd.c ':include')


### Exerciții
1. Pentru programul `wc` tratați și cazul când nu sunt specificate fișiere de intrare. În acest caz va fi procesat fișierul standard de intrare. Acest fapt permite combinarea programelor folosind funcționalitatea "pipe" (|) din shell. Implementați și funcționalitatea de afișare a totalurilor pentru mai multe fișiere.

2. Modificați programul `cp` astfel încât dimensiunea buffer-ului folosit să fie fixă. (Nu citiți tot fișierul în memorie).

3. Implementați comanda `nl`.

4. Implementați comanda `paste`.

5. Implementați comanda `shuf`.

6. Implementați comanda `tail` într-un mod eficient (nu stocați tot fișierul în memorie).