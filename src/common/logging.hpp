#pragma once

#include "common/constants.hpp"
#include "plog/Severity.h"

#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Init.h>
#include <plog/Log.h>

#include <filesystem>
#include <fstream>

namespace logging
{
    inline void initialize(const std::filesystem::path& log_directory, std::string_view log_file_name)
    {
        auto log_file = log_directory / log_file_name += ".log";
    
        std::ofstream ofs(log_file, std::ios::trunc);
        ofs.close();
    
        static plog::RollingFileAppender<plog::TxtFormatter>fileAppender(log_file.string().c_str(), 0, 0);
        static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
    
        plog::init(plog::debug, &fileAppender).addAppender(&consoleAppender);

        PLOG_INFO << "Sledge " << constants::version << " - Build date: " << __DATE__ << " " << __TIME__;
    }
}