#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    size_t result;

    // se procesează doar primul fișier
    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        fputs("Input file open error", stderr);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);

    fseek(f, 0, SEEK_SET);
    char* buffer = (char*)malloc(sizeof(char) * size);

    if (buffer == NULL) {
        fputs("Memory error", stderr);
        exit(2);
    }

    size_t nread = fread(buffer, 1, size, f);
    if (nread != size) {
        free(buffer);
        fputs("Reading error", stderr);
        exit(3);
    }

    puts(buffer);

    free(buffer);
    fclose(f);
    return 0;
}
