#pragma once

#include <cstdint>

#include "crystal/renderer/BufferLayout.h"

namespace Crystal
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		static Reference<VertexBuffer> Create(uint32_t size);
		static Reference<VertexBuffer> Create(float* vertices, uint32_t size);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
	};
}