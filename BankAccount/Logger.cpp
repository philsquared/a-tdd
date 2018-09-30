#include "Logger.h"

LogLevel g_currentLogLevel = LogLevel::Info;
std::string logFile = "log.txt";

void log( LogLevel level, std::string const& line ) {
    std::ofstream of( logFile );

    // Get current date-time in printable form
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    of << buf << " ";

    switch( level ) {
        case LogLevel::Error:   of << "  ERROR"; break;
        case LogLevel::Warning: of << "WARNING"; break;
        case LogLevel::Info:    of << "   INFO"; break;
        case LogLevel::Debug:   of << "  DEBUG"; break;
    }
    of << " | " << line << std::endl;
}