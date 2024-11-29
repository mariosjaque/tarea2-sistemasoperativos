//
// Created by benja on 27-11-2024.
//

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <vector>
#include <mutex>

class CircularQueue {
private:
    std::vector<int> cola;
    int capacidad;
    int frente;
    int final;
    int count;
    std::mutex mtx;
    void duplicar();
    void reducir();

public:
    CircularQueue(int tam_inicial);
    bool insertar(int item);
    bool extraer(int &item);
    int obtenerTamano();
};

#endif
