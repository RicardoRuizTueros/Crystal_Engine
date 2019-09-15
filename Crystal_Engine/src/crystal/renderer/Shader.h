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
		Shader(const string& vertexSource, const string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const string& name, const mat4& matrix);

	private:
		uint32_t rendererID;
	};
}
	
