#pragma once

namespace unify::core {

	class LogManager {
		friend class Engine;
	public:
		static LogManager& GetInstance();

		LogManager(const LogManager&) = delete;
		LogManager& operator=(const LogManager&) = delete;

	private:
		LogManager() = default;
		~LogManager() = default;

		static bool Initialize();
		static void Shutdown();
	};

}