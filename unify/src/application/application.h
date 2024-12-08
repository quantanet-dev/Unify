#pragma once
#include "pch/un2pch.h"

namespace unify {

	class UNIFY_API Application {
	public:
		Application() = default;
		virtual ~Application() = default;

		void run();
	};

	// Defined in CLIENT

	Application* CreateInstance();
}