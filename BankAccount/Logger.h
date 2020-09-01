#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string_view>

enum class LogLevel {
    Error,
    Warning,
    Info,
    Debug
};

class Logger {
    static LogLevel s_currentLogLevel;

public:
    virtual ~Logger();

    virtual void log( LogLevel level, std::string_view line ) = 0;

    static void setLevel( LogLevel newLevel );
    static LogLevel level() { return s_currentLogLevel; }
};

Logger& logger();

#define LOG_ERROR( text ) do { if( Logger::level() >= LogLevel::Error ){ std::ostringstream oss; oss << text; logger().log( LogLevel::Error, oss.str() ); } } while( false )
#define LOG_WARN( text ) do { if( Logger::level() >= LogLevel::Warning ){ std::ostringstream oss; oss << text; logger().log( LogLevel::Warning, oss.str() ); } } while( false )
#define LOG_INFO( text ) do { if( Logger::level() >= LogLevel::Info ){ std::ostringstream oss; oss << text; logger().log( LogLevel::Info, oss.str() ); } } while( false )
#define LOG_DEBUG( text ) do { if( Logger::level() >= LogLevel::Debug ){ std::ostringstream oss; oss << text; logger().log( LogLevel::Debug, oss.str() ); } } while( false )



#endif // LOGGER_H
