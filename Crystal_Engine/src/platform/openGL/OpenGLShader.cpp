#include "crystalpch.h"

#include "platform/openGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace Crystal
{
	static GLenum ShaderTypeFromString(const string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		CRYSTAL_CORE_ASSERT(false, "Unknown type shader!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const string& filepath) 
	{
		CRYSTAL_PROFILE_FUNCTION();

		string source = ReadFile(filepath);
		auto shaderSources = Preprocess(source);
		Compile(shaderSources);

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const string& name, const string& filepath) : name(name)
	{
		CRYSTAL_PROFILE_FUNCTION();

		string source = ReadFile(filepath);
		auto shaderSources = Preprocess(source);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const string& name, const string& vertexSource, const string& fragmentSource) : name(name)
	{
		CRYSTAL_PROFILE_FUNCTION();

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			CRYSTAL_CORE_ERROR("{0}", infoLog.data());
			CRYSTAL_CORE_ASSERT(false, "Vertex shader compilation failure!");

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			CRYSTAL_CORE_ERROR("{0}", infoLog.data());
			CRYSTAL_CORE_ASSERT(false, "Fragment shader compilation failure!");

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		rendererID = glCreateProgram();
		GLuint program = rendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CRYSTAL_CORE_ERROR("{0}", infoLog.data());
			CRYSTAL_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		CRYSTAL_PROFILE_FUNCTION();

		glDeleteProgram(rendererID);
	}

	void OpenGLShader::Bind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glUseProgram(rendererID);
	}

	void OpenGLShader::Unbind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const string& name, const int& value)
	{
		CRYSTAL_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const string& name, int* values, uint32_t count)
	{
		CRYSTAL_PROFILE_FUNCTION();

		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const string& name, const float& value)
	{
		CRYSTAL_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const string& name, const vec2& value)
	{
		CRYSTAL_PROFILE_FUNCTION();

		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const string& name, const vec3& vector)
	{
		CRYSTAL_PROFILE_FUNCTION();

		UploadUniformFloat3(name, vector);
	}

	void OpenGLShader::SetFloat4(const string& name, const vec4& vector)
	{
		CRYSTAL_PROFILE_FUNCTION();

		UploadUniformFloat4(name, vector);
	}

	void OpenGLShader::SetMat4(const string& name, const mat4& matrix)
	{
		CRYSTAL_PROFILE_FUNCTION();

		UploadUniformMat4(name, matrix);
	}

	void OpenGLShader::UploadUniformInt(const string& name, int value)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const string& name, float value)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const string& name, const vec2& vector)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::UploadUniformFloat3(const string& name, const vec3& vector)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformFloat4(const string& name, const vec4& vector)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::UploadUniformMat3(const string& name, const mat3& matrix)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const string& name, const mat4& matrix)
	{
		GLint location = glGetUniformLocation(rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(matrix));
	}

	string OpenGLShader::ReadFile(const string& filepath)
	{
		CRYSTAL_PROFILE_FUNCTION();

		string result;
		ifstream filestream(filepath, ios::in | ios::binary);

		if (filestream)
		{
			filestream.seekg(0, ios::end);

			size_t size = filestream.tellg();

			if (size != -1)
			{
				result.resize(size);
				filestream.seekg(0, ios::beg);
				filestream.read(&result[0], size);
			}
			else
			{
				CRYSTAL_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			CRYSTAL_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}
	unordered_map<GLenum, string> OpenGLShader::Preprocess(const string& source)
	{
		CRYSTAL_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t position = source.find(typeToken, 0);
		while (position != std::string::npos)
		{
			size_t endOfLine = source.find_first_of("\r\n", position);
			size_t begin = position + typeTokenLength + 1;
			std::string type = source.substr(begin, endOfLine - begin);
			CRYSTAL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", endOfLine);
			position = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = (position == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, position - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const unordered_map<GLenum, string>& shaderSources)
	{
		CRYSTAL_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		CRYSTAL_CORE_ASSERT(shaderSources.size() > 2, "We only support 2 shaders");
		array<GLenum, 2> glShadersIDs;
		int glShaderIDIndex = 0;

		for (auto& keyValue : shaderSources)
		{
			GLenum type = keyValue.first;
			const GLchar* source = keyValue.second.c_str();

			GLuint shader = glCreateShader(type);

			glShaderSource(shader, 1, &source, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				CRYSTAL_CORE_ERROR("{0}", infoLog.data());
				CRYSTAL_CORE_ASSERT(false, "Shader compilation failed!");
				break;
			}

			glAttachShader(program, shader);
			glShadersIDs[glShaderIDIndex++] = shader;
		}

		rendererID = program;

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShadersIDs)
				glDeleteShader(id);

			CRYSTAL_CORE_ERROR("{0}", infoLog.data());
			CRYSTAL_CORE_ASSERT(false, "Shader link error!");
			return;
		}

		for (auto id : glShadersIDs) {
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}
}
