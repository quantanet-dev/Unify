#pragma once

namespace unify2::core {

	class WindowManager {
		friend class Engine;
	public:
		static WindowManager& GetInstance();

		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;

	private:
		WindowManager() = default;
		~WindowManager() = default;

		static bool Initialize();
		static void Shutdown();
		static void Update();
	};

}

