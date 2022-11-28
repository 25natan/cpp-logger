#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <chrono>
#include <string>
#include <ctime>
#include <map>
#include <fstream>
#include <iomanip>
#include <sstream>
enum LogType{Info, Error, Debug};
class Logger{
    public:
    Logger():m_isStd(true),
        m_typesMap{{LogType::Info, "INFO"}, {LogType::Error, "ERROR"}, {LogType::Debug, "DEBUG"}}{}
    Logger(const std::string& fileName):m_isStd(false), m_logFile(fileName), 
        m_typesMap{{LogType::Info, "INFO"}, {LogType::Error, "ERROR"}, {LogType::Debug, "DEBUG"}}{}
    void log(const LogType& type, const std::string& message){
        std::ostream& out = m_isStd ? std::cout : m_logFile;
        out << '[' << timeStamp() << "][" << m_typesMap[type] << "] " << message << '\n';
    }
    private:
    std::string timeStamp(){
        auto timec = std::time(NULL);
        auto timecpp = std::chrono::system_clock::now().time_since_epoch();
        auto timeInfo = std::localtime(&timec);
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timecpp).count() % 1000;
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(timecpp).count() % 1000;
        auto strStream = std::stringstream();
        strStream << std::setfill('0') << std::setw(2) << timeInfo->tm_hour << ':' << std::setw(2) << timeInfo->tm_min << ':' 
            << std::setw(2) << timeInfo->tm_sec << ':' << std::setw(3) << milliseconds << ':' << std::setw(3) << microseconds;
        return strStream.str();
    }
    std::ofstream m_logFile;
    std::map<LogType, std::string> m_typesMap;
    bool m_isStd;
};
#endif