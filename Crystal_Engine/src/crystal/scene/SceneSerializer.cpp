#include "crystalpch.h"
#include "SceneSerializer.h"
#include "crystal/scene/Entity.h"
#include "crystal/scene/Components.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

using namespace YAML;

namespace YAML
{
	template<>
	struct convert<vec3>
	{
		static Node encode(const vec3& vector)
		{
			Node node;

			node.push_back(vector.x);
			node.push_back(vector.y);
			node.push_back(vector.z);
			
			return node;
		}

		static bool decode(const Node& node, vec3& vector)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			vector.x = node[0].as<float>();
			vector.y = node[1].as<float>();
			vector.z = node[2].as<float>();

			return true;
		}

		static Node encode(const vec4& vector)
		{
			Node node;

			node.push_back(vector.x);
			node.push_back(vector.y);
			node.push_back(vector.z);
			node.push_back(vector.w);

			return node;
		}

		static bool decode(const Node& node, vec4& vector)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			vector.x = node[0].as<float>();
			vector.y = node[1].as<float>();
			vector.z = node[2].as<float>();
			vector.w = node[3].as<float>();

			return true;
		}
	};
}

namespace Crystal
{
	SceneSerializer::SceneSerializer(const Reference<Scene>& scene)
	{
		this->scene = scene;
	}
	
	void SceneSerializer::Serialize(const string& filepath)
	{
		Emitter out;
		out << BeginMap;
		out << Key << "Scene" << Value << "Untitled scene";
		out << Key << "Entities" << Value << BeginSeq;
		
		scene->registry.each([&](auto entityID)
		{
			Entity entity = { entityID, scene.get() };

			if (!entity)
				return;

			SerializeEntity(out, entity)
		});

		out << EndSeq;
		out << EndMap;

		ofstream fout(filepath);
		fout << out.c_str();
	}
	
	static void SerializeEntity(Emitter out, Entity entity)
	{
		out << BeginMap;
		out << Key << "EntityID" << Value << "7777"; // Todo: Replace with entity UUID
		
		if (entity.HasComponent<TagComponent>())
		{
			out << Key << "TagComponent";
			out << BeginMap;

			auto& tag = entity.GetComponent<TagComponent>().tag;
			out << Key << "Tag" << Value << tag;
			out << EndMap;
		}

		if (entity.HasComponent<TransformComponent>())
		{
			out << Key << "TranformComponent";
			out << BeginMap;

			auto& transformComponent = entity.GetComponent<TransformComponent>();
			out << Key << "Translation" << Value << transformComponent.translation;
			out << Key << "Rotation" << Value << transformComponent.rotation;
			out << Key << "Scale" << Value << transformComponent.scale;

		}
	}
}
