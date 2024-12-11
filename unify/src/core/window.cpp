#include "pch/un2pch.h"
#include "cmath"
#include "window.h"
#include "log.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
//#include "graphics/opengl.h"
#include "core/renderer.h"

namespace unify::core {

	bool m_MouseInWindow = false;
	static GLFWwindow* m_Window;

	void cursor_enter_callback(GLFWwindow* window, int entered) {
		(entered) ? m_MouseInWindow = true : m_MouseInWindow = false;
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		if (m_MouseInWindow) {
			Event::CreateNewEvent(EventType::MouseMoved, [xpos, ypos]() {
				//LOG_TRACE("Mouse Moved! {}, {}", xpos, ypos)
			});
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Event::CreateNewEvent(EventType::MouseScrolled, [xoffset, yoffset]() {
			//LOG_TRACE("Mouse Scrolled! {}, {}", xoffset, yoffset)
		});
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			Event::CreateNewEvent(EventType::MouseMoved, [button]() {
				//LOG_TRACE("Mouse Button Pressed! {}", button)
			});
			break;
		case GLFW_RELEASE:
			Event::CreateNewEvent(EventType::MouseMoved, [button]() {
				//LOG_TRACE("Mouse Button Released! {}", button)
			});
			break;
		default:
			break;
		}

	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			Event::CreateNewEvent(EventType::KeyPressed, [key, scancode]() {
				//LOG_TRACE("Key Pressed! {}, {}", key, scancode)
			});
			break;
		case GLFW_RELEASE:
			Event::CreateNewEvent(EventType::KeyReleased, [key, scancode]() {
				//LOG_TRACE("Key Released! {}, {}", key, scancode)
			});
			break;
		default:
			break;
		}
	}

	void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
		Event::CreateNewEvent(EventType::WindowMove, [xpos, ypos]() {
			//LOG_TRACE("Window Moved! {}, {}", xpos, ypos)
		});
	}

	void window_focus_callback(GLFWwindow* window, int focused) {
		if (focused)
		{
			Event::CreateNewEvent(EventType::WindowFocus, []() {
				//LOG_TRACE("Window Focused!")
			});
		}
		else
		{
			Event::CreateNewEvent(EventType::WindowUnfocus, []() {
				//LOG_TRACE("Window Unfocused!")
			});
		}
	}

	void window_size_callback(GLFWwindow* window, int width, int height) {
		Event::CreateNewEvent(EventType::WindowResize, [width, height]() {
			//LOG_TRACE("Window Resized! {}, {}", width, height)
		});
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	WindowManager& WindowManager::GetInstance() {
		static WindowManager* m_Instance = new WindowManager;
		return *m_Instance;
	}

	/*static GLuint openGLShaderProgram;*/

	GLfloat vertices[] =
	{
	   -0.5f, -0.5f, 0.0f, // 0
		0.5f, -0.5f, 0.0f, // 1
		0.5f,  0.5f, 0.0f, // 2
	   -0.5f,  0.5f, 0.0f, // 3

	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<graphics::opengl::Shader> shader;
	std::shared_ptr<graphics::opengl::VertexArray> vArray;
	std::shared_ptr<graphics::opengl::VertexBuffer> vBuffer;
	std::shared_ptr<graphics::opengl::VertexBufferLayout> vLayout;
	std::shared_ptr<graphics::opengl::ElementBuffer> eBuffer;

	void WindowManager::Initialize() {

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

		glfwSwapInterval(1);

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

		shader = std::make_shared<graphics::opengl::Shader>("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
		vArray = std::make_shared<graphics::opengl::VertexArray>();
		vBuffer = std::make_shared<graphics::opengl::VertexBuffer>(vertices, sizeof(vertices));
		vLayout = std::make_shared<graphics::opengl::VertexBufferLayout>();
		eBuffer = std::make_shared<graphics::opengl::ElementBuffer>(indices, sizeof(indices));


		vLayout->Push<GLfloat>(3);
		vArray->AddBuffer(*vBuffer, *vLayout);

		shader->Unbind();
		vArray->Unbind();
		vBuffer->Unbind();
		eBuffer->Unbind();
		
	}

	static float r = 0.0f;
	static float g = 0.0f;
	static float b = 0.0f;

	static float rinc = 0.05f;
	static float binc = 0.10f;
	static float ginc = 0.15f;

	void WindowManager::Update() {
		
		if (glfwWindowShouldClose(m_Window)) {
			Event::CreateNewEvent(EventType::WindowClose, []() {
				Engine::GetInstance().Shutdown();
				});
		}

		shader->Bind();
		shader->SetUniform4f("uColor", r, g, b, 1.0f);

		glClearColor(0.07f, .13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		core::RenderManager::GetInstance().Draw(*vArray, *eBuffer, *shader);

		if (r > 1.f)
			rinc = -0.05f;
		else if (r < 0.0f)
			rinc = 0.05f;

		if (g > 1.f)
			ginc = -0.10f;
		else if (g < 0.0f)
			ginc = 0.10f;

		if (b > 1.f)
			binc = -0.15f;
		else if (b < 0.0f)
			binc = 0.15f;

		r += rinc;
		g += ginc;
		b += binc;

		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		
	}

	void WindowManager::Shutdown() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}