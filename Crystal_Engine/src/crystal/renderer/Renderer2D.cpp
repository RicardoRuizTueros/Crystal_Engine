#include "crystalpch.h"
#include "Renderer2D.h"

#include "crystal/renderer/VertexArray.h"
#include "crystal/renderer/Shader.h"
#include "crystal/renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

namespace Crystal 
{
	struct QuadVertex
	{
		vec3 position;
		vec4 color;
		vec2 textureCoordinates;
		float textureIndex;
		float tilingFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t MAX_QUADS = 20000;
		static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
		static const uint32_t MAX_INDICES = MAX_QUADS * 6;
		static const uint32_t MAX_TEXTURE_SLOTS = 32;

		Reference<VertexArray> quadVertexArray;
		Reference<VertexBuffer> quadVertexBuffer;
		Reference<Shader> textureShader;
		Reference<Texture2D> whiteTexture;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPointer = nullptr;
		vec4 quadVertexPositions[4];

		array<Reference<Texture2D>, MAX_TEXTURE_SLOTS> textureSlots;
		uint32_t textureSlotIndex = 1;

		Renderer2D::Statistics statistics;
	};

	static Renderer2DData data;

	void Renderer2D::Init()
	{
		CRYSTAL_PROFILE_FUNCTION();

		data.quadVertexArray = VertexArray::Create();
		data.quadVertexBuffer = VertexBuffer::Create(data.MAX_VERTICES * sizeof(QuadVertex));
		
		data.quadVertexBuffer->SetLayout
		({
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color"},
			{ ShaderDataType::Float2, "a_textureCoordinates" },
			{ ShaderDataType::Float, "a_textureIndex" },
			{ ShaderDataType::Float, "a_tilingFactor" }
		});

		data.quadVertexArray->AddVertexBuffer(data.quadVertexBuffer);

		data.quadVertexBufferBase = new QuadVertex[data.MAX_VERTICES];

		uint32_t* quadIndices = new uint32_t[data.MAX_INDICES];
		uint32_t offset = 0;

		for (uint32_t i = 0; i < data.MAX_INDICES; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Reference<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, data.MAX_INDICES);
		data.quadVertexArray->SetIndexBuffer(quadIndexBuffer);
		delete[] quadIndices;

		data.whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data.whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[data.MAX_TEXTURE_SLOTS];
		for (uint32_t index = 0; index < data.MAX_TEXTURE_SLOTS; index++)
			samplers[index] = index;

		data.textureShader = Shader::Create("assets/shaders/Texture.glsl");
		data.textureShader->Bind();
		data.textureShader->SetIntArray("u_textures", samplers, data.MAX_TEXTURE_SLOTS);

		data.textureSlots[0] = data.whiteTexture;

		data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data.quadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		data.quadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		CRYSTAL_PROFILE_FUNCTION();

		delete data.quadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		CRYSTAL_PROFILE_FUNCTION();

		data.textureShader->Bind();
		data.textureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());

		data.quadIndexCount = 0;
		data.quadVertexBufferPointer = data.quadVertexBufferBase;

		data.textureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		CRYSTAL_PROFILE_FUNCTION();

		uint32_t dataSize = uint32_t ((uint8_t*)data.quadVertexBufferPointer - (uint8_t*)data.quadVertexBufferBase);
		data.quadVertexBuffer->SetData(data.quadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		if (data.quadIndexCount == 0)
			return;

		for (uint32_t index = 0; index < data.textureSlotIndex; index++)
			data.textureSlots[index]->Bind(index);

		RenderCommand::DrawIndexed(data.quadVertexArray, data.quadIndexCount);

		data.statistics.drawCalls++;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();
		
		data.quadIndexCount = 0;
		data.quadVertexBufferPointer = data.quadVertexBufferBase;
		data.textureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const vec4& color)
	{
		CRYSTAL_PROFILE_FUNCTION();

		mat4 transform = translate(mat4(1.0f), position) * scale(mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, color);
	}
	
	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const mat4& transform, const vec4& color)
	{
		CRYSTAL_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;

		const float textureIndex = 0.0f;
		constexpr vec2 textureCoordinates[] = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
		const float tilingFactor = 1.0f;

		if (data.quadIndexCount >= data.MAX_INDICES)
			FlushAndReset();

		for (size_t index = 0; index < quadVertexCount; index++)
		{
			data.quadVertexBufferPointer->position = transform * data.quadVertexPositions[index];
			data.quadVertexBufferPointer->color = color;
			data.quadVertexBufferPointer->textureCoordinates = textureCoordinates[index];
			data.quadVertexBufferPointer->textureIndex = textureIndex;
			data.quadVertexBufferPointer->tilingFactor = tilingFactor;

			data.quadVertexBufferPointer++;
		}

		data.quadIndexCount += 6;

		data.statistics.quadCount++;
	}

	void Renderer2D::DrawQuad(const mat4& transform, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		CRYSTAL_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;

		constexpr vec2 textureCoordinates[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		float textureIndex = 0.0f;

		if (data.quadIndexCount >= data.MAX_INDICES)
			FlushAndReset();

		for (uint32_t index = 1; index < data.textureSlotIndex; index++)
		{
			if (*data.textureSlots[index].get() == *texture.get())
			{
				textureIndex = (float)index;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (data.textureSlotIndex >= Renderer2DData::MAX_TEXTURE_SLOTS)
				FlushAndReset();

			textureIndex = (float)data.textureSlotIndex;
			data.textureSlots[data.textureSlotIndex] = texture;
			data.textureSlotIndex++;
		}

		for (size_t index = 0; index < quadVertexCount; index++)
		{
			data.quadVertexBufferPointer->position = transform * data.quadVertexPositions[index];
			data.quadVertexBufferPointer->color = tintColor;
			data.quadVertexBufferPointer->textureCoordinates = textureCoordinates[index];
			data.quadVertexBufferPointer->textureIndex = textureIndex;
			data.quadVertexBufferPointer->tilingFactor = tilingFactor;

			data.quadVertexBufferPointer++;
		}

		data.quadIndexCount += 6;

		data.statistics.quadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const vec4& color)
	{
		CRYSTAL_PROFILE_FUNCTION();

		mat4 transform = translate(mat4(1.0f), position)
			* rotate(mat4(1.0f), radians(rotation), { 0.0f, 0.0f, 1.0f })
			* scale(mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		CRYSTAL_PROFILE_FUNCTION();

		mat4 transform = translate(mat4(1.0f), position)
			* rotate(mat4(1.0f), radians(rotation), { 0.0f, 0.0f, 1.0f })
			* scale(mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		CRYSTAL_PROFILE_FUNCTION();

		mat4 transform = translate(mat4(1.0f), position) * scale(mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::ResetStatistics()
	{
		memset(&data.statistics, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStatistics()
	{
		return data.statistics;
	}
}