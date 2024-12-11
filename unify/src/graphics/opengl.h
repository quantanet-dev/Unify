#pragma once
#include "pch/un2pch.h"

#include "glad/gl.h"

namespace unify::graphics::opengl {

	class Shader {
	private:
		GLuint m_RendererID;
		// uniform caching
	public:

		GLuint GetRendererID() { return m_RendererID; }

		Shader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform4f(const char* uniformName, float v0, float v1, float v2, float v3);
	private:
		std::string ReadFile(const char* filepath);
		GLuint CompileShader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath);
		GLint GetUniformLocation(const char*& uniformName);
	};

	class VertexBuffer
	{
	private:
		GLuint m_RendererID;
	public:
		
		GLuint GetRendererID() { return m_RendererID; }

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
		
		GLuint GetRendererID() { return m_RendererID; }

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

		GLuint GetRendererID() { return m_RendererID; }

		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vBuffer, const VertexBufferLayout& vLayout);

		void Bind() const;
		void Unbind() const;
	};


}

