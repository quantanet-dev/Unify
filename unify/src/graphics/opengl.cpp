#include "pch/un2pch.h"
#include "opengl.h"
#include "glad/gl.h"
#include "log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace unify::graphics::opengl {

	std::string Shader::ReadFile(const char* filepath) {
		std::ifstream file(filepath);
		if (file) {
			std::stringstream ss;
			ss << file.rdbuf();
			std::string content = ss.str();
			return content;
		}
		LOG_ERROR("Can't open shader file!");
		return "";
	}

	GLuint Shader::CompileShader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath) {

		std::string vertexCode = ReadFile(vertexShaderFilepath);
		std::string fragmentCode = ReadFile(fragmentShaderFilepath);
		const char* vertexSource = vertexCode.c_str();
		const char* fragmentSource = fragmentCode.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);

		GLuint shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgram;
	}


	Shader::Shader(const char* vertexShaderFilepath, const char* fragmentShaderFilepath) : m_RendererID(0) {
		m_RendererID = CompileShader(vertexShaderFilepath, fragmentShaderFilepath);
	}

	Shader::~Shader() {
		glDeleteProgram(m_RendererID);
	}

	Texture::Texture(const char* filepath) : m_RendererID(0), m_Filepath(filepath), m_LocalBuffer(NULL), m_Width(0), m_Height(0), m_BPP(0) {
		
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(filepath, &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		
		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_LocalBuffer) {
			stbi_image_free(m_LocalBuffer);
		}
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::Bind(GLuint slot) const {
		glActiveTexture(GL_TEXTURE + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Texture::Unbind() const {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Shader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const char* uniformName, int v0) {
		GLuint location = GetUniformLocation(uniformName);
		glUniform1i(location, v0);
	}

	void Shader::SetUniform4f(const char* uniformName, float v0, float v1, float v2, float v3) {
		GLuint location = GetUniformLocation(uniformName);
		glUniform4f(location, v0, v1, v2, v3);
	}

	void Shader::SetUniformMat4f(const char* uniformName, const glm::mat4& matrix) {
		GLuint location = GetUniformLocation(uniformName);
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	GLint Shader::GetUniformLocation(const char*& uniformName) {
		GLint location = glGetUniformLocation(m_RendererID, uniformName);
		if (location == -1) {
			std::cout << "Warning: uniform " << uniformName << " doesn't exist\n";
		}
		return location;
	}

	// Vertex Array Buffer //

	VertexBuffer::VertexBuffer(const void* data, GLuint size)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Element Array Buffer //

	ElementBuffer::ElementBuffer(GLuint* data, GLuint count) : m_Count(count)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	}

	ElementBuffer::~ElementBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void ElementBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void ElementBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// Vertex Array

	VertexArray::VertexArray() : m_RendererID(0)
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vBuffer, const VertexBufferLayout& vLayout)
	{	
		Bind();
		vBuffer.Bind();
		const auto& elements = vLayout.GetElements();
		GLuint offset = 0;
		for (GLuint i = 0; i < elements.size(); i++) {
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, vLayout.GetStride(), (const void*)offset);
			offset += element.count * sizeof(element.type);
		}
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}