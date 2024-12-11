#include "pch/un2pch.h"
#include "application.h"
#include "core/core.h"

namespace unify {


	void Application::run() {

		// Initialize engine core
		core::Engine::GetInstance().Initialize();

	};

}