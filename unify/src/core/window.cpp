#include "pch/un2pch.h"
#include "window.h"
#include "core.h"
#include "events.h"
#include "log.h"
#include "glad/gl.h"
//#include "glad/vulkan.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace unify::core {

	bool m_MouseInWindow = false;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void cursor_enter_callback(GLFWwindow* window, int entered)
	{
		(entered) ? m_MouseInWindow = true : m_MouseInWindow = false;
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		if (m_MouseInWindow) {
			Event::CreateEvent(EventType::MouseMoved, [xpos, ypos]() {
				LOG_TRACE("Mouse Moved! {}, {}", xpos, ypos)
				});
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Event::CreateEvent(EventType::MouseScrolled, [xoffset, yoffset]() {
			LOG_TRACE("Mouse Scrolled! {}, {}", xoffset, yoffset)
			});
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		switch (action) {
		case GLFW_PRESS:
			Event::CreateEvent(EventType::MouseMoved, [button]() {
				LOG_TRACE("Mouse Button Pressed! {}", button)
				});
			break;
		case GLFW_RELEASE:
			Event::CreateEvent(EventType::MouseMoved, [button]() {
				LOG_TRACE("Mouse Button Released! {}", button)
				});
			break;
		default:
			break;
		}

	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action) {
		case GLFW_PRESS:
			Event::CreateEvent(EventType::KeyPressed, [key, scancode]() {
				LOG_TRACE("Key Pressed! {}, {}", key, scancode)
				});
			break;
		case GLFW_RELEASE:
			Event::CreateEvent(EventType::KeyReleased, [key, scancode]() {
				LOG_TRACE("Key Released! {}, {}", key, scancode)
				});
			break;
		default:
			break;
		}
	}

	void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
	{
		Event::CreateEvent(EventType::WindowMove, [xpos, ypos]() {
			LOG_TRACE("Window Moved! {}, {}", xpos, ypos)
			});
	}

	void window_focus_callback(GLFWwindow* window, int focused)
	{
		if (focused)
		{
			Event::CreateEvent(EventType::WindowFocus, []() {
				LOG_TRACE("Window Focused!")
				});
		}
		else
		{
			Event::CreateEvent(EventType::WindowUnfocus, []() {
				LOG_TRACE("Window Unfocused!")
				});
		}
	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Event::CreateEvent(EventType::WindowResize, [width, height]() {
			LOG_TRACE("Window Resized! {}, {}", width, height)
			});
	}

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
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		// Initialze GLFW
		// TODO : Set window paramaters externally

		if (m_Window == NULL) {
			m_Window = glfwCreateWindow(640, 360, "", NULL, NULL);
			glfwMakeContextCurrent(m_Window);

			int version = gladLoadGL(glfwGetProcAddress);
			if (version == 0) {
				LOG_ERROR("Failed to initialize OpenGL context");
			}
			else {
				LOG_INFO("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
			}
		}

		if (!m_Window) {
			return false;
		}

		glfwSetWindowSizeLimits(m_Window, 640, 360, GLFW_DONT_CARE, GLFW_DONT_CARE);
		glfwSetWindowAspectRatio(m_Window, 16, 9);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
		glfwSetWindowPosCallback(m_Window, window_pos_callback);
		glfwSetWindowFocusCallback(m_Window, window_focus_callback);
		glfwSetWindowSizeCallback(m_Window, window_size_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetCursorEnterCallback(m_Window, cursor_enter_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);

		return isInitialized;
	}

	void WindowManager::Update() {

		if (m_Window != NULL) {
			if (glfwWindowShouldClose(m_Window)) {
				Event::CreateEvent(EventType::WindowClose, []() {
					Engine::Shutdown();
					});
			}
			glfwPollEvents();
			glClearColor(0.f, .7f, 1, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(m_Window);
		}

	}

	void WindowManager::Shutdown() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();

		delete m_Instance;
		m_Instance = NULL;
	}
}
