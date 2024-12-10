#pragma once

#include "glad/gl.h"

namespace unify::graphics::opengl {

	void CreateShaderProgram(const char* vertexFilepath, const char* fragmentFilepath, GLuint& shaderProgram);

	class VertexBuffer
	{
	private:
		GLuint m_RendererID;
	public:
		VertexBuffer(const void* data, GLuint size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const ;
	};

	class ElementBuffer
	{
	private:
		GLuint m_RendererID;
		GLuint m_Count;
	public:
		ElementBuffer(GLuint* data, GLuint count);
		~ElementBuffer();

		void Bind() const;
		void Unbind() const;

		inline GLuint GetCount() const { return m_Count; }
	};

	struct VertexBufferLayoutElement {
		GLuint type;
		GLuint count;
		GLuint normalized;
	};

	class VertexBufferLayout {
	private:
		std::vector<VertexBufferLayoutElement> m_Elements;
		GLuint m_Stride;
	public:
		VertexBufferLayout() : m_Stride(0) {};

		template<typename T>
		void Push(GLuint count) {
			/*static_assert(GL_FALSE);*/
		}

		template<>
		void Push<GLfloat>(GLuint count) {
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += sizeof(GLfloat) * count;
		}

		template<>
		void Push<GLuint>(GLuint count) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += sizeof(GLuint) * count;
		}

		template<>
		void Push<GLubyte>(GLuint count) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_Stride += sizeof(GLubyte) * count;
		}

		inline const std::vector<VertexBufferLayoutElement> GetElements() const { return m_Elements; }
		inline GLuint GetStride() const { return m_Stride; }
	};

	class VertexArray {
	private:
		GLuint m_RendererID;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vBuffer, const VertexBufferLayout& vLayout);

		void Bind() const;
		void Unbind() const;
	};


}

