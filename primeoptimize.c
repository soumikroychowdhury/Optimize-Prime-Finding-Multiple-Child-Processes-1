#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    if (num <= 3) return 1;
    if (num % 2 == 0 || num % 3 == 0) return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

void find_primes(int start, int end) {
    for (int num = start; num <= end; num++) {
        if (is_prime(num)) {
            printf("%d is prime\n", num);
        }
    }
}

int main() {
    int N, M;
    printf("Enter the value of N: ");
    scanf("%d", &N);
    printf("Enter the number of child processes (M): ");
    scanf("%d", &M);

    int end, range_per_process = N / M, start = 1;
    for (int i = 0; i < M; i++) {
        end = (i == M - 1) ? N : start + range_per_process - 1;
        pid_t pid = fork();
        if (pid == -1) {
            perror("Fork error");
            exit(1);
        }
        else if (pid == 0) { // Child process
            find_primes(start, end);
            exit(0);
        }
        else { // Parent process
            start = end + 1;
        }
    }
    
    for (int i = 0; i < M; i++) {
        wait(NULL); // Wait for all child processes to finish
    }
    return 0;
}