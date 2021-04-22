#include <stdio.h>

// Acest program afișează dimensiunea în bytes
// a fișierelor specificate ca argumente în linia de comandă
int main(int argc, const char* argv[]) {
    for (int i = 1; i < argc; i++) {
        FILE* fin = fopen(argv[i], "r");
        if (fin == NULL) {
            fprintf(stderr, "eroare la deschiderea fisierului de intrare\n");
            return -1;
        }
        fseek(fin, 0, SEEK_END);
        long int len = ftell(fin);
        printf("%s %ld\n", argv[i], len);
        fclose(fin);
    }
}
