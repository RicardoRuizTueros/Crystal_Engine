#type vertex
#version 450

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textureCoordinates;
layout(location = 3) in float a_textureIndex;
layout(location = 4) in float a_tilingFactor;
layout(location = 5) in int a_entityID;

uniform mat4 u_viewProjection;

out vec4 v_color;
out vec2 v_textureCoordinates;
out flat float v_textureIndex;
out float v_tilingFactor;
out flat int v_entityID;

void main()
{
	v_color = a_color;
	v_textureCoordinates = a_textureCoordinates;
	v_textureIndex = a_textureIndex;
	v_tilingFactor = a_tilingFactor;
	v_entityID = a_entityID;
	gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 color;
layout(location = 1) out int entityID;

in vec4 v_color;
in vec2 v_textureCoordinates;
in flat float v_textureIndex;
in float v_tilingFactor;
in flat int v_entityID;

uniform sampler2D u_textures[32];

void main()
{
	vec4 textureColor = v_color;

	switch(int(v_textureIndex))
	{
		case 0: textureColor *= texture(u_textures[0], v_textureCoordinates * v_tilingFactor); break;
		case 1: textureColor *= texture(u_textures[1], v_textureCoordinates * v_tilingFactor); break;
		case 2: textureColor *= texture(u_textures[2], v_textureCoordinates * v_tilingFactor); break;
		case 3: textureColor *= texture(u_textures[3], v_textureCoordinates * v_tilingFactor); break;
		case 4: textureColor *= texture(u_textures[4], v_textureCoordinates * v_tilingFactor); break;
		case 5: textureColor *= texture(u_textures[5], v_textureCoordinates * v_tilingFactor); break;
		case 6: textureColor *= texture(u_textures[6], v_textureCoordinates * v_tilingFactor); break;
		case 7: textureColor *= texture(u_textures[7], v_textureCoordinates * v_tilingFactor); break;
		case 8: textureColor *= texture(u_textures[8], v_textureCoordinates * v_tilingFactor); break;
		case 9: textureColor *= texture(u_textures[9], v_textureCoordinates * v_tilingFactor); break;
		case 10: textureColor *= texture(u_textures[10], v_textureCoordinates * v_tilingFactor); break;
		case 11: textureColor *= texture(u_textures[11], v_textureCoordinates * v_tilingFactor); break;
		case 12: textureColor *= texture(u_textures[12], v_textureCoordinates * v_tilingFactor); break;
		case 13: textureColor *= texture(u_textures[13], v_textureCoordinates * v_tilingFactor); break;
		case 14: textureColor *= texture(u_textures[14], v_textureCoordinates * v_tilingFactor); break;
		case 15: textureColor *= texture(u_textures[15], v_textureCoordinates * v_tilingFactor); break;
		case 16: textureColor *= texture(u_textures[16], v_textureCoordinates * v_tilingFactor); break;
		case 17: textureColor *= texture(u_textures[17], v_textureCoordinates * v_tilingFactor); break;
		case 18: textureColor *= texture(u_textures[18], v_textureCoordinates * v_tilingFactor); break;
		case 19: textureColor *= texture(u_textures[19], v_textureCoordinates * v_tilingFactor); break;
		case 20: textureColor *= texture(u_textures[20], v_textureCoordinates * v_tilingFactor); break;
		case 21: textureColor *= texture(u_textures[21], v_textureCoordinates * v_tilingFactor); break;
		case 22: textureColor *= texture(u_textures[22], v_textureCoordinates * v_tilingFactor); break;
		case 23: textureColor *= texture(u_textures[23], v_textureCoordinates * v_tilingFactor); break;
		case 24: textureColor *= texture(u_textures[24], v_textureCoordinates * v_tilingFactor); break;
		case 25: textureColor *= texture(u_textures[25], v_textureCoordinates * v_tilingFactor); break;
		case 26: textureColor *= texture(u_textures[26], v_textureCoordinates * v_tilingFactor); break;
		case 27: textureColor *= texture(u_textures[27], v_textureCoordinates * v_tilingFactor); break;
		case 28: textureColor *= texture(u_textures[28], v_textureCoordinates * v_tilingFactor); break;
		case 29: textureColor *= texture(u_textures[29], v_textureCoordinates * v_tilingFactor); break;
		case 30: textureColor *= texture(u_textures[30], v_textureCoordinates * v_tilingFactor); break;
		case 31: textureColor *= texture(u_textures[31], v_textureCoordinates * v_tilingFactor); break;
	}

	color = textureColor;

	entityID = v_entityID;
}