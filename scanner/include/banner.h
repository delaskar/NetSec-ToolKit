#ifndef BANNER_H
#define BANNER_H

#include <netinet/in.h>

#define BANNER_MAX_SIZE 1024
#define BANNER_TIMEOUT_SEC 3

typedef struct {
    int port;
    char banner[BANNER_MAX_SIZE];
    char service_name[64];      //ej: "HTTP", "SSH"
    char service_version[128];  //ej: "Apache/2.4.51"
    int has_banner;             // 0 = no tiene, 1 = si tiene
} BannerInfo;

// Funcion principal de banner grabbing
int grab_banner(const char *ip, int port, BannerInfo *info);

// Identificar servicio por banner
void identify_service(BannerInfo *info);

#endif
