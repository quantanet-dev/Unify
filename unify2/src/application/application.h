#pragma once
#include "pch/un2pch.h"

namespace unify2 {

	class UNIFY2_API Application {
	public:
		Application() = default;
		virtual ~Application() = default;

		void run();
	};

	// Defined in CLIENT

	Application* CreateInstance();
}