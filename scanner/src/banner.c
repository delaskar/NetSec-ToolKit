#include "../include/banner.h"
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Re-Conexion al puerto para leer el banner
int grab_banner(const char *ip, int port, BannerInfo *info) {
    // Por ahora, solo inicializa la estructura
    info->port = port;
    info->has_banner = 0;
    memset(info->banner, 0, BANNER_MAX_SIZE);
    memset(info->service_name, 0, 64);
    memset(info->service_version, 0, 128);

    // Crear socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket for banner.");
        return -1;
    }

    // Configurar timeout
    struct timeval timeout;
    timeout.tv_sec = BANNER_TIMEOUT_SEC;
    timeout.tv_usec = 0;

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("Error setting timeout");
        close(sock);
        return -1;
    }

    // Conectar al puerto
    struct sockaddr_in target_addr;
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(port);
    target_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr *)&target_addr, sizeof(target_addr)) < 0) {
        close(sock);
        return -1;  // No pudimos conectar (puerto cerrado/filtrado)
    }

    // Leer el banner
    int bytes_received = recv(sock, info->banner, BANNER_MAX_SIZE - 1, 0);

    if (bytes_received > 0) {
        // Recibimos un banner
        info->banner[bytes_received] = '\0';
        info->has_banner = 1;
        close(sock);
        return 0;  // Exito
    }

    // No recibimos nada (Servicio no hablo primero)
    const char *http_probe = "GET / HTTP/1.0\r\n\r\n";
    send(sock, http_probe, strlen(http_probe), 0);

    // Intentar leer la respuesta
    bytes_received = recv(sock, info->banner, BANNER_MAX_SIZE - 1, 0);

    if (bytes_received > 0) {
        info->banner[bytes_received] = '\0';
        info->has_banner = 1;
        close(sock);
        return 0;
    }

    // Definitivamente no hay banner
    close(sock);
    return -1;  // Indicar que aún no está implementado
}

// Detectar servicio
void identify_service(BannerInfo *info) {
    // Si no hay banner, marcar como desconocido
    if (!info->has_banner || strlen(info->banner) == 0) {
        strcpy(info->service_name, "Unknown");
        strcpy(info->service_version, "N/A");
        return;
    }

    // TODO: Detectar HTTP
    if (strstr(info->banner, "HTTP/") != NULL) {
        strcpy(info->service_name, "HTTP");

        char *server_line = strstr(info->banner, "Server:");
        if (server_line != NULL) {
            server_line += 8;
            char *end = strchr(server_line, '\n');
            if (end != NULL) {
                int len = end - server_line;
                strncpy(info->service_version, server_line, len);
                info->service_version[len] = '\0';
            }
        }

        return;
    }

    // TODO: Detectar SSH
    if (strstr(info->banner, "SSH-") != NULL) {
        strcpy(info->service_name, "SSH");
        // Copiar toda la primera línea como versión
        char *end = strchr(info->banner, '\n');
        if (end != NULL) {
            int len = end - info->banner;
            strncpy(info->service_version, info->banner, len);
            info->service_version[len] = '\0';
        } else {
            strcpy(info->service_version, info->banner);
        }
        return;
    }

    // TODO: Detectar FTP
    if (strstr(info->banner, "220 ") != NULL && strstr(info->banner, "FTP") != NULL) {
        strcpy(info->service_name, "FTP");
        char *end = strchr(info->banner, '\n');
        if (end != NULL) {
            int len = end - info->banner;
            strncpy(info->service_version, info->banner, len);
            info->service_version[len] = '\0';
        }
        return;
    }

    // TODO: Detectar SMTP
    if (strstr(info->banner, "220 ") != NULL && strstr(info->banner, "SMTP") != NULL) {
        strcpy(info->service_name, "SMTP");
        char *end = strchr(info->banner, '\n');
        if (end != NULL) {
            int len = end - info->banner;
            strncpy(info->service_version, info->banner, len);
            info->service_version[len] = '\0';
        }
        return;
    }

    // TODO: Detectar SMB (por puerto conocido)
    if (info->port == 445 || info->port == 139) {
        strcpy(info->service_name, "SMB");
        strcpy(info->service_version, "Port 445/139 (SMB/NetBIOS)");
        return;
    }

    // Si no coincide con nada conocido
    strcpy(info->service_name, "Unknown");
    strcpy(info->service_version, "N/A");
}
