//
// Created by Phil Nash on 30/09/2018.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

enum class LogLevel {
    Error,
    Warning,
    Info,
    Debug
};

extern LogLevel g_currentLogLevel;
extern std::string logFile;

void log( LogLevel level, std::string const& line );


#define LOG_ERROR( text ) do { if( g_currentLogLevel >= LogLevel::Error ){ std::ostringstream oss; oss << text; log( LogLevel::Error, oss.str() ); } } while( false )
#define LOG_WARN( text ) do { if( g_currentLogLevel >= LogLevel::Warning ){ std::ostringstream oss; oss << text; log( LogLevel::Warning, oss.str() ); } } while( false )
#define LOG_INFO( text ) do { if( g_currentLogLevel >= LogLevel::Info ){ std::ostringstream oss; oss << text; log( LogLevel::Info, oss.str() ); } } while( false )
#define LOG_DEBUG( text ) do { if( g_currentLogLevel >= LogLevel::Debug ){ std::ostringstream oss; oss << text; log( LogLevel::Debug, oss.str() ); } } while( false )



#endif // LOGGER_H
