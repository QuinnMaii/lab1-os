#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    long repetitions;
} ThreadData;

// Hàm thực hiện công việc tính toán
void *ema_search_int(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    long sum = 0;
    for (long i = 0; i < data->repetitions; i++) {
        sum += i;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <repetitions> <num_threads>\n", argv[0]);
        return 1;
    }

    long repetitions = atol(argv[1]);
    int num_threads = atoi(argv[2]);

    pthread_t threads[num_threads];
    ThreadData data[num_threads];

    clock_t start_time = clock();

    // Tạo và chạy các luồng
    for (int i = 0; i < num_threads; i++) {
        data[i].repetitions = repetitions;
        pthread_create(&threads[i], NULL, ema_search_int, &data[i]);
    }

    // Chờ tất cả luồng hoàn thành
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time with %d threads: %f seconds\n", num_threads, execution_time);

    return 0;
}
