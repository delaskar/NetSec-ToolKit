#include "../include/validation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// Convierte string de modo a enum
ScanMode string_to_mode(const char *mode_str) {
    if (strcmp(mode_str, "open") == 0) return OPEN;
    if (strcmp(mode_str, "closed") == 0) return CLOSED;
    if (strcmp(mode_str, "filtered") == 0) return FILTERED;
    if (strcmp(mode_str, "all") == 0) return ALL;
    return INVALID_MODE;
}

// Convierte string a int con validación
int string_to_int(const char *str_num) {
    char *endptr;
    long num = strtol(str_num, &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Error: '%s' is not a valid number!\n", str_num);
        exit(1);
    }
    return (int)num;
}

// Valida rango de puertos (1-65535)
int validate_port_range(int start_port, int end_port) {
    if (start_port < 1 || start_port > 65535 ||
        end_port < 1 || end_port > 65535) {
        fprintf(stderr, "Error: Ports must be between 1 and 65535\n");
        return -1;
    }

    if (start_port > end_port) {
        fprintf(stderr, "Error: Start port must be <= End port\n");
        return -1;
    }

    return 0;
}

// Valida formato de IP
int validate_ip(const char *ip_str) {
    if (inet_addr(ip_str) == INADDR_NONE) {
        fprintf(stderr, "Error: '%s' is not a valid IP address!\n", ip_str);
        return -1;
    }
    return 0;
}
