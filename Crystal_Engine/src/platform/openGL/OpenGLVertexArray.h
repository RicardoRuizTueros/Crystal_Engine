#pragma once

#include "crystal/renderer/VertexArray.h"

using namespace std;

namespace Crystal
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) override;
		
		virtual const vector<Reference<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers; }
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }

	private:
		uint32_t rendererID;
		uint32_t vertexBufferIndex = 0;
		vector<Reference<VertexBuffer>> vertexBuffers;
		Reference<IndexBuffer> indexBuffer;
	};
}