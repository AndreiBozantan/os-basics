#include <stdio.h>

// O implementare simplă a comenzii cat
int main(int argc, char* argv[]) {
    // se procesează toate fișierele primite ca argumente
    for (int i = 1; i < argc; i++) {
        FILE* f = fopen(argv[i], "r");
        if (f != NULL) {
            do {
                int c = fgetc(f);
                if (c == EOF)
                    break;
                printf("%c", c);
            } while (1);
        }
        fclose(f);
    }
    return 0;
}
