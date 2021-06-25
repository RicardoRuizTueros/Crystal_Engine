#include "crystalpch.h"

#include "platform/openGL/OpenGLShader.h"

#include "crystal/core/Timer.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>


using namespace std;

namespace Crystal
{
	namespace Utils
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

		static const char* GetCacheDirectory()
		{
			// To do: Validation of cache directory
			return "assets/cache/shader/opengl";
		}

		static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:
				return ".cached_opengl.vertex";

			case GL_FRAGMENT_SHADER:
				return ".cached_opengl.fragment";
			}

			CRYSTAL_CORE_ASSERT(false, "Unsupported stage!");
			return "";
		}

		static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:
				return ".cached_vulkan.vertex";

			case GL_FRAGMENT_SHADER:
				return ".cached_vulkan.fragment";
			}

			CRYSTAL_CORE_ASSERT(false, "Unsupported stage!");
			return "";
		}

		static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:
				return shaderc_glsl_vertex_shader;

			case GL_FRAGMENT_SHADER:
				return shaderc_glsl_fragment_shader;
			}

			CRYSTAL_CORE_ASSERT(false, "Unsupported stage!");
			return (shaderc_shader_kind)0;
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:
				return "GL_VERTEX_SHADER";

			case GL_FRAGMENT_SHADER:
				return "GL_FRAGMENT_SHADER";
			}

			CRYSTAL_CORE_ASSERT(false, "Unsupported stage!");
			return nullptr;
		}

		static void CreateCacheDirectoryIfNeeded()
		{
			string cacheDirectory = GetCacheDirectory();

			if (!filesystem::exists(cacheDirectory))
				filesystem::create_directories(cacheDirectory);
		}
	}

	OpenGLShader::OpenGLShader(const string& filepath): filepath(filepath)
	{
		CRYSTAL_PROFILE_FUNCTION();

		Utils::CreateCacheDirectoryIfNeeded();

		string source = ReadFile(filepath);
		auto shaderSources = Preprocess(source);
		{
			Timer timer;

			CompileOrGetVulkanBinaries(shaderSources);
			CompileOrGetOpenGLBinaries();
			CreateProgram();
			CRYSTAL_CORE_WARNING("Shader creation in {0} ms", timer.ElapsedMilliSeconds());
		}

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const string& name, const string& vertexSource, const string& fragmentSource) : name(name)
	{
		CRYSTAL_PROFILE_FUNCTION();

		unordered_map<GLenum, string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;

		CompileOrGetVulkanBinaries(sources);
		CompileOrGetOpenGLBinaries();
		CreateProgram();;
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
			CRYSTAL_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", endOfLine);
			position = source.find(typeToken, nextLinePos);
			shaderSources[Utils::ShaderTypeFromString(type)] = (position == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, position - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::CompileOrGetVulkanBinaries(const unordered_map<GLenum, string>& shaderSources)
	{
		CRYSTAL_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);

		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		auto& shaderData = vulkanSPIRV;
		shaderData.clear();
		for (auto&& [stage, source] : shaderSources)
		{
			filesystem::path shaderFilePath = filepath;
			filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() +
				Utils::GLShaderStageCachedVulkanFileExtension(stage));

			ifstream inStream(cachedPath, ios::in | ios::binary);
			if (inStream.is_open())
			{
				inStream.seekg(0, ios::end);
				auto size = inStream.tellg();
				inStream.seekg(0, ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				inStream.read((char*)data.data(), size);
			}
			else
			{
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source,
					Utils::GLShaderStageToShaderC(stage), filepath.c_str(), options);

				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					CRYSTAL_CORE_ERROR(module.GetErrorMessage());
					CRYSTAL_CORE_ASSERT(false);
				}

				shaderData[stage] = vector<uint32_t>(module.cbegin(), module.cend());

				ofstream outStream(cachedPath, ios::out | ios::binary);
				if (outStream.is_open())
				{
					auto& data = shaderData[stage];
					outStream.write((char*)data.data(), data.size() * sizeof(uint32_t));
					outStream.flush();
					outStream.close();
				}
			}
		}

		for (auto&& [stage, data] : shaderData)
			Reflect(stage, data);
	}

	void OpenGLShader::CompileOrGetOpenGLBinaries()
	{
		CRYSTAL_PROFILE_FUNCTION();

		auto& shaderData = openGLSPIRV;
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		shaderData.clear();
		openGLSourceCode.clear();
		for (auto&& [stage, spirv] : vulkanSPIRV)
		{
			filesystem::path shaderFilePath = filepath;
			filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() +
				Utils::GLShaderStageCachedVulkanFileExtension(stage));

			ifstream inStream(cachedPath, ios::in | ios::binary);
			if (inStream.is_open())
			{
				inStream.seekg(0, ios::end);
				auto size = inStream.tellg();
				inStream.seekg(0, ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				inStream.read((char*)data.data(), size);
			}
			else
			{
				spirv_cross::CompilerGLSL glslCompiler(spirv);
				openGLSourceCode[stage] = glslCompiler.compile();

				auto& source = openGLSourceCode[stage];
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source,
					Utils::GLShaderStageToShaderC(stage), filepath.c_str());

				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					CRYSTAL_CORE_ERROR(module.GetErrorMessage());
					CRYSTAL_CORE_ASSERT(false);
				}

				shaderData[stage] = vector<uint32_t>(module.cbegin(), module.cend());

				ofstream outStream(cachedPath, ios::out | ios::binary);
				if (outStream.is_open())
				{
					auto& data = shaderData[stage];
					outStream.write((char*)data.data(), data.size() * sizeof(uint32_t));
					outStream.flush();
					outStream.close();
				}
			}
		}
	}

	void OpenGLShader::CreateProgram()
	{
		GLuint program = glCreateProgram();
		
		vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : openGLSPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}


		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			CRYSTAL_CORE_ERROR("Shader linking failed ({0}):\n{1}", filepath, infoLog.data());

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);
		}

		for (auto id : shaderIDs) 
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		rendererID = program;
	}

	void OpenGLShader::Reflect(GLenum stage, const vector<uint32_t>& shaderData)
	{
		spirv_cross::Compiler compiler(shaderData);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		CRYSTAL_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", Utils::GLShaderStageToString(stage), filepath);
		CRYSTAL_CORE_TRACE("OpenGLShader::Reflect - {0} Uniform buffers size", resources.uniform_buffers.size());
		CRYSTAL_CORE_TRACE("OpenGLShader::Reflect - {0} Resources size", resources.sampled_images.size());
		CRYSTAL_CORE_TRACE("OpenGLShader::Reflect - {0} Resources", resources.sampled_images.size());
		

		CRYSTAL_CORE_TRACE("OpenGLShader::Reflect - Uniform buffers:");

		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);

			int memberCount = bufferType.member_types.size();

			CRYSTAL_CORE_TRACE("{0}", resource.name);
			CRYSTAL_CORE_TRACE("Size = {0}", bufferSize);
			CRYSTAL_CORE_TRACE("Binding = {0}", binding);
			CRYSTAL_CORE_TRACE("Members = {0}", memberCount);
		}
	}
}
