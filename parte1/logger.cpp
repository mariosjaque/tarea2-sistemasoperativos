//
// Created by benja on 27-11-2024.
//

#include "logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

Logger::Logger(const std::string &filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error al abrir archivo de log\n";
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string &message) {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::string logMessage = std::string(std::ctime(&time)) + ": " + message;

    logFile << logMessage << std::endl;
    std::cout << logMessage << std::endl;
}
