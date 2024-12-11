#pragma once

#include "graphics/opengl.h"
#include "core.h"


namespace unify::core {

	class RenderManager : public IManager {
	public:
		static RenderManager& GetInstance();

		void Initialize() override;
		void Update() override;
		void Shutdown() override;

		RenderManager(const RenderManager&) = delete;
		RenderManager& operator=(const RenderManager&) = delete;

		static void Draw(graphics::opengl::VertexArray& vArray, graphics::opengl::ElementBuffer& eBuffer, graphics::opengl::Shader& shader);
	private:

		RenderManager() = default;
		~RenderManager() = default;

	};

}