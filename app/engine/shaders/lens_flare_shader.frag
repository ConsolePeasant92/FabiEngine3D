#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec2 f_uv;
in float f_flareVisibility;

layout (location = 1) uniform sampler2D u_sceneMap;
layout (location = 2) uniform sampler2D u_flareMap;

uniform float u_lensFlareIntensity;
uniform float u_lensFlareTransparency;

uniform bool u_isLensFlareEnabled;

layout (location = 0) out vec4 o_finalColor;

void main()
{
	if (!u_isLensFlareEnabled)
	{
        o_finalColor.rgb = texture(u_sceneMap, f_uv).rgb;
		o_finalColor.a = 1.0f;
		return;
    }

    vec3 worldColor = texture(u_sceneMap, f_uv).rgb;
    vec3 flareColor = texture(u_flareMap, vec2(f_uv.x, -f_uv.y)).rgb;

    o_finalColor.rgb = worldColor;
    o_finalColor.rgb += (flareColor * u_lensFlareTransparency * u_lensFlareIntensity * f_flareVisibility);
	o_finalColor.a = 1.0f;
}