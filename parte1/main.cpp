#include "monitor.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc < 9) {
        std::cerr << "Uso: " << argv[0] << " -p <prod> -c <cons> -s <size> -t <timeout>\n";
        return 1;
    }

    int productores = std::atoi(argv[2]);
    int consumidores = std::atoi(argv[4]);
    int tam_inicial = std::atoi(argv[6]);
    int timeout = std::atoi(argv[8]);

    Monitor monitor(productores, consumidores, tam_inicial, timeout);
    monitor.iniciarSimulacion();

    return 0;
}