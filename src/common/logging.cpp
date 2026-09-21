#include "logging.hpp"

#include "common/config.hpp"
#include "common/constants.hpp"
#include "common/utils/os.hpp"

#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace logging {
    void initialize(const std::filesystem::path& log_directory, std::string_view log_file_name) {
        auto log_file = log_directory / log_file_name;
        log_file += ".log";

        try {
            auto logger = spdlog::basic_logger_mt("main", log_file.string(), true);
            spdlog::set_default_logger(logger);
            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
            spdlog::set_level(spdlog::level::info);
            spdlog::flush_on(spdlog::level::info);
        } catch (const spdlog::spdlog_ex& ex) {
            utils::os::show_message_error(std::format("Error initializing logger: {}", ex.what()));
            return;
        }

        spdlog::info("Sledge {} - Build date: {} {}", constants::version, __DATE__, __TIME__);
    }

    void update_level() {
        if (config::get().sledge.debug_logs_enabled) {
            spdlog::set_level(spdlog::level::debug);
        }
    }
}