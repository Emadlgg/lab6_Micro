#include <iostream>
#include <pthread.h>
#include <vector>
#include <cmath>

struct ThreadData {
    int start;
    int end;
    long long sum;
};

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void* findPrimes(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    data->sum = 0;
    for (int i = data->start; i <= data->end; i++) {
        if (isPrime(i)) {
            data->sum += i;
        }
    }
    pthread_exit(nullptr);
}

int main() {
    int max_value, num_threads;
    std::cout << "Ingrese el valor maximo: ";
    std::cin >> max_value;
    std::cout << "Ingrese la cantidad de hilos: ";
    std::cin >> num_threads;

    std::vector<pthread_t> threads(num_threads);
    std::vector<ThreadData> thread_data(num_threads);

    int range = max_value / num_threads;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start = i * range;
        thread_data[i].end = (i == num_threads - 1) ? max_value : (i + 1) * range - 1;
        pthread_create(&threads[i], nullptr, findPrimes, (void*)&thread_data[i]);
    }

    long long total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], nullptr);
        total_sum += thread_data[i].sum;
    }

    std::cout << "La suma total de los numeros primos es: " << total_sum << std::endl;

    return 0;
}
