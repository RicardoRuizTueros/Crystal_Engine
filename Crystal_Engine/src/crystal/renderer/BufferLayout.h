#pragma once

using namespace std;

namespace Crystal
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Matrix3, Matrix4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:
				return 4;
		case ShaderDataType::Float2:
			return 4 * 2;
		case ShaderDataType::Float3:
			return 4 * 3;
		case ShaderDataType::Float4:
			return 4 * 4;
		case ShaderDataType::Matrix3:
			return 4 * 3 * 3;
		case ShaderDataType::Matrix4:
			return 4 * 4 * 4;
		case ShaderDataType::Int:
			return 4;
		case ShaderDataType::Int2:
			return 4 * 2;
		case ShaderDataType::Int3:
			return 4 * 3;
		case ShaderDataType::Int4:
			return 4 * 4;
		case ShaderDataType::Bool:
			return 1;
		}

		CRYSTAL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		
		return 0;
	}

	struct BufferElement
	{
		string name;
		ShaderDataType type;
		uint32_t size;
		size_t offset;
		bool normalized;

		BufferElement() = default;
		
		BufferElement(ShaderDataType type, const string& name, bool normalized = false) :
			name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (type)
			{
			case ShaderDataType::Float:
				return 1;
			case ShaderDataType::Float2:
				return 2;
			case ShaderDataType::Float3:
				return 3;
			case ShaderDataType::Float4:
				return 4;
			case ShaderDataType::Matrix3:
				return 3 * 3;
			case ShaderDataType::Matrix4:
				return 4 * 4;
			case ShaderDataType::Int:
				return 1;
			case ShaderDataType::Int2:
				return 2;
			case ShaderDataType::Int3:
				return 3;
			case ShaderDataType::Int4:
				return 4;
			case ShaderDataType::Bool:
				return 1;
			}

			CRYSTAL_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const initializer_list<BufferElement>& elements);

		uint32_t GetStride() const { return stride; }
		const vector<BufferElement>& GetElements() const { return elements; }

		vector<BufferElement>::iterator begin() { return elements.begin(); }
		vector<BufferElement>::iterator end() { return elements.end(); }
		vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		vector<BufferElement>::const_iterator end() const { return elements.end(); }

	private:
		vector<BufferElement> elements;
		uint32_t stride = 0;

		void CalculateOffsetsAndStride();
	};
}