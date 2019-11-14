#pragma once

#include "Shader.h"

using namespace std;

namespace Crystal
{
	class ShaderLibrary
	{
	public:
		void Add(const string& name, const Reference<Shader>& shader);
		void Add(const Reference<Shader>& shader);

		Reference<Shader> Load(const string& filepath);
		Reference<Shader> Load(const string& name, const string& filepath);

		Reference<Shader> Get(const string& name);

		bool Exists(const string& name) const;
	private:
		unordered_map<std::string, Reference<Shader>> shaders;

	};
}
