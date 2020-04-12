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
	};

	struct Renderer2DData
	{
		const uint32_t MAX_QUADS = 10000;
		const uint32_t MAX_VERTICES = MAX_QUADS * 4;
		const uint32_t MAX_INDICES = MAX_QUADS * 6;

		Reference<VertexArray> quadVertexArray;
		Reference<VertexBuffer> quadVertexBuffer;
		Reference<Shader> textureShader;
		Reference<Texture2D> whiteTexture;

		uint32_t quadIndexCount = 0;
		QuadVertex* quadVertexBufferBase = nullptr;
		QuadVertex* quadVertexBufferPointer = nullptr;
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

		data.textureShader = Shader::Create("assets/shaders/Texture.glsl");
		data.textureShader->Bind();
		data.textureShader->SetInt("u_texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		CRYSTAL_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		CRYSTAL_PROFILE_FUNCTION();

		data.textureShader->Bind();
		data.textureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());

		data.quadIndexCount = 0;
		data.quadVertexBufferPointer = data.quadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		CRYSTAL_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)data.quadVertexBufferPointer - (uint8_t*)data.quadVertexBufferBase;
		data.quadVertexBuffer->SetData(data.quadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(data.quadVertexArray, data.quadIndexCount);
	}

	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const vec4& color)
	{
		CRYSTAL_PROFILE_FUNCTION();

		data.quadVertexBufferPointer->position = position;
		data.quadVertexBufferPointer->color = color;
		data.quadVertexBufferPointer->textureCoordinates = { 0.0f, 0.0f };
		data.quadVertexBufferPointer++;

		data.quadVertexBufferPointer->position = { position.x + size.x, position.y, position.z };
		data.quadVertexBufferPointer->color = color;
		data.quadVertexBufferPointer->textureCoordinates = { 1.0f, 0.0f };
		data.quadVertexBufferPointer++;

		data.quadVertexBufferPointer->position = { position.x + size.x, position.y + size.y, position.z };
		data.quadVertexBufferPointer->color = color;
		data.quadVertexBufferPointer->textureCoordinates = { 1.0f, 1.0f };
		data.quadVertexBufferPointer++;

		data.quadVertexBufferPointer->position = { position.x, position.y + size.y, position.z };
		data.quadVertexBufferPointer->color = color;
		data.quadVertexBufferPointer->textureCoordinates = { 0.0f, 1.0f };
		data.quadVertexBufferPointer++;

		data.quadIndexCount += 6;

		data.whiteTexture->Bind();

		/*mat4 transform = translate(mat4(1.0f), position) * scale(mat4(1.0f), { size.x, size.y, 1.0f });
		data.textureShader->SetFloat4("u_color", color);
		data.textureShader->SetMat4("u_transform", transform);

		data.quadVertexArray->Bind();*/

		RenderCommand::DrawIndexed(data.quadVertexArray);
	}
	
	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const vec4& color)
	{
		CRYSTAL_PROFILE_FUNCTION();

		data.whiteTexture->Bind();

		mat4 transform = translate(mat4(1.0f), position) * rotate(mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * scale(mat4(1.0f), { size.x, size.y, 1.0f });
		data.textureShader->SetFloat4("u_color", color);
		data.textureShader->SetMat4("u_transform", transform);

		data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(data.quadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const vec3& position, const vec2& size, float rotation, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		CRYSTAL_PROFILE_FUNCTION();

		texture->Bind();

		mat4 transform = translate(mat4(1.0f), position) * rotate(mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * scale(mat4(1.0f), { size.x, size.y, 1.0f });
		data.textureShader->SetFloat4("u_color", tintColor);
		data.textureShader->SetMat4("u_transform", transform);
		data.textureShader->SetFloat("u_tilingFactor", tilingFactor);

		data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(data.quadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const vec2& position, const vec2& size, float rotation, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const Reference<Texture2D>& texture, float tilingFactor, const vec4& tintColor)
	{
		CRYSTAL_PROFILE_FUNCTION();

		texture->Bind();

		mat4 transform = translate(mat4(1.0f), position) * scale(mat4(1.0f), { size.x, size.y, 1.0f });
		data.textureShader->SetFloat4("u_color", tintColor);
		data.textureShader->SetMat4("u_transform", transform);
		data.textureShader->SetFloat("u_tilingFactor", tilingFactor);

		data.quadVertexArray->Bind();
		RenderCommand::DrawIndexed(data.quadVertexArray);
	}
}