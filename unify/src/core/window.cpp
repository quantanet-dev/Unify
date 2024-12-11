#include "pch/un2pch.h"
#include "cmath"
#include "window.h"
#include "log.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
//#include "graphics/opengl.h"
#include "core/renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
// IMGUI
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <thread>
#include <chrono>

namespace unify::core {

	bool m_MouseInWindow = false;
	static GLFWwindow* m_Window;
	static int screenWidth = 1280;
	static int screenHeight = 720;

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
		screenWidth = width;
		screenHeight = height;
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

	GLfloat vertices[] =
	{
		-50.0f, -50.0f, 0.0f, 0.0f, // 0
		 50.0f, -50.0f, 1.0f, 0.0f, // 1
		 50.0f,  50.0f, 1.0f, 1.0f, // 2
		-50.0f,  50.0f, 0.0f, 1.0f // 3
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<graphics::opengl::Shader> shader;
	std::shared_ptr<graphics::opengl::Texture> texture;
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
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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

		glfwSetWindowSizeLimits(m_Window, 1280 / 4, 720 / 4, GLFW_DONT_CARE, GLFW_DONT_CARE);
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

		// IMGUI -----------------

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();

		// -----------------------

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shader = std::make_shared<graphics::opengl::Shader>("res/shaders/vertexShader.glsl", "res/shaders/fragmentShader.glsl");
		texture = std::make_shared<graphics::opengl::Texture>("res/textures/UnifyLogo.png");

		vArray = std::make_shared<graphics::opengl::VertexArray>();
		vBuffer = std::make_shared<graphics::opengl::VertexBuffer>(vertices, sizeof(vertices));
		vLayout = std::make_shared<graphics::opengl::VertexBufferLayout>();
		eBuffer = std::make_shared<graphics::opengl::ElementBuffer>(indices, sizeof(indices));


		vLayout->Push<GLfloat>(2);
		vLayout->Push<GLfloat>(2);
		vArray->AddBuffer(*vBuffer, *vLayout);

		shader->Unbind();
		vArray->Unbind();
		vBuffer->Unbind();
		eBuffer->Unbind();

		LOG_INFO("Window Manager Initialized");
	}

	static float r = 0.0f;
	static float g = 0.0f;
	static float b = 0.0f;

	static float rinc = 0.01f;
	static float binc = 0.01f;
	static float ginc = 0.01f;

	glm::mat4 proj = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationB(200, 200, 0);

	void WindowManager::Update() {

		if (glfwWindowShouldClose(m_Window)) {
			Event::CreateNewEvent(EventType::WindowClose, []() {
				Engine::GetInstance().Shutdown();
			});
		}
		else if (!glfwWindowShouldClose(m_Window)) {

			glfwPollEvents();
			glClearColor(0.07f, .13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// (Your code calls glfwPollEvents())
			// ...
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::ShowDemoWindow(); // Show demo window! :)
			// --------------------------------------------------


			texture->Bind();
			shader->SetUniform4f("uColor", r, g, b, 1.0f);
			shader->SetUniform1i("uTexture", 0);

			glm::mat4 modelA = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvpA = proj * view * modelA;
			shader->SetUniformMat4f("uMVP", mvpA);
			core::RenderManager::GetInstance().Draw(*vArray, *eBuffer, *shader);

			glm::mat4 modelB = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvpB = proj * view * modelB;
			shader->SetUniformMat4f("uMVP", mvpB);
			core::RenderManager::GetInstance().Draw(*vArray, *eBuffer, *shader);

			if (r > 1.f)
				rinc = -0.01f;
			else if (r < 0.0f)
				rinc = 0.01f;

			if (g > 1.f)
				ginc = -0.01f;
			else if (g < 0.0f)
				ginc = 0.01f;

			if (b > 1.f)
				binc = -0.01f;
			else if (b < 0.0f)
				binc = 0.01f;

			r += rinc;
			g += ginc;
			b += binc;

			/*ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, (float)screenWidth);
			ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, (float)screenWidth);*/
			// -----------------------------------------------------
			// Rendering
			// (Your code clears your framebuffer, renders your other stuff etc.)
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			// (Your code calls glfwSwapBuffers() etc.)

			glfwSwapBuffers(m_Window);

		}

	}

	void WindowManager::Shutdown() {

		LOG_INFO("Window Manager Shutting Down");

		// IMGUI -----------------
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		// -----------------------
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}