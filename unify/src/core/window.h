#pragma once
#include "pch/un2pch.h"
#include "core.h"
#include "events.h"

namespace unify::core {

	class WindowManager : public IManager {
		friend class Engine;
	public:
		static WindowManager& GetInstance();

		void Initialize();
		void Update();
		void Shutdown();

		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;

	private:
		WindowManager() {
			std::cout << "Window Manager Created\n";
		};
		~WindowManager() = default;
	};

}

