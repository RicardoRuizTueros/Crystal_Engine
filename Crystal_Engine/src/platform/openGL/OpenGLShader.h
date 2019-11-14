#pragma once

#include "crystal/renderer/Shader.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

typedef unsigned int GLenum;

namespace Crystal
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const string& filepath);
		OpenGLShader(const string& name, const string& filepath);
		OpenGLShader(const string& name, const string& vertexSource, const string& fragmentSource);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		virtual const string& GetName() const override { return name; }

		void UploadUniformInt(const string& name, int value);

		void UploadUniformFloat(const string& name, float value);
		void UploadUniformFloat2(const string& name, const vec2& vector);
		void UploadUniformFloat3(const string& name, const vec3& vector);
		void UploadUniformFloat4(const string& name, const vec4& vector);

		void UploadUniformMat3(const string& name, const mat3& matrix);
		void UploadUniformMat4(const string& name, const mat4& matrix);

	private:
		uint32_t rendererID;
		string name;

		string ReadFile(const string& filepath);
		unordered_map<GLenum, string> Preprocess(const string& source);
		void Compile(const unordered_map<GLenum, string>& shaderSources);
	};
}

