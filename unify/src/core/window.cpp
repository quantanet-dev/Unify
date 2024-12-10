#include "pch/un2pch.h"
#include "window.h"
#include "core.h"
#include "cmath"
#include "log.h"
//#include "glad/vulkan.h"
#include "glad/gl.h"
#include "windowCallbacks.h"
#include "graphics/opengl.h"

namespace unify::core {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	static WindowManager* m_Instance = NULL;
	static GLFWwindow* m_Window = NULL;

	WindowManager& WindowManager::GetInstance() { return *m_Instance; }

	bool WindowManager::Initialize() {

		bool isInitialized = true;

		if (m_Instance == NULL) {
			m_Instance = new WindowManager();
		}

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#ifdef UNIFY_PLATFORM_MACOS
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

		m_Window = glfwCreateWindow(1280, 720, "Unify Engine", NULL, NULL);
		glfwMakeContextCurrent(m_Window);

		int version = gladLoadGL(glfwGetProcAddress);
		if (version == 0) {
			LOG_ERROR("Failed to initialize OpenGL context");
		}
		else {
			LOG_INFO("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
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

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Upper triangle
		5, 4, 1 // Lower right triangle
	};

	static GLuint openGLShaderProgram;

	void WindowManager::Update() {

		

		if (m_Window != NULL) {
			if (glfwWindowShouldClose(m_Window)) {
				Event::CreateEvent(EventType::WindowClose, []() {
					Engine::Shutdown();
					});
			}

			graphics::opengl::CreateShaderProgram("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl", openGLShaderProgram);

			graphics::opengl::VertexArray vArray;
			graphics::opengl::VertexBuffer vBuffer(vertices, sizeof(vertices));

			graphics::opengl::VertexBufferLayout vLayout;
			vLayout.Push<GLfloat>(3);
			vArray.AddBuffer(vBuffer, vLayout);

			graphics::opengl::ElementBuffer eBuffer(indices, sizeof(indices));

			glUseProgram(0);
			vArray.Unbind();
			vBuffer.Unbind();
			eBuffer.Unbind();

			glClearColor(0.07f, .13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(openGLShaderProgram);

			vArray.Bind();
			eBuffer.Bind();

			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	void WindowManager::Shutdown() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();

		delete m_Instance;
		m_Instance = NULL;
	}
}
