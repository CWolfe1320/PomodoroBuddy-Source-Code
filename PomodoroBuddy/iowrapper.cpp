#include "iowrapper.h"


ioWrapper::ioWrapper()
{
//ioWrapper default constructor
}

ioWrapper::ioWrapper(std::string fileName)
{
    //ioWrapper constructor responsible for reading in the stats.txt file

    std::string stat;

    std::ifstream statFile ("stats.txt");
    if(statFile.is_open()){
        while(getline(statFile,stat)){
            dateAscendStats.push_back(stat);
        }
        statFile.close();
    }
}

ioWrapper::ioWrapper(std::string fileName, bool differentiate)
{
    //ioWrapper constructor responsible for reading in the settings.txt file

    std::string setting;
    std::vector<std::string> settings;

    std::ifstream settingFile ("settings.txt");
    if(settingFile.is_open()){
        while(getline(settingFile,setting)){
            settings.push_back(setting);
        }
        settingFile  .close();
    }

    trueStudyMinutes = std::stoi(settings.at(0));
    trueBreakMinutes = std::stoi(settings.at(1));
    trueLongBreakMinutes = std::stoi(settings.at(2));
}

ioWrapper::~ioWrapper()
{
//ioWrapper destructor
}

ioWrapper::ioWrapper(int pomCounter, std::chrono::duration<double> elapsedTime, time_t endDate)
{
    //ioWrapper constructor responsible for writing out to stats.txt

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
}

ioWrapper::ioWrapper(std::string studyTime, std::string breakTime, std::string longBreakTime)
{
    //ioWrapper constructor responsible for writing out to settings.txt

    std::string settingStudyTime = minuteSplicer(studyTime);
    std::string settingBreakTime = minuteSplicer(breakTime);
    std::string settinglBreakTime = minuteSplicer(longBreakTime);

    std::ofstream settingsFile ("settings.txt", std::ios::out);
    if (settingsFile.is_open()){
        settingsFile << settingStudyTime + "\n";
        settingsFile << settingBreakTime + "\n";
        settingsFile << settinglBreakTime + "\n";
    }
}

std::vector<std::string> ioWrapper::getDateAscendStats()
{
    //dateAscendStats accessor

    return dateAscendStats;
}

int ioWrapper::getStudyMinutes()
{
    //trueStudyMinutes accessor

    return trueStudyMinutes;
}

int ioWrapper::getBreakMinutes()
{
    //trueBreakMinutes accessor

    return trueBreakMinutes;
}

int ioWrapper::getLongBreakMinutes()
{
    //trueLongBreakMinutes accessor

    return trueLongBreakMinutes;
}

std::string ioWrapper::timeSplicer(std::chrono::duration<double> elapsedTime)
{
    //Splices time down to find elapsed time

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
    //Splices date down to find the correct date

    std::string tempDate = ctime(&endDate);
    std::string date;
    tempDate.pop_back();

    date = tempDate.substr(4,6) + ", " + tempDate.substr(20,tempDate.size());

    return date;
}

std::string ioWrapper::minuteSplicer(std::string minutes)
{
    //Splices minutes

    int counter = 0;
    char semi = 'i';
    while(semi != ':'){

        semi = minutes.at(counter);
        \
        if(semi != ':'){
            counter++;
        }
    }

    std::string timedMinutes = minutes.substr(0,counter);

    return timedMinutes;
}
