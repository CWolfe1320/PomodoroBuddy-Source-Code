#ifndef IOWRAPPER_H
#define IOWRAPPER_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <QDebug>
#include <vector>

class ioWrapper
{
public:
    ioWrapper();

    //stats.txt->dateAscendStats
    ioWrapper(std::string fileName);

    ~ioWrapper();

    //Stats->stats.txt constructor
    ioWrapper(int pomCounter, std::chrono::duration<double> elapsedTime, std::time_t endDate);

    std::vector<std::string> getDateAscendStats();

private:
    std::string timeSplicer(std::chrono::duration<double> elapsedTime);
    std::string dateSplicer(time_t endDate);


    std::vector<std::string> dateAscendStats;

};

#endif // IOWRAPPER_H
