#include "../include/scanner.h"
#include "../include/thread_scanner.h"
#include "../include/validation.h"
#include "../include/output.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int num_threads = 1;  // Por defecto, modo secuencial
    int enable_banner = 0;
    int arg_offset = 0;

    // Verificar si se especificó opción -t
    if (argc >= 3 && strcmp(argv[1], "-t") == 0) {
        num_threads = string_to_int(argv[2]);

        if (num_threads < 1 || num_threads > 100) {
            fprintf(stderr, "Error: Number of threads must be between 1 and 100\n");
            return 1;
        }

        arg_offset = 2;  // Saltar los argumentos -t <num>
    }

    // Verificar si se especifico la opcion -b
    if (argc >= 2 && strcmp(argv[1 + arg_offset], "-b") == 0) {
        enable_banner = 1;
        arg_offset++;   // Saltar el argumento -b
    }

    // Validar número de argumentos
    if (argc - arg_offset != 5) {
        fprintf(stderr, "Usage: %s [-t <threads>] <MODE> <Target_IP> <Start_Port> <End_Port>\n", argv[0]);
        fprintf(stderr, "Modes: open, closed, filtered, all\n");
        fprintf(stderr, "Example: %s open 127.0.0.1 1 1000\n", argv[0]);
        fprintf(stderr, "Example: %s -t 10 open 127.0.0.1 1 1000\n", argv[0]);
        return 1;
    }

    // Convertir y validar modo
    ScanMode mode = string_to_mode(argv[1 + arg_offset]);
    if (mode == INVALID_MODE) {
        fprintf(stderr, "Error: Invalid mode '%s'\n", argv[1 + arg_offset]);
        fprintf(stderr, "Valid modes: open, closed, filtered, all\n");
        return 1;
    }

    // Obtener y validar IP
    char *target_ip = argv[2 + arg_offset];
    if (validate_ip(target_ip) != 0) {
        return 1;
    }

    // Convertir y validar puertos
    int start_port = string_to_int(argv[3 + arg_offset]);
    int end_port = string_to_int(argv[4 + arg_offset]);

    if (validate_port_range(start_port, end_port) != 0) {
        return 1;
    }

    // Configurar estructura ScanConfig
    ScanConfig config;
    config.target_ip = target_ip;
    config.start_port = start_port;
    config.end_port = end_port;
    config.mode = mode;
    config.enable_banner = enable_banner;

    // Configurar dirección de red
    config.target_addr.sin_family = AF_INET;
    config.target_addr.sin_addr.s_addr = inet_addr(target_ip);

    // Crear estructura de resultados
    ScanResults results;

    // Imprimir banner inicial
    print_banner(&config);

    // Mostrar modo de escaneo
    if (num_threads > 1) {
        printf("Scan mode: Multithreaded (%d threads)\n\n", num_threads);
    } else {
        printf("Scan mode: Sequential\n\n");
    }

    // Mostrar si banner grabbing esta activo
    if (enable_banner) {
        printf("Banner grabbing: ENABLED\n\n");
    }

    // Iniciar cronómetro
    time_t start_time = time(NULL);

    // Ejecutar escaneo (con o sin threads)
    if (num_threads > 1) {
        run_threaded_scan(&config, &results, num_threads);
    } else {
        run_scan(&config, &results);
    }

    // Finalizar cronómetro
    time_t end_time = time(NULL);
    double elapsed = difftime(end_time, start_time);

    // Mostrar resumen
    print_summary(&config, &results, elapsed);

    // Guardar resultados
    save_results_to_file(&config, &results, elapsed);

    return 0;
}
