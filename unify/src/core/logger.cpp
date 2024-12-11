#include "pch/un2pch.h"
#include "logger.h"
#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace unify::core {

    LogManager& LogManager::GetInstance() { 
        static LogManager* m_Instance = new LogManager;
        return *m_Instance;
    }

    void LogManager::Initialize()
    {
        auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%n]: %v%$");

        std::vector<spdlog::sink_ptr> sinks{ console };
        auto logger = std::make_shared<spdlog::logger>(UNIFY_LOGGER_NAME, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(logger);
        LOG_INFO("Log Manager Initialized");
    }

    void LogManager::Update(){}

    void LogManager::Shutdown() {
        LOG_INFO("Log Manager Shutting Down");
        spdlog::shutdown();
    }
}
