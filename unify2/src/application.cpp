#include "un2pch.h"
#include "application.h"
#include "core/logger.h"
#include "log.h"

namespace unify2{

	void application::run() {
		core::LogManager::Initialize();

		LOG_TRACE("HELLO FROM UNIFY ENGINE!");
		LOG_INFO("HELLO FROM UNIFY ENGINE!");
		LOG_WARN("HELLO FROM UNIFY ENGINE!");
		LOG_DEBUG("HELLO FROM UNIFY ENGINE!");
		LOG_ERROR("HELLO FROM UNIFY ENGINE!");
		LOG_FATAL("HELLO FROM UNIFY ENGINE!");


		/*while (true);*/

		core::LogManager::Shutdown();
	};

}