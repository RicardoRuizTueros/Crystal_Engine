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
		
		virtual const string& GetName() const = 0;

		static Reference<Shader> Create(const string& filepath);
		static Reference<Shader> Create(const string& name, const string& vertexSource, const string& fragmentSource);
	};
}
	
