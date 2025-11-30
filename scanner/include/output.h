#ifndef OUTPUT_H
#define OUTPUT_H

#include "scanner.h"
#include "banner.h"
#include <time.h>

// Funciones de salida
void print_banner(ScanConfig *config);
void print_port_result(int port, const char *status, ScanMode mode);
void print_summary(ScanConfig *config, ScanResults *results, double elapsed_time);
int save_results_to_file(ScanConfig *config, ScanResults *results, double elapsed_time);
void print_banner_info(BannerInfo *info);

#endif
