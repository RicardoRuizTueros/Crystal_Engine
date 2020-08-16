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

		static void Flush();
		static void FlushAndReset();

		static void DrawQuad(const vec2& position, const vec2& size, const vec4& color);
		static void DrawQuad(const vec3& position, const vec2& size, const vec4& color);
		static void DrawQuad(const vec3& position, const vec2& size, const Reference<Texture2D>& texture, float tilingFactor = 1.0f, const vec4& tintColor = vec4(1.0f));
		static void DrawQuad(const vec2& position, const vec2& size, const Reference<Texture2D>& texture, float tilingFactor = 1.0f, const vec4& tintColor = vec4(1.0f));

		static void DrawQuad(const mat4& transform, const vec4& color);
		static void DrawQuad(const mat4& transform, const Reference<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = vec4(1.0f));


		static void DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const vec4& color);
		static void DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const vec4& color);
		static void DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const Reference<Texture2D>& texture, float tilingFactor = 1.0f, const vec4& tintColor = vec4(1.0f));
		static void DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const Reference<Texture2D>& texture, float tilingFactor = 1.0f, const vec4& tintColor = vec4(1.0f));
	
		struct Statistics
		{
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;

			uint32_t GetVertexCount() { return quadCount * 4; }
			uint32_t GetIndexCount() { return quadCount * 6; }
		};

		static void ResetStatistics();
		static Statistics GetStatistics();
	};
}
