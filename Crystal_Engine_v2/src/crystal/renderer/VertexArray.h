#pragma once

#include <memory>
#include <vector>
#include "crystal/renderer/VertexBuffer.h"
#include "crystal/renderer/IndexBuffer.h"

using namespace std;

namespace Crystal
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const vector<shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}