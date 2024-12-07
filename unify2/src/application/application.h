#pragma once
#include "pch/un2pch.h"

namespace unify2 {

	class UNIFY2_API application {
	public:
		application() = default;
		virtual ~application() = default;

		void run();
	};

	// Defined in CLIENT

	application* createInstance();
}