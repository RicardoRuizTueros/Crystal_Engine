#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace Crystal::Math
{
    bool DecomposeTransform(const mat4& transform, vec3& outTranslation, vec3& outRotation, vec3& outScale);
}
