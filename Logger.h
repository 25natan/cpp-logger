#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <chrono>
#include <string>
#include <ctime>
#include <map>
#include <fstream>
enum LogType{Info, Error, Debug};
class Logger{
    public:
    Logger():m_isStd(true){
        initLogTypesMap();
    }
    Logger(const std::string& fileName):m_isStd(false), m_logFile(fileName){
        initLogTypesMap();
    }
    void log(const LogType& type, const std::string& message){
        std::ostream& out = m_isStd ? std::cout : m_logFile;
        out << '[' + now() + "][" + m_typesMap[type] + "] " + message << '\n';
    }
    private:
    void initLogTypesMap(){
        m_typesMap[LogType::Info] = "INFO";
        m_typesMap[LogType::Error] = "ERROR";
        m_typesMap[LogType::Debug] = "DEBUG";
    }
    std::string now(){
        auto timec = std::time(NULL);
        auto timecpp = std::chrono::system_clock::now().time_since_epoch();
        auto timeInfo = std::localtime(&timec);
        auto hour = timeInfo->tm_hour;
        auto minutes = timeInfo->tm_min;
        auto seconds = timeInfo->tm_sec;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timecpp).count() % 1000;
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(timecpp).count() % 1000;
        auto timeStr = std::string();
        timeStr += std::to_string(hour / 10) + std::to_string(hour % 10);
        timeStr += ':' + std::to_string(minutes / 10) + std::to_string(minutes % 10);
        timeStr += ':' + std::to_string(seconds / 10) + std::to_string(seconds % 10);
        timeStr += ':' + std::to_string(milliseconds / 100) + std::to_string((milliseconds % 100) / 10) + std::to_string(milliseconds % 10);
        timeStr += ':' + std::to_string(microseconds / 100) + std::to_string((microseconds % 100) / 10) + std::to_string(microseconds % 10);
        return timeStr;
    }
    std::ofstream m_logFile;
    std::map<LogType, std::string> m_typesMap;
    bool m_isStd;
};
#endif