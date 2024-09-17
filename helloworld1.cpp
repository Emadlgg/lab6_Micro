#include <iostream>
#include <pthread.h>

void* printHello(void* arg) {
    int thread_id = *((int*)arg);
    std::cout << "Hello world thread No. " << thread_id << std::endl;
    pthread_exit(nullptr);
}

int main() {
    int num_threads = 8; 
    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], nullptr, printHello, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], nullptr);
    }

    return 0;
}
