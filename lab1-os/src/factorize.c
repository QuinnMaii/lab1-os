#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    long num;
    long repetitions;
} ThreadData;

// Function to perform prime factorization of a number
void factorize(long num) {
    for (long i = 2; i <= num / 2; i++) {
        while (num % i == 0) {
            num /= i;
        }
    }
}

void* thread_function(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (long i = 0; i < data->repetitions; i++) {
        factorize(data->num);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <number> <repetitions> <num_threads>\n", argv[0]);
        return 1;
    }

    long num = atol(argv[1]);
    long repetitions = atol(argv[2]);
    int num_threads = atoi(argv[3]);

    if (num <= 1 || repetitions <= 0 || num_threads <= 0) {
        printf("Please provide valid inputs: number (>1), positive repetitions, and positive num_threads.\n");
        return 1;
    }

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    clock_t total_start_time = clock();

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].num = num;
        thread_data[i].repetitions = repetitions / num_threads; // Divide work among threads
        pthread_create(&threads[i], NULL, thread_function, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t total_end_time = clock();
    double total_execution_time = (double)(total_end_time - total_start_time) / CLOCKS_PER_SEC;

    printf("Total execution time with %d threads: %f seconds\n", num_threads, total_execution_time);

    return 0;
}
