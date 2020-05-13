#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* str = argv[1];
    long n = strtol(str, NULL, 10);
    printf("%f\n", log2(n));
    return 0;
}
