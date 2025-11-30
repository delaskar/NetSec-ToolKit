#ifndef THREAD_SCANNER_H
#define THREAD_SCANNER_H

#include "scanner.h"

// Configuracion de threads
typedef struct {
    ScanConfig *config;
    ScanResults *results;
    int thread_id;
    int num_threads;
} ThreadData;

// Funciones de escaneo con threads
void run_threaded_scan(ScanConfig *config, ScanResults *results, int num_threads);

#endif
