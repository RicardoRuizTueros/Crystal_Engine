#pragma once

#include <string>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace Crystal
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const string& name, const int& value) = 0;
		virtual void SetIntArray(const string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const string& name, const float& value) = 0;
		virtual void SetFloat2(const string& name, const vec2& value) = 0;
		virtual void SetFloat3(const string& name, const vec3& value) = 0;
		virtual void SetMat4(const string& name, const mat4& matrix) = 0;
		virtual void SetFloat4(const string& name, const vec4& vector) = 0;
		virtual void SetFloat3(const string& name, const vec3& vector) = 0;

		virtual const string& GetName() const = 0;

		static Reference<Shader> Create(const string& filepath);
		static Reference<Shader> Create(const string& name, const string& vertexSource, const string& fragmentSource);
	};
}
	
