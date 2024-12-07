#include "realpch.h"
#include "logger.h"
#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace unify2::core {

    static LogManager* m_Instance = NULL;

    LogManager& LogManager::GetInstance() { return *m_Instance; }

    bool LogManager::Initialize()
    {
        bool isInitialized = true;

        if (m_Instance == NULL) {
            m_Instance = new LogManager();
        }

        auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console->set_pattern("%^[%Y-%m-%d %H:%M:%S] [%n]: %v%$");

        std::vector<spdlog::sink_ptr> sinks{ console };
        auto logger = std::make_shared<spdlog::logger>(UNIFY_LOGGER_NAME, sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(logger);

        if (!spdlog::get(UNIFY_LOGGER_NAME)) {
            return false;
        }

        return isInitialized;
    }

    void LogManager::Shutdown() {
        spdlog::shutdown();

        delete m_Instance;
        m_Instance = NULL;
    }
}
