#include <stdbool.h>
#include <stdio.h>

bool isPrime(int n) {
    if (n < 2 || n % 2 == 0) {
        return false;
    }
    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }
    return true;
}

int minPrime(int count, int seq[]) {
    int num_primes = 0;
    int min = seq[0];
    for (int i = 0; i < count; i++) {
        if (!isPrime(seq[i]))
            continue;
        if (num_primes == 0 || seq[i] < min) {
            min = seq[i];
            num_primes++;
        }
    }
    return (num_primes == 0) ? -1 : min;
}

int maxPrime(int count, int seq[]) {
    int num_primes = 0;
    int max = seq[0];
    for (int i = 0; i < count; i++) {
        if (!isPrime(seq[i]))
            continue;
        if (num_primes == 0 || seq[i] > max) {
            max = seq[i];
            num_primes++;
        }
    }
    return (num_primes == 0) ? -1 : max;
}

int main(int argc, char* argv[]) {
    int MAX = 1000;
    int seq[MAX];
    int count = 0;
    int num = 0;
    while (true) {
        int ret = scanf("%d", &num);
        if (ret == EOF) {
            break;
        }
        if (ret != 1 || num <= 0) {
            fprintf(stderr, "Invalid number %d\n", num);
        }
        else {
            seq[count] = num;
            count++;
        }
        if (count == MAX) {
            fprintf(stderr, "Can not process more than %d numbers\n", MAX);
            break;
        }
    }
    int min = minPrime(count, seq);
    int max = maxPrime(count, seq);
    fprintf(stdout, "%d %d\n", min, max);
}