#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* envp[]) {
    const char* v = getenv("v");

    // v0
    printf("%s\n", getenv("v"));

    // v1
    printf("%s\n", v == NULL ? "NULL" : v);

    // v2 - use envp parameter
    for (int i = 0; envp[i] != NULL; i++) {
        printf("%s\n", envp[i]);
    }
}