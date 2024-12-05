#include <managers/managers.h>

namespace Unify::managers
{

    void UnifyLogManager::Initialize()
    {
        auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console->set_pattern("%^[%Y-%m-%d %H:%M:%S] %v%$");

        auto logger = std::make_shared<spdlog::logger>("console", console);
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);
        spdlog::register_logger(logger);
    };

    void UnifyLogManager::Update() {

    };

    void UnifyLogManager::Shutdown() {
        spdlog::shutdown();
    };

}