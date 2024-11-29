//
// Created by benja on 27-11-2024.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string &filename);
    ~Logger();
    void log(const std::string &message);
};

#endif
