#ifndef VALIDATION_H
#define VALIDATION_H

# include "scanner.h"

// Funciones de validacion
ScanMode string_to_mode(const char *mode_str);
int string_to_int(const char *str_num);
int validate_port_range(int start_port, int end_port);
int validate_ip(const char *ip_str);

#endif
