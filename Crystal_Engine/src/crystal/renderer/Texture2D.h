#pragma once

#include "Texture.h"

#include <string>

using namespace std;

namespace Crystal
{
	class Texture2D : public Texture
	{
	public:
		static Reference<Texture2D> Create(uint32_t width, uint32_t height);
		static Reference<Texture2D> Create(const string& path);
	};
}