#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

// Estructura para pasar los argumentos a cada hilo
struct ThreadData {
    int n;  // Valor de 'n' para este hilo
    double result;  // Resultado de la serie para este valor de 'n'
};

// Función que calcula el término de la serie geométrica
void* calculateTerm(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int n = data->n;

    // Calculo del término de la serie: 3/(2^n)
    data->result = 3.0 / (1 << n);  // 1 << n es equivalente a 2^n

    pthread_exit(nullptr);
}

int main() {
    int max_n;
    
    // Solicitar al usuario el valor máximo de n
    cout << "Ingrese el valor maximo de n: ";
    cin >> max_n;

    // Crear un array de hilos y estructuras para los datos
    vector<pthread_t> threads(max_n + 1);
    vector<ThreadData> threadData(max_n + 1);

    // Crear y lanzar un hilo por cada valor de n
    for (int i = 0; i <= max_n; ++i) {
        threadData[i].n = i;
        pthread_create(&threads[i], nullptr, calculateTerm, &threadData[i]);
    }

    // Sumar los resultados en el hilo principal
    double totalSum = 0.0;
    for (int i = 0; i <= max_n; ++i) {
        pthread_join(threads[i], nullptr);  // Esperar a que el hilo termine
        totalSum += threadData[i].result;   // Sumar el resultado de la serie
    }

    // Imprimir el resultado final
    cout << "La suma de la serie geometrica es: " << totalSum << endl;

    return 0;
}
