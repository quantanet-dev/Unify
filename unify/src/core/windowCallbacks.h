#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "log.h"
#include "events.h"

namespace unify::core {
	bool m_MouseInWindow = false;

	void cursor_enter_callback(GLFWwindow* window, int entered) {
		(entered) ? m_MouseInWindow = true : m_MouseInWindow = false;
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		if (m_MouseInWindow) {
			Event::CreateEvent(EventType::MouseMoved, [xpos, ypos]() {
				//LOG_TRACE("Mouse Moved! {}, {}", xpos, ypos)
			});
		}
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
		Event::CreateEvent(EventType::MouseScrolled, [xoffset, yoffset]() {
			//LOG_TRACE("Mouse Scrolled! {}, {}", xoffset, yoffset)
		});
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		switch (action) {
		case GLFW_PRESS:
			Event::CreateEvent(EventType::MouseMoved, [button]() {
				//LOG_TRACE("Mouse Button Pressed! {}", button)
			});
			break;
		case GLFW_RELEASE:
			Event::CreateEvent(EventType::MouseMoved, [button]() {
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
			Event::CreateEvent(EventType::KeyPressed, [key, scancode]() {
				//LOG_TRACE("Key Pressed! {}, {}", key, scancode)
			});
			break;
		case GLFW_RELEASE:
			Event::CreateEvent(EventType::KeyReleased, [key, scancode]() {
				//LOG_TRACE("Key Released! {}, {}", key, scancode)
			});
			break;
		default:
			break;
		}
	}

	void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
		Event::CreateEvent(EventType::WindowMove, [xpos, ypos]() {
			//LOG_TRACE("Window Moved! {}, {}", xpos, ypos)
		});
	}

	void window_focus_callback(GLFWwindow* window, int focused) {
		if (focused)
		{
			Event::CreateEvent(EventType::WindowFocus, []() {
				//LOG_TRACE("Window Focused!")
			});
		}
		else
		{
			Event::CreateEvent(EventType::WindowUnfocus, []() {
				//LOG_TRACE("Window Unfocused!")
			});
		}
	}

	void window_size_callback(GLFWwindow* window, int width, int height) {
		Event::CreateEvent(EventType::WindowResize, [width, height]() {
			//LOG_TRACE("Window Resized! {}, {}", width, height)
		});
	}

}