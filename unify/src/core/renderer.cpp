#include "pch/un2pch.h"
#include "renderer.h"

namespace unify::core {

	RenderManager& RenderManager::GetInstance() {
		static RenderManager* m_Instance = new RenderManager;
		return *m_Instance;
	}

	void RenderManager::Update() {
	}

	void RenderManager::Draw(graphics::opengl::VertexArray& vArray, graphics::opengl::ElementBuffer& eBuffer, graphics::opengl::Shader& shader) {
		
		shader.Bind();
		vArray.Bind();
		eBuffer.Bind();

		glDrawElements(GL_TRIANGLES, eBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	}

	void RenderManager::Initialize() {
	}

	void RenderManager::Shutdown() {
	}

}