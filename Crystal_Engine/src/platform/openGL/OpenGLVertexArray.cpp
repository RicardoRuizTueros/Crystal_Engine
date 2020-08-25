#include "crystalpch.h"

#include "platform/openGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Crystal
{
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:
			return GL_FLOAT;
		case ShaderDataType::Float2:
			return GL_FLOAT;
		case ShaderDataType::Float3:
			return GL_FLOAT;
		case ShaderDataType::Float4:
			return GL_FLOAT;
		case ShaderDataType::Matrix3:
			return GL_FLOAT;
		case ShaderDataType::Matrix4:
			return GL_FLOAT;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::Int2:
			return GL_INT;
		case ShaderDataType::Int3:
			return GL_INT;
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown ShaderDataType!");

		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		CRYSTAL_PROFILE_FUNCTION();

		 glGenVertexArrays(1, &rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		CRYSTAL_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer)
	{
		CRYSTAL_PROFILE_FUNCTION();

		CRYSTAL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

		glBindVertexArray(rendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout)
		{
			switch (element.type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{

				glEnableVertexAttribArray(vertexBufferIndex);
				glVertexAttribPointer(
					vertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset
				);

				vertexBufferIndex++;

				break;
			}

			case ShaderDataType::Matrix3:
			case ShaderDataType::Matrix4:
			{
				uint8_t count = element.GetComponentCount();
				
				for (uint8_t index = 0; index < count; index++)
				{
					glEnableVertexAttribArray(vertexBufferIndex);
					glVertexAttribPointer(
						vertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.offset + sizeof(float) * count * index)
					);
					glVertexAttribDivisor(vertexBufferIndex, 1);
					vertexBufferIndex++;
				}

				break;
			}
			default:
				CRYSTAL_CORE_ASSERT(false, "Unknown ShaderDataType!");

			}
		}

		vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer)
	{
		CRYSTAL_PROFILE_FUNCTION();

		glBindVertexArray(rendererID);
		indexBuffer->Bind();
		this->indexBuffer = indexBuffer;
	}
}

