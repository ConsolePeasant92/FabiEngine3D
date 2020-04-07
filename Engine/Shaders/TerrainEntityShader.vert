#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

// In variables
layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec3 v_normal;

// Uniforms
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
uniform mat4 u_shadowMatrix;
uniform vec4 u_clippingPlane;

// Out variables
out vec3 f_pos;
out vec2 f_uv;
out vec3 f_normal;
out vec4 f_shadowPos;

void main()
{
	// In variables
	vec4 worldSpacePos = vec4(v_pos, 1.0f);
	vec4 viewSpacePos  = u_viewMatrix * worldSpacePos;
	vec4 clipSpacePos  = u_projMatrix * viewSpacePos;

	// GLSL variables
	gl_Position = clipSpacePos;
	gl_ClipDistance[0] = dot(worldSpacePos, u_clippingPlane);
	
	// Out variables
	f_pos = worldSpacePos.xyz;
	f_uv = v_uv;
	f_normal = normalize(v_normal);
	f_shadowPos = u_shadowMatrix * worldSpacePos;
}