#include <stdbool.h>
#include <stdio.h>

bool isPrime(int n) {
    if (n < 2) 
        return false;
    int d = 2;
    while (d * d <= n && n % d != 0) {
        if (d == 2)
            d = 3;
        else
            d += 2;
    }
    if (d * d > n) 
        return true;
    return false;
}


int minPrime(int len, int seq[]) {
    int i = 0;
    while (i < len && !isPrime(seq[i])) 
        i++;
    if (i > len)
        return -1;
    int m = seq[i];
    for (int j = i + 1; j < len; j++) {
        if (isPrime(seq[j]) && seq[j] < m) {
            m = seq[j];
        }
    }
    return m;
}

int maxPrime(int len, int seq[]) {
    int i = 0;
    while (i < len && !isPrime(seq[i])) 
        i++;
    if (i > len)
        return -1;
    int m = seq[i];
    for (int j = i + 1; j < len; j++) {
        if (isPrime(seq[j]) && seq[j] > m) {
            m = seq[j];
        }
    }
    return m;
}

int readNum(char* msg) {
    int n;
    printf("%s", msg);
    int r = scanf("%d", &n);
    if (n < 0 || r != 1) {
        printf("Ai gresit, scrie un număr natural.\n");
        return readNum(msg);
    }
    return n;
}

int showMenu() {
    printf("1.Citire secventa\n");
    printf("2.Determinare cel mai mic  numar prim din secventa\n");
    printf("3.Determinare cel mai mare numar prim din secventa\n");
    printf("0.Terminare program\n");
    int opt = readNum("Optiunea ta: ");
    return opt;
}

int main(int argc, char* argv[]) {
    int seq[100];
    int num = 0;
    int len = 0;
    int min = 0;
    int max = 0;
    while (true) {
        int opt = showMenu();
        switch (opt) {
            case 0:
                printf("Terminare program\n");
                return 0;
            case 1:
                len = 0;
                do {
                    num = readNum("Introdu un numar din secventa (la 0=terminare): ");
                    if (num > 0) {
                        seq[len] = num;
                        len++;
                    }
                } while (num > 0);
                break;
            case 2:
                min = minPrime(len, seq);
                if (min > 0)
                    printf("cel mai mic numar prim este %d\n", min);
                else
                    printf("nu există prime in secventa\n");
                break;
            case 3:
                max = maxPrime(len, seq);
                if (max > 0)
                    printf("cel mai mare numar prim este %d\n", max);
                else
                    printf("nu există prime in secventa\n");
                break;
            default:
                printf("Ai gresit optiunea\n");
        }
    }
}