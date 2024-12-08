#pragma once

namespace unify2::core {

	class WindowManager {
	public:

		static WindowManager& GetInstance();

		static bool Initialize();
		static void Update();
		static void Shutdown();

		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;

	private:
		WindowManager() = default;
		~WindowManager() = default;
	};

}

