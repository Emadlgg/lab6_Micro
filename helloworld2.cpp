#include <iostream>
#include <pthread.h>

void* printHello(void* arg) {
    int thread_id = *((int*)arg);
    std::cout << "Hello world thread No. " << thread_id << std::endl;
    pthread_exit(nullptr);
}

int main() {
    int num_threads = 8; 
    pthread_t thread;
    int thread_id;

    for (int i = 0; i < num_threads; i++) {
        thread_id = i;
        pthread_create(&thread, nullptr, printHello, (void*)&thread_id);
        pthread_join(thread, nullptr);
    }

    return 0;
}
