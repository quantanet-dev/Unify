#pragma once

namespace unify2::core {

	class LogManager {
	public:

		static LogManager& GetInstance();

		static bool Initialize();
		static void Shutdown();

		LogManager(const LogManager&) = delete;
		LogManager& operator=(const LogManager&) = delete;

	private:
		LogManager() = default;
		~LogManager() = default;
	};

}