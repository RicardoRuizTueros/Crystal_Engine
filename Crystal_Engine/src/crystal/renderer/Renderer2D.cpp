#include "crystalpch.h"
#include "Renderer2D.h"

#include "crystal/renderer/VertexArray.h"
#include "crystal/renderer/Shader.h"
#include "crystal/renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

namespace Crystal 
{
	struct Renderer2DStorage
	{
		Reference<VertexArray> quadVertexArray;
		Reference<Shader> textureShader;
		Reference<Texture2D> whiteTexture;
	};

	static Renderer2DStorage* data;

	void Renderer2D::Init()
	{
		data = new Renderer2DStorage;
		data->quadVertexArray = VertexArray::Create();

		float quadVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Reference<VertexBuffer> quadVertexBuffer = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVertexBuffer->SetLayout
		({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_textureCoordinates" },

		});

		data->quadVertexArray->AddVertexBuffer(quadVertexBuffer);

		uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Reference<IndexBuffer> squareIndexBuffer = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		data->quadVertexArray->SetIndexBuffer(squareIndexBuffer);

		data->whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		data->textureShader = Shader::Create("assets/shaders/Texture.glsl");
		data->textureShader->Bind();
		data->textureShader->SetInt("u_texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		data->textureShader->Bind();
		data->textureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const vec4& color)
	{
		data->whiteTexture->Bind();

		mat4 transform = translate(mat4(1.0f), position) * /* rotation - to do */ scale(mat4(1.0f), { size.x, size.y, 1.0f });
		data->textureShader->SetFloat4("u_color", color);
		data->textureShader->SetMat4("u_transform", transform);

		data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(data->quadVertexArray);
	}
	
	void Renderer2D::DrawQuad(const vec2& position, const vec2& size, const Reference<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	
	void Renderer2D::DrawQuad(const vec3& position, const vec2& size, const Reference<Texture2D>& texture)
	{
		texture->Bind();

		mat4 transform = translate(mat4(1.0f), position) * /* rotation - to do*/ scale(mat4(1.0f), { size.x, size.y, 1.0f });
		data->textureShader->SetFloat4("u_color", vec4(1.0f));
		data->textureShader->SetMat4("u_transform", transform);

		data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(data->quadVertexArray);
	}
}