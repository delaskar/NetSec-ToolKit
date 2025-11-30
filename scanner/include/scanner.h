#ifndef SCANNER_H
#define SCANNER_H

#include <netinet/in.h>

// Modos de escaneo
typedef enum {
    OPEN,
    CLOSED,
    FILTERED,
    ALL,
    INVALID_MODE
} ScanMode;

// Estructura para resultados
typedef struct {
    int total_ports;
    int open_ports;
    int closed_ports;
    int filtered_ports;
} ScanResults;

// Estructura para configuracion de escaneo
typedef struct {
    char *target_ip;
    int start_port;
    int end_port;
    ScanMode mode;
    struct sockaddr_in target_addr;
    int enable_banner;
} ScanConfig;

// Funciones Publicas del modulo scanner
int scan_port(struct sockaddr_in *target, int port);
void run_scan(ScanConfig *config, ScanResults *results);

#endif
