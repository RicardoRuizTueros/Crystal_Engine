#pragma once

#include "crystal/renderer/Shader.h"
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace Crystal
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const string& vertexSource, const string& fragmentSource);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt(const string& name, int value);

		void UploadUniformFloat(const string& name, float value);
		void UploadUniformFloat2(const string& name, const vec2& vector);
		void UploadUniformFloat3(const string& name, const vec3& vector);
		void UploadUniformFloat4(const string& name, const vec4& vector);

		void UploadUniformMat3(const string& name, const mat3& matrix);
		void UploadUniformMat4(const string& name, const mat4& matrix);

	private:
		uint32_t rendererID;
	};
}

