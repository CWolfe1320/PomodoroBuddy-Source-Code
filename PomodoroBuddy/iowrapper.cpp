#include "iowrapper.h"
#include <QString>

ioWrapper::ioWrapper()
{

}

ioWrapper::ioWrapper(std::string fileName)
{
    std::string stat;

    std::ifstream statFile ("stats.txt");
    if(statFile.is_open()){
        while(getline(statFile,stat)){
            dateAscendStats.push_back(stat);
        }
        statFile.close();
    }
    else{
        qDebug() << "No work sorry :(";
    }
}

ioWrapper::~ioWrapper()
{

}

ioWrapper::ioWrapper(int pomCounter, std::chrono::duration<double> elapsedTime, time_t endDate)
{
    std::string statString;
    std::string pcString = "Pomodoros: " + std::to_string(pomCounter);
    std::string eTime = timeSplicer(elapsedTime);
    std::string date = dateSplicer(endDate);
    statString = date + "| " + pcString + " | " + eTime;

    std::ofstream statsFile ("stats.txt", std::ios::out | std::ios::app);
    if (statsFile.is_open()){
        statsFile << statString + "\n";
        statsFile.close();
    }
    else{ //REMOVE THIS ADD SOMETHING ELSE
        qDebug() << "No work sorry";
    }
}

std::vector<std::string> ioWrapper::getDateAscendStats()
{
    return dateAscendStats;
}

std::string ioWrapper::timeSplicer(std::chrono::duration<double> elapsedTime)
{
    int elapsedSeconds = elapsedTime.count();
    int elapsedMinutes = 0;
    int elapsedHours = 0;
    std::string eTime = "Time spent: ";
    std::string tempMinutes;
    std::string tempSeconds;

    if(elapsedSeconds > 59){
        elapsedMinutes = elapsedSeconds / 60;
        elapsedSeconds = elapsedSeconds % 60;
    }
    if(elapsedMinutes > 59){
        elapsedHours = elapsedMinutes / 60;
        elapsedMinutes = elapsedMinutes % 60;
    }

    if (elapsedMinutes < 10){
        tempMinutes = "0" + std::to_string(elapsedMinutes);
    }
    else{
        tempMinutes = std::to_string(elapsedMinutes);
    }

    if (elapsedSeconds < 10){
        tempSeconds = "0" + std::to_string(elapsedSeconds);
    }
    else{
        tempSeconds = std::to_string(elapsedSeconds);
    }

    eTime = eTime + std::to_string(elapsedHours) + ":";
    eTime = eTime + tempMinutes + ":";
    eTime = eTime + tempSeconds;

    return eTime;
}

std::string ioWrapper::dateSplicer(time_t endDate)
{
    std::string tempDate = ctime(&endDate);
    std::string date;
    tempDate.pop_back();

    date = tempDate.substr(4,6) + ", " + tempDate.substr(20,tempDate.size());


    qDebug() << QString::fromStdString(tempDate);
    qDebug() << QString::fromStdString(date);

    return date;
}
