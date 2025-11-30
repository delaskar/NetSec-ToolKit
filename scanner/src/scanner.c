#include "../include/scanner.h"
#include "../include/output.h"
#include "../include/banner.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

// Escanea un puerto individual
// Retorna: 0 = abierto, -1 = cerrado/error
int scan_port(struct sockaddr_in *target, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        return -1;
    }

    target->sin_port = htons(port);
    int connection = connect(sock, (struct sockaddr *)target, sizeof(*target));
    close(sock);
    return connection;
}

// Ejecuta el escaneo completo
void run_scan(ScanConfig *config, ScanResults *results) {
    // Inicializar contadores
    results->total_ports = 0;
    results->open_ports = 0;
    results->closed_ports = 0;
    results->filtered_ports = 0;

    // Bucle principal: iterar por cada puerto
    for (int port = config->start_port; port <= config->end_port; port++) {

        // Escanear el puerto
        int result = scan_port(&config->target_addr, port);

        // Determinar estado y actualizar contadores
        if (result == 0) {
            // Puerto ABIERTO
            print_port_result(port, "OPEN", config->mode);
            results->open_ports++;

            if (config->enable_banner) {
                BannerInfo banner_info;
                if (grab_banner(config->target_ip, port, &banner_info) == 0) {
                    identify_service(&banner_info);
                    print_banner_info(&banner_info);
                }
            }
        }
        else if (errno == ECONNREFUSED) {
            // Puerto CERRADO
            print_port_result(port, "CLOSED", config->mode);
            results->closed_ports++;
        }
        else if (errno == ETIMEDOUT) {
            // Puerto FILTRADO
            print_port_result(port, "FILTERED", config->mode);
            results->filtered_ports++;
        }

        // Incrementar total
        results->total_ports++;
    }
}
