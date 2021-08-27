#ifndef IOWRAPPER_H
#define IOWRAPPER_H
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <QString>
#include <vector>

class ioWrapper
{
public:
    ioWrapper();

    //stats.txt->dateAscendStats
    ioWrapper(std::string fileName);

    //settings.txt->minutes
    ioWrapper(std::string fileName, bool differentiate);

    ~ioWrapper();

    //Stats->stats.txt constructor
    ioWrapper(int pomCounter, std::chrono::duration<double> elapsedTime, std::time_t endDate);

    //Settings->settings.txt constructor
    ioWrapper(std::string studyTime, std::string breakTime, std::string longBreakTime);

    //Accessors
    std::vector<std::string> getDateAscendStats();
    int getStudyMinutes();
    int getBreakMinutes();
    int getLongBreakMinutes();

private:
    //Various splicer functions
    std::string timeSplicer(std::chrono::duration<double> elapsedTime);
    std::string dateSplicer(time_t endDate);
    std::string minuteSplicer(std::string minutes);

    //settings.txt preferences
    int trueStudyMinutes;
    int trueBreakMinutes;
    int trueLongBreakMinutes;

    //stats.txt data
    std::vector<std::string> dateAscendStats;

};

#endif // IOWRAPPER_H
