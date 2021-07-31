#type vertex
#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textureCoordinates;
layout(location = 3) in float a_textureIndex;
layout(location = 4) in float a_tilingFactor;
layout(location = 5) in int a_entityID;

layout(std 140, binding = 0) uniform Camera
{
	mat4 u_viewProjection;
}

struct VertexOutput
{
	vec4 color;
	vec2 textureCoordinates;
	float textureIndex;
	float tilingFactor;
}

layout(location = 0) out VertexOutput vertexOutput;
layout(location = 4) out flat int v_entityID;

void main()
{
	vertexOutput.color = a_color;
	vertexOutput.textureCoordinates = a_textureCoordinates;
	vertexOutput.textureIndex = a_textureIndex;
	vertexOutput.tilingFactor = a_tilingFactor;
	vertexOutput.entityID = a_entityID;
	gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;
layout(location = 1) out int entityID;

struct VertexOutput
{
	vec4 color;
	vec2 textureCoordinates;
	float textureIndex;
	float tilingFactor;
}

layout(location = 0) in VertexOutput fragmentInput;
layout(location = 4) in flat int entityID;

layout(binding = 0) uniform sampler2D u_textures[32];

void main()
{
	vec4 textureColor = fragmentInput.color;

	switch(int(fragmentInput.textureIndex))
	{
		case 0: textureColor *= texture(u_textures[0], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 1: textureColor *= texture(u_textures[1], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 2: textureColor *= texture(u_textures[2], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 3: textureColor *= texture(u_textures[3], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 4: textureColor *= texture(u_textures[4], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 5: textureColor *= texture(u_textures[5], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 6: textureColor *= texture(u_textures[6], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 7: textureColor *= texture(u_textures[7], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 8: textureColor *= texture(u_textures[8], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 9: textureColor *= texture(u_textures[9], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 10: textureColor *= texture(u_textures[10], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 11: textureColor *= texture(u_textures[11], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 12: textureColor *= texture(u_textures[12], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 13: textureColor *= texture(u_textures[13], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 14: textureColor *= texture(u_textures[14], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 15: textureColor *= texture(u_textures[15], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 16: textureColor *= texture(u_textures[16], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 17: textureColor *= texture(u_textures[17], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 18: textureColor *= texture(u_textures[18], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 19: textureColor *= texture(u_textures[19], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 20: textureColor *= texture(u_textures[20], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 21: textureColor *= texture(u_textures[21], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 22: textureColor *= texture(u_textures[22], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 23: textureColor *= texture(u_textures[23], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 24: textureColor *= texture(u_textures[24], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 25: textureColor *= texture(u_textures[25], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 26: textureColor *= texture(u_textures[26], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 27: textureColor *= texture(u_textures[27], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 28: textureColor *= texture(u_textures[28], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 29: textureColor *= texture(u_textures[29], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 30: textureColor *= texture(u_textures[30], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
		case 31: textureColor *= texture(u_textures[31], fragmentInput.textureCoordinates * fragmentInput.tilingFactor); break;
	}

	color = textureColor;
	entityID = v_entityID;
}