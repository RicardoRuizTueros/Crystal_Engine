#pragma once

#include "crystal/renderer/OrthographicCamera.h"
#include "crystal/renderer/Texture2D.h"

using namespace glm;

namespace Crystal
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const vec2& position, const vec2& size, const vec4& color);
		static void DrawQuad(const vec3& position, const vec2& size, const vec4& color);
		static void DrawQuad(const vec2& position, const vec2& size, const Reference<Texture2D>& texture);
		static void DrawQuad(const vec3& position, const vec2& size, const Reference<Texture2D>& texture);
	};
}
