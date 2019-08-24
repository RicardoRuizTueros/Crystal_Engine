#pragma once

#include <string>

using namespace std;

namespace Crystal
{
	class Shader
	{
	public:
		Shader(const string& vertexSource, const string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t rendererID;
	};
}
	
