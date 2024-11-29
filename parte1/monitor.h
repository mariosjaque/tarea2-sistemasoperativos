//
// Created by benja on 27-11-2024.
//

#ifndef MONITOR_H
#define MONITOR_H

#include "circular_queue.h"
#include "logger.h"
#include <thread>
#include <vector>
#include <atomic>
#include <condition_variable>

class Monitor {
private:
    CircularQueue cola;
    int numProductores;
    int numConsumidores;
    int tiempoEspera;
    Logger logger;
    std::vector<std::thread> productores;
    std::vector<std::thread> consumidores;
    std::atomic<bool> todosProductoresFinalizados;
    std::mutex mtx;
    std::condition_variable cv;
    void productor(int id);
    void consumidor(int id);

public:
    Monitor(int p, int c, int tam_inicial, int t);
    void iniciarSimulacion();
};

#endif
