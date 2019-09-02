#include "crystalpch.h"
#include "BufferLayout.h"

namespace Crystal
{
	BufferLayout::BufferLayout()
	{

	}
	
	BufferLayout::BufferLayout(const initializer_list<BufferElement>& elements)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		uint32_t offset = 0;
		stride = 0;

		for (auto& element : elements)
		{
			element.offset = offset;
			offset += element.size;
			stride += element.size;
		}
	}
}