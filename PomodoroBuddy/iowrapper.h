#ifndef IOWRAPPER_H
#define IOWRAPPER_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <QDebug>

class ioWrapper
{
public:
    ioWrapper();

    ~ioWrapper();

    //Stats->stats.txt constructor
    ioWrapper(int pomCounter, std::chrono::duration<double> elapsedTime, std::time_t endDate);

private:
    std::string timeSplicer(std::chrono::duration<double> elapsedTime);
    std::string dateSplicer(time_t endDate);

};

#endif // IOWRAPPER_H
