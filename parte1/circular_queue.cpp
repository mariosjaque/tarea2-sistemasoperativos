//
// Created by benja on 27-11-2024.
//

#include "circular_queue.h"
#include <iostream>

CircularQueue::CircularQueue(int tam_inicial)
    : capacidad(tam_inicial), frente(0), final(0), count(0) {
    cola.resize(capacidad);
}

bool CircularQueue::insertar(int item) {
    std::lock_guard<std::mutex> lock(mtx);
    if (count == capacidad) {
        duplicar();
    }
    cola[final] = item;
    final = (final + 1) % capacidad;
    count++;
    return true;
}

bool CircularQueue::extraer(int &item) {
    std::lock_guard<std::mutex> lock(mtx);
    if (count == 0) return false;  // Cola vacía

    item = cola[frente];
    frente = (frente + 1) % capacidad;
    count--;

    if (count <= capacidad / 4 && capacidad > 2) {
        reducir();
    }
    return true;
}

void CircularQueue::duplicar() {
    capacidad *= 2;
    std::vector<int> nuevaCola(capacidad);
    for (int i = 0; i < count; ++i) {
        nuevaCola[i] = cola[(frente + i) % (capacidad / 2)];
    }
    frente = 0;
    final = count;
    cola = std::move(nuevaCola);
}

void CircularQueue::reducir() {
    capacidad /= 2;
    std::vector<int> nuevaCola(capacidad);
    for (int i = 0; i < count; ++i) {
        nuevaCola[i] = cola[(frente + i) % (capacidad * 2)];
    }
    frente = 0;
    final = count;
    cola = std::move(nuevaCola);
}

int CircularQueue::obtenerTamano() {
    std::lock_guard<std::mutex> lock(mtx);
    return capacidad;
}
