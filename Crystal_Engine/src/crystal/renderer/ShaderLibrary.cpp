#include "crystalpch.h"
#include "ShaderLibrary.h"

namespace Crystal
{
	void ShaderLibrary::Add(const string& name, const Reference<Shader>& shader)
	{
		CRYSTAL_CORE_ASSERT(!Exists(name), "Shader already exists!");
		shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Reference<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Reference<Shader> Crystal::ShaderLibrary::Load(const string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Reference<Shader> Crystal::ShaderLibrary::Load(const string& name, const string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Reference<Shader> Crystal::ShaderLibrary::Get(const string& name)
	{
		CRYSTAL_CORE_ASSERT(Exists(name), "Shader not found");
		return shaders[name];
	}

	bool Crystal::ShaderLibrary::Exists(const string& name) const
	{
		return shaders.find(name) != shaders.end();
	}
}