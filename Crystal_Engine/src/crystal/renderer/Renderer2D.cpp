#include "crystalpch.h"
#include "Renderer2D.h"

#include "crystal/renderer/VertexArray.h"
#include "crystal/renderer/Shader.h"
#include "crystal/renderer/RenderCommand.h"

#include "platform/openGL/OpenGLShader.h"

using namespace std;

namespace Crystal 
{
	struct Renderer2DStorage
	{
		Reference<VertexArray> quadVertexArray;
		Reference<Shader> flatColorShader;
	};

	static Renderer2DStorage* data;

	void Renderer2D::Init()
	{
		data = new Renderer2DStorage;
		data->quadVertexArray = VertexArray::Create();

		float quadVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Reference<VertexBuffer> quadVertexBuffer;
		quadVertexBuffer.reset(VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
		quadVertexBuffer->SetLayout
		({
			{ ShaderDataType::Float3, "a_Position" },
		});

		data->quadVertexArray->AddVertexBuffer(quadVertexBuffer);

		uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Reference<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
		data->quadVertexArray->SetIndexBuffer(squareIndexBuffer);

		data->flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		dynamic_pointer_cast<OpenGLShader>(data->flatColorShader)->Bind();
		dynamic_pointer_cast<OpenGLShader>(data->flatColorShader)->UploadUniformMat4("u_viewProjection", camera.GetViewProjectionMatrix());
		dynamic_pointer_cast<OpenGLShader>(data->flatColorShader)->UploadUniformMat4("u_transform", mat4(1.0f));
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
		dynamic_pointer_cast<OpenGLShader>(data->flatColorShader)->Bind();
		dynamic_pointer_cast<OpenGLShader>(data->flatColorShader)->UploadUniformFloat4("u_color", color);

		data->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(data->quadVertexArray);
	}
}
