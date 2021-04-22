#include <stdio.h>

int isWordSep(int c) {
    if (c == '\t' || c == '\n' || c == '\r' || c == ' ' )
        return 1;
    return 0;
}

void wc(FILE* f, const char* filename) {
    int chars = 0;
    int lines = 0;
    int words = 0;
    int prevc = 0;
    do {
        // se citeste cate un caracter din fisier folosind functia
        int c = fgetc(f);
        // oprim bucla dacă am ajuns la sfârșitul fișierului
        if (c == EOF)
            break;
        // se compară caracterul citit cu '\n' și se incrementează numarul de linii
        if (c == '\n')
            lines++;
        if (isWordSep(c) && !isWordSep(prevc))
            words++;
        prevc = c;
        chars++;
    } while (1);
    // se afișează numele fișierului și numărul de linii pe ecran
    printf("%d %d %d %s\n", lines, words, chars, filename);
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        FILE* f = fopen(argv[i], "r");
        if (f == NULL) {
            fprintf(stderr, "Nu se poate deschide fisierul %s\n", argv[i]);
        } else {
            wc(f, argv[i]);
            fclose(f);
        }
    }
    return 0;
}
