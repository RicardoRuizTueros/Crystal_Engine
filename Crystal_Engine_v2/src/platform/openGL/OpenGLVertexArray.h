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
		
		virtual void AddVertexBuffer(const shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const shared_ptr<IndexBuffer>& indexBuffer) override;
		
		virtual const vector<shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers; }
		virtual const shared_ptr<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }

	private:
		uint32_t rendererID;
		vector<shared_ptr<VertexBuffer>> vertexBuffers;
		shared_ptr<IndexBuffer> indexBuffer;
	};
}