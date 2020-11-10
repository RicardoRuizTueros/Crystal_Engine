#pragma once

#include "crystal/scene/Scene.h"

namespace Crystal
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Reference<Scene>& scene);

		void Serialize(const string& filepath);
		void SerializeRuntime(const string& filepath);

		void Deserialize(const string& filepath);
		void DeserializeRuntime(const string& filepath);
		
	private:
		Reference<Scene> scene;
	};
	
}
