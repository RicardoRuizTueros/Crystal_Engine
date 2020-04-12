#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textureCoordinates;

uniform mat4 u_viewProjection;

out vec4 v_color;
out vec2 v_textureCoordinates;

void main()
{
	v_color = a_color;
	v_textureCoordinates = a_textureCoordinates;
	gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_textureCoordinates;

uniform vec4 u_color;
uniform sampler2D u_texture;
uniform float u_tilingFactor;

void main()
{
	color = v_color;
}