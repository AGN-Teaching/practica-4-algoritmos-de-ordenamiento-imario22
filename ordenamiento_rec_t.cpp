
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include "ordenamiento_t.h"
#include "ordenamiento_rec_t.h"

using namespace std;
using namespace std::chrono;
// Prototipo de la función
bool incluirAlgoritmo(string listaAlgs, char alg);

// Resto del código...

// Luego, la implementación de la función incluirAlgoritmo puede permanecer sin cambios.
bool incluirAlgoritmo(string listaAlgs, char alg)
{
    size_t incluir = listaAlgs.find(alg);
    return incluir != string::npos;
}


duration<double> crear_arreglo(int *A, int TAM_ARREGLO, int RANGO_MAX) {
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    for (int i = 0; i < TAM_ARREGLO; i++) {
        int x = rand() % RANGO_MAX;
        A[i] = x;
    }
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_insertion_sort(int *A, int TAM_ARREGLO) {
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    insertion_sort(A, TAM_ARREGLO);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_selection_sort(int *A, int TAM_ARREGLO) {
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    selection_sort(A, TAM_ARREGLO);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_bubblesort(int *A, int TAM_ARREGLO) {
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    bubblesort(A, TAM_ARREGLO);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_merge_sort(int *A, int TAM_ARREGLO) {
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    merge_sort(A, 0, TAM_ARREGLO - 1);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_quicksort(int *A, int TAM_ARREGLO) {
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    quicksort(A, 0, TAM_ARREGLO - 1);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

duration<double> ordenar_merge_sort_is(int *A, int TAM_ARREGLO, int k) {
    high_resolution_clock::time_point inicio = high_resolution_clock::now();
    merge_sort_is(A, 0, TAM_ARREGLO - 1, k);
    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> tiempo = duration_cast<duration<double>>(fin - inicio);
    return tiempo;
}

int *copiar_arreglo(int A[], int n) {
    int *aux = new int[n];
    for (int i = 0; i < n; i++) {
        aux[i] = A[i];
    }
    return aux;
}

void calcular_desviacion_estandar(double *tiempos, int repeticiones, double &desviacion) {
    double promedio = 0.0;
    for (int i = 0; i < repeticiones; i++) {
        promedio += tiempos[i];
    }
    promedio /= repeticiones;

    desviacion = 0.0;
    for (int i = 0; i < repeticiones; i++) {
        desviacion += pow(tiempos[i] - promedio, 2);
    }
    desviacion = sqrt(desviacion / repeticiones);
}

void experimentos(int tam, int reps, bool ms, bool qs, bool mis, bool buble, bool insertion, bool selection) {
    int TAM_ARREGLO = tam;
    int RANGO_MAX = 10 * TAM_ARREGLO;
    int REPETICIONES = reps;
    double t_prom_ms = 0.0;
    double t_prom_qs = 0.0;
    double t_prom_mis = 0.0;
    double t_prom_buble = 0.0;
    double t_prom_insertion = 0.0;
    double t_prom_selection = 0.0;

    srand((unsigned)time(0));
    for (int i = 0; i < REPETICIONES; i++) {
        cout << "*** REPETICION " << i + 1 << " ***" << endl;
        int *A = new int[TAM_ARREGLO];
        duration<double> tiempo;

        // Arreglo aleatorio
        cout << "Creando arreglo aleatorio de tamanio " << TAM_ARREGLO << "... " << flush;
        tiempo = crear_arreglo(A, TAM_ARREGLO, RANGO_MAX);
        cout << "\tCreado. ";
        cout << "\tTiempo: " << tiempo.count() << "s" << endl;

        int *aux;
        if (ms)
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            cout << "Iniciando ordenamiento con MERGE SORT... " << flush;
            tiempo = ordenar_merge_sort(aux, TAM_ARREGLO);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo.count() << "s" << endl;
            t_prom_ms = t_prom_ms + tiempo.count();
            delete[] aux;
        }

        if (qs)
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            cout << "Iniciando ordenamiento con QUICKSORT... " << flush;
            tiempo = ordenar_quicksort(aux, TAM_ARREGLO);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo.count() << "s" << endl;
            t_prom_qs = t_prom_qs + tiempo.count();
            delete[] aux;
        }

        if (mis)
        {
            int k;
            cout << "Ingrese el valor de k para merge_sort_is: ";
            cin >> k;

            aux = copiar_arreglo(A, TAM_ARREGLO);
            cout << "Iniciando ordenamiento con MERGESORT CON INSERTION SORT... " << flush;
            tiempo = ordenar_merge_sort_is(aux, TAM_ARREGLO, k);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo.count() << "s" << endl;
            t_prom_mis = t_prom_mis + tiempo.count();
            delete[] aux;
        }
        if (buble)
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            cout << "Iniciando ordenamiento con bubblesort... " << flush;
            tiempo = ordenar_bubblesort(aux, TAM_ARREGLO);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo.count() << "s" << endl;
            t_prom_buble = t_prom_buble + tiempo.count();
            delete[] aux;
        }
        if (insertion)
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            cout << "Iniciando ordenamiento con insertion short... " << flush;
            tiempo = ordenar_insertion_sort(aux, TAM_ARREGLO);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo.count() << "s" << endl;
            t_prom_insertion = t_prom_insertion + tiempo.count();
            delete[] aux;
        }
        if (selection)
        {
            aux = copiar_arreglo(A, TAM_ARREGLO);
            cout << "Iniciando ordenamiento con selection short... " << flush;
            tiempo = ordenar_selection_sort(aux, TAM_ARREGLO);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo.count() << "s" << endl;
            t_prom_selection = t_prom_selection + tiempo.count();
            delete[] aux;
        }

        delete[] A;
        cout << endl;
    }
    t_prom_ms = t_prom_ms / REPETICIONES;
    t_prom_qs = t_prom_qs / REPETICIONES;
    t_prom_mis = t_prom_mis / REPETICIONES;
    t_prom_buble = t_prom_buble / REPETICIONES;
    t_prom_insertion = t_prom_insertion / REPETICIONES;
    t_prom_selection = t_prom_selection / REPETICIONES;

    cout << "*** TIEMPO PROMEDIO ***" << endl;
    if (ms)
    {
        cout << "Merge sort:\t" << t_prom_ms << endl;
    }
    if (qs)
    {
        cout << "Quicksort:\t" << t_prom_qs << endl;
    }
    if (mis)
    {
        cout << "Merge sort con insertion sort:\t" << t_prom_mis << endl;
    }
    if (buble)
    {
        cout << "Bubblesort:\t" << t_prom_buble << endl;
    }
    if (insertion)
    {
        cout << "Insertion sort:\t" << t_prom_insertion << endl;
    }
    if (selection)
    {
        cout << "Selection sort:\t" << t_prom_selection << endl;
    }

    // Arrays para almacenar los tiempos de cada algoritmo
    double *tiempos_ms = new double[REPETICIONES];
    double *tiempos_qs = new double[REPETICIONES];
    double *tiempos_mis = new double[REPETICIONES];
    double *tiempos_buble = new double[REPETICIONES];
    double *tiempos_insertion = new double[REPETICIONES];
    double *tiempos_selection = new double[REPETICIONES];

    for (int i = 0; i < REPETICIONES; i++)
    {
        int *A = new int[TAM_ARREGLO];
        duration<double> tiempo;

        // Arreglo aleatorio
        crear_arreglo(A, TAM_ARREGLO, RANGO_MAX);

        int *aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_merge_sort(aux, TAM_ARREGLO);
        tiempos_ms[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_quicksort(aux, TAM_ARREGLO);
        tiempos_qs[i] = tiempo.count();
        delete[] aux;

        int k;
        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_merge_sort_is(aux, TAM_ARREGLO, k);
        tiempos_mis[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_bubblesort(aux, TAM_ARREGLO);
        tiempos_buble[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_insertion_sort(aux, TAM_ARREGLO);
        tiempos_insertion[i] = tiempo.count();
        delete[] aux;

        aux = copiar_arreglo(A, TAM_ARREGLO);
        tiempo = ordenar_selection_sort(aux, TAM_ARREGLO);
        tiempos_selection[i] = tiempo.count();
        delete[] aux;

        delete[] A;
    }

    // Calcular desviación estándar
    double desviacion_ms, desviacion_qs, desviacion_mis, desviacion_buble, desviacion_insertion, desviacion_selection;

    calcular_desviacion_estandar(tiempos_ms, REPETICIONES, desviacion_ms);
    calcular_desviacion_estandar(tiempos_qs, REPETICIONES, desviacion_qs);
    calcular_desviacion_estandar(tiempos_mis, REPETICIONES, desviacion_mis);
    calcular_desviacion_estandar(tiempos_buble, REPETICIONES, desviacion_buble);
    calcular_desviacion_estandar(tiempos_insertion, REPETICIONES, desviacion_insertion);
    calcular_desviacion_estandar(tiempos_selection, REPETICIONES, desviacion_selection);

    // Mostrar resultados
    cout << "\n*** Desviación Estándar ***" << endl;
    if (ms)
    {
        cout << "Merge sort:\t" << desviacion_ms << endl;
    }
    if (qs)
    {
        cout << "Quicksort:\t" << desviacion_qs << endl;
    }
    if (mis)
    {
        cout << "Merge sort con insertion sort:\t" << desviacion_mis << endl;
    }
    if (buble)
    {
        cout << "Bubblesort:\t" << desviacion_buble << endl;
    }
    if (insertion)
    {
        cout << "Insertion sort:\t" << desviacion_insertion << endl;
    }
    if (selection)
    {
        cout << "Selection sort:\t" << desviacion_selection << endl;
    }

    // Liberar memoria
    delete[] tiempos_ms;
    delete[] tiempos_qs;
    delete[] tiempos_mis;
    delete[] tiempos_buble;
    delete[] tiempos_insertion;
    delete[] tiempos_selection;
}


int main()
{
    int TAM_ARREGLO, REPETICIONES;
    string listaAlgoritmos;

    cout << "Ingrese el tamanio del arreglo: ";
    cin >> TAM_ARREGLO;

    cout << "Ingrese el numero de repeticiones: ";
    cin >> REPETICIONES;

    cout << "Ingrese la lista de algoritmos (m para Merge Sort, q para Quicksort, i para Merge Sort con Insertion Sort, b para bubblesort, n insertion short, s para selection sort): ";
    cin >> listaAlgoritmos;

    bool ms = incluirAlgoritmo(listaAlgoritmos, 'm');
    bool qs = incluirAlgoritmo(listaAlgoritmos, 'q');
    bool mis = incluirAlgoritmo(listaAlgoritmos, 'i');
    bool buble = incluirAlgoritmo(listaAlgoritmos, 'b');
    bool insertion = incluirAlgoritmo(listaAlgoritmos, 'n');
    bool selection = incluirAlgoritmo(listaAlgoritmos, 's');

    // Redirigir la salida a un archivo
    ofstream archivoSalida("resultados.txt");
    streambuf *salidaOriginal = cout.rdbuf(); // Guardar el puntero al flujo de salida original
    cout.rdbuf(archivoSalida.rdbuf());         // Redirigir la salida al archivo

    experimentos(TAM_ARREGLO, REPETICIONES, ms, qs, mis, buble, insertion, selection);

    // Restaurar la salida original
    cout.rdbuf(salidaOriginal);

    return EXIT_SUCCESS;
}
