#pragma once

#include <string>

using namespace std;

namespace Crystal
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const string& filepath);
		static Shader* Create(const string& vertexSource, const string& fragmentSource);
	};
}
	
