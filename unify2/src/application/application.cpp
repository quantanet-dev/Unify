#include "pch/un2pch.h"
#include "application.h"
#include "core/logger.h"
#include "core/window.h"
#include "log.h"

namespace unify2 {



	void application::run() {
		
		
		
		// Initialize Managers
		core::LogManager::Initialize();
		core::WindowManager::Initialize();


		// Update


		// Shutdown Managers
		core::WindowManager::Shutdown();
		core::LogManager::Shutdown();



	};

}