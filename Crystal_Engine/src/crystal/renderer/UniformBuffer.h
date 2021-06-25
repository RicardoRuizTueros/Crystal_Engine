#pragma once

#include "crystal/core/Base.h"

namespace Crystal
{
	class UniformBuffer
	{
	public: 
		virtual ~UniformBuffer() {};
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) = 0;

		static Reference<UniformBuffer> Create(uint32_t size, uint32_t binding);
	};
}
