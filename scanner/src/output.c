#include "../include/output.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// Imprime el banner inicial con información del escaneo
void print_banner(ScanConfig *config) {
    printf("========================================\n");
    printf("NetSec Toolkit - Port Scanner\n");
    printf("========================================\n");
    printf("Target: %s\n", config->target_ip);
    printf("Port range: %d-%d\n", config->start_port, config->end_port);
    printf("Mode: %s\n", get_mode_string(config->mode));
    printf("========================================\n\n");
}

// Imprime resultado de un puerto según el modo activo
void print_port_result(int port, const char *status, ScanMode mode) {
    // Determinar si debemos imprimir según el modo
    int should_print = 0;

    if (mode == ALL) {
        should_print = 1;  // Modo ALL imprime todo
    } else if (mode == OPEN && strcmp(status, "OPEN") == 0) {
        should_print = 1;
    } else if (mode == CLOSED && strcmp(status, "CLOSED") == 0) {
        should_print = 1;
    } else if (mode == FILTERED && strcmp(status, "FILTERED") == 0) {
        should_print = 1;
    }

    // Si debe imprimir, mostrar el resultado
    if (should_print) {
        printf("Port %d - %s\n", port, status);
    }
}

// Imprime el resumen final del escaneo
void print_summary(ScanConfig *config, ScanResults *results, double elapsed_time) {
    printf("\n========================================\n");
    printf("SCAN SUMMARY\n");
    printf("========================================\n");
    printf("Target: %s\n", config->target_ip);
    printf("Ports scanned: %d\n", results->total_ports);
    printf("Open ports: %d\n", results->open_ports);
    printf("Closed ports: %d\n", results->closed_ports);
    printf("Filtered ports: %d\n", results->filtered_ports);
    printf("Scan duration: %.2f seconds\n", elapsed_time);
    printf("========================================\n");
}

// Guarda los resultados en archivo
int save_results_to_file(ScanConfig *config, ScanResults *results, double elapsed_time) {
    // 1. Abrir archivo en modo "w"
    FILE *file = fopen("scan_results.txt", "w");

    // 2. Verificar si se abrió correctamente
    if (file == NULL) {
        perror("Warning: Could not save results to file");
        return -1;
    }

    // 3. Escribir resultados en el archivo
    time_t now = time(NULL);

    fprintf(file, "========================================\n");
    fprintf(file, "NetSec Toolkit - Scan Results\n");
    fprintf(file, "========================================\n");
    fprintf(file, "Date: %s", ctime(&now));
    fprintf(file, "Target: %s\n", config->target_ip);
    fprintf(file, "Port range: %d-%d\n", config->start_port, config->end_port);
    fprintf(file, "Mode: %s\n", get_mode_string(config->mode));
    fprintf(file, "----------------------------------------\n");
    fprintf(file, "Ports scanned: %d\n", results->total_ports);
    fprintf(file, "Open ports: %d\n", results->open_ports);
    fprintf(file, "Closed ports: %d\n", results->closed_ports);
    fprintf(file, "Filtered ports: %d\n", results->filtered_ports);
    fprintf(file, "----------------------------------------\n");
    fprintf(file, "Scan duration: %.2f seconds\n", elapsed_time);
    fprintf(file, "========================================\n");

    // 4. Cerrar archivo
    fclose(file);

    // 5. Mensaje de confirmación (va DESPUÉS de cerrar)
    printf("\nResults saved to: scan_results.txt\n");

    // 6. Retornar éxito
    return 0;
}

// Imprime información del banner con formato indentado
void print_banner_info(BannerInfo *info) {
    if (info->has_banner) {
        printf("  └─ Service: %s\n", info->service_name);
        printf("  └─ Version: %s\n", info->service_version);
    }
}
