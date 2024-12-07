#include "pch/un2pch.h"
#include "window.h"
#include "log.h"
#include "GLFW/glfw3.h"

namespace unify2::core {

	static WindowManager* m_Instance = NULL;
	static GLFWwindow* m_Window = NULL;

	WindowManager& WindowManager::GetInstance() { return *m_Instance; }

	bool WindowManager::Initialize() {

		bool isInitialized = true;

		if (m_Instance == NULL) {
			m_Instance = new WindowManager();
		}


		// Initialize GLFW
		glfwInit();

		// Setup GLFW window hints

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// Initialze GLFW
		// TODO : Set window paramaters externally

		if (m_Window == NULL) {
			m_Window = glfwCreateWindow(1280, 720, "", NULL, NULL);
			glfwMakeContextCurrent(m_Window);
		}

		if (!m_Window) {
			return false;
		}


		// Poll for window events & pass them to the event manager

		if (m_Window != NULL) {
			while (!glfwWindowShouldClose(m_Window)) {
				glfwSwapBuffers(m_Window);
				glfwPollEvents();
			}
		}

		return isInitialized;
	}

	void WindowManager::Shutdown() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();

		delete m_Instance;
		m_Instance = NULL;
	}
}
