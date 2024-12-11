#pragma once
#include "core.h"

namespace unify::core {

	class LogManager : IManager {
		friend class Engine;
	public:
		static LogManager& GetInstance();

		void Initialize();
		void Update();
		void Shutdown();

		LogManager(const LogManager&) = delete;
		LogManager& operator=(const LogManager&) = delete;

	private:
		LogManager() = default;
		~LogManager() = default;
	};

}