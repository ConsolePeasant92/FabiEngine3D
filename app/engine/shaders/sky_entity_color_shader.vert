#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout (location = 0) in vec3 v_pos;

uniform mat4 u_rotationMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 f_uv;

void main()
{
	vec4 pos = u_projectionMatrix * u_viewMatrix * u_rotationMatrix * vec4(v_pos, 1.0f);
	gl_Position = pos.xyww;
    f_uv = v_pos;
}