//
// Created by benja on 27-11-2024.
//

#include "monitor.h"
#include <iostream>
#include <chrono>
#include <thread>

Monitor::Monitor(int p, int c, int tam_inicial, int t)
    : cola(tam_inicial), numProductores(p), numConsumidores(c), tiempoEspera(t),
      todosProductoresFinalizados(false), logger("log.txt") {}

void Monitor::productor(int id) {
    for (int i = 0; i < 100; ++i) {
        cola.insertar(i);
        logger.log("Productor " + std::to_string(id) + " ha insertado " + std::to_string(i));
    }
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (--numProductores == 0) {
            todosProductoresFinalizados = true;
            cv.notify_all();
        }
    }
}

void Monitor::consumidor(int id) {
    int item;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return todosProductoresFinalizados || cola.obtenerTamano() > 0; });
        if (cola.extraer(item)) {
            logger.log("Consumidor " + std::to_string(id) + " extrajo " + std::to_string(item));
        } else if (todosProductoresFinalizados) {
            break;
        }
    }
}

void Monitor::iniciarSimulacion() {
    for (int i = 0; i < numProductores; ++i) {
        productores.push_back(std::thread(&Monitor::productor, this, i));
    }

    for (int i = 0; i < numConsumidores; ++i) {
        consumidores.push_back(std::thread(&Monitor::consumidor, this, i));
    }

    for (auto &prod : productores) {
        prod.join();
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        todosProductoresFinalizados = true;
        cv.notify_all();
    }

    for (auto &cons : consumidores) {
        cons.join();
    }
}