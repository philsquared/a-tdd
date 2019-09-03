#include "Logger.h"

#include <memory>

std::string logFile = "log.txt";

LogLevel Logger::s_currentLogLevel = LogLevel::Info;

void Logger::setLevel( LogLevel newLevel ) {
    s_currentLogLevel = newLevel;
}

Logger::~Logger() {}


class FileLogger : public Logger {
    std::string m_filename;
    bool m_firstLog = true;

public:
    FileLogger( std::string filename ) : m_filename( std::move( filename ) ) {}


    void log( LogLevel level, std::string_view line ) override {
        std::ofstream of;
        if( m_firstLog ) {
            of.open( m_filename );
            m_firstLog = false;
        }
        else {
            of.open( m_filename, std::ios::app );
        }

        if( line.size() > 55 )
            throw std::domain_error("Log line too long");

        // Get current date-time in printable form
        time_t now = time(0);
        tm tstruct = *localtime(&now);
        char buf[80];
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

};

Logger& logger() {
    static std::unique_ptr<Logger> s_logger = std::make_unique<FileLogger>(logFile );
    return *s_logger;
}
