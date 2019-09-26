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

		virtual void AddVertexBuffer(const Reference<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Reference<IndexBuffer>& indexBuffer) = 0;

		virtual const vector<Reference<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Reference<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}