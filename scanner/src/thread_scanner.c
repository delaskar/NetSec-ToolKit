#include "../include/banner.h"
#include "../include/thread_scanner.h"
#include "../include/output.h"
#include "../include/scanner.h"
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// Mutex para sincronizar acceso a resultados y output
pthread_mutex_t result_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t output_mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_scan_worker(void *arg) {
    ThreadData *data = (ThreadData *)arg;

    // Cada thread escanea puertos con patrón: thread_id, thread_id+num,...
    for (int port = data->config->start_port + data->thread_id;
        port <= data->config->end_port;
        port += data->num_threads) {

            // Escanear el puerto
            int result = scan_port(&data->config->target_addr, port);  // ← CORREGIDO

            // Determinar el estado
            const char *status;
            if (result == 0) {
                status = "OPEN";
                pthread_mutex_lock(&result_mutex);
                data->results->open_ports++;
                pthread_mutex_unlock(&result_mutex);

                // Imprimir OPEN + banner (atómicamente)
                pthread_mutex_lock(&output_mutex);
                print_port_result(port, status, data->config->mode);
                if (data->config->enable_banner) {
                    BannerInfo banner_info;
                    if (grab_banner(data->config->target_ip, port, &banner_info) == 0) {
                        identify_service(&banner_info);
                        print_banner_info(&banner_info);
                    }
                }
                pthread_mutex_unlock(&output_mutex);
            }
            else if (errno == ECONNREFUSED) {
                status = "CLOSED";
                pthread_mutex_lock(&result_mutex);
                data->results->closed_ports++;
                pthread_mutex_unlock(&result_mutex);

                // Imprimir CLOSED
                pthread_mutex_lock(&output_mutex);
                print_port_result(port, status, data->config->mode);
                pthread_mutex_unlock(&output_mutex);
            }
            else if (errno == ETIMEDOUT) {
                status = "FILTERED";
                pthread_mutex_lock(&result_mutex);
                data->results->filtered_ports++;
                pthread_mutex_unlock(&result_mutex);

                // Imprimir FILTERED
                pthread_mutex_lock(&output_mutex);
                print_port_result(port, status, data->config->mode);
                pthread_mutex_unlock(&output_mutex);
            }
            else {
                // Otro error, contar como cerrado
                status = "CLOSED";
                pthread_mutex_lock(&result_mutex);
                data->results->closed_ports++;
                pthread_mutex_unlock(&result_mutex);

                // Imprimir CLOSED
                pthread_mutex_lock(&output_mutex);
                print_port_result(port, status, data->config->mode);
                pthread_mutex_unlock(&output_mutex);
            }

            // Incrementar total
            pthread_mutex_lock(&result_mutex);
            data->results->total_ports++;
            pthread_mutex_unlock(&result_mutex);
        }

    return NULL;
}

// Función principal que crea y maneja los threads
void run_threaded_scan(ScanConfig *config, ScanResults *results, int num_threads) {
    // Inicializar contadores
    results->total_ports = 0;
    results->open_ports = 0;
    results->closed_ports = 0;
    results->filtered_ports = 0;

    // Crear arrays para threads y sus datos
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    // Crear threads
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].config = config;
        thread_data[i].results = results;
        thread_data[i].thread_id = i;
        thread_data[i].num_threads = num_threads;

        if (pthread_create(&threads[i], NULL, thread_scan_worker, &thread_data[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return;
        }
    }

    // Esperar a que todos los threads terminen
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}
