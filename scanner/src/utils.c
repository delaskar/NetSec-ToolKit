#include "../include/utils.h"
#include <stdio.h>

// Imprime mensaje de uso del programa
void print_usage(const char *program_name) {
    fprintf(stderr, "Usage: %s <MODE> <Target_IP> <Start_Port> <End_Port>\n", program_name);
    fprintf(stderr, "Modes: open, closed, filtered, all\n");
    fprintf(stderr, "Example: %s open 127.0.0.1 1 1000\n", program_name);
}

// Convierte enum ScanMode a string
const char* get_mode_string(ScanMode mode) {
    switch(mode) {
        case OPEN: return "open";
        case CLOSED: return "closed";
        case FILTERED: return "filtered";
        case ALL: return "all";
        default: return "unknown";
    }
}
