#version 460 core

layout (location = 0) in vec2 v_position;
layout (location = 1) in vec2 v_uv;

out vec2 f_worldSpacePosition;
out vec2 f_uv;

void main()
{
	f_worldSpacePosition = v_position;
	f_uv = v_uv;

	gl_Position = vec4(v_position, 0.0f, 1.0f);
}