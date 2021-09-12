#version 330 core
#extension GL_ARB_explicit_uniform_location : require

// Const variables
#define MAX_LIGHT_COUNT 128

// In variables
in vec3 f_pos;
in vec2 f_uv;
in vec3 f_normal;
in vec4 f_shadowPos;
in mat3 f_tbnMatrix;

// Textures
layout (location = 0) uniform sampler2D u_shadowMap;
layout (location = 1) uniform sampler2D u_diffuseMap;
layout (location = 2) uniform sampler2D u_normalMap;
layout (location = 3) uniform sampler2D u_blendMap;
layout (location = 4) uniform sampler2D u_diffuseMapR;
layout (location = 5) uniform sampler2D u_diffuseMapG;
layout (location = 6) uniform sampler2D u_diffuseMapB;
layout (location = 7) uniform sampler2D u_normalMapR;
layout (location = 8) uniform sampler2D u_normalMapG;
layout (location = 9) uniform sampler2D u_normalMapB;

// Vector uniforms
uniform vec3 u_lightPositions[MAX_LIGHT_COUNT];
uniform vec3 u_lightRadiuses[MAX_LIGHT_COUNT];
uniform vec3 u_lightColors[MAX_LIGHT_COUNT];
uniform vec3 u_cameraPosition;
uniform vec3 u_cameraFront;
uniform vec3 u_ambientLightingColor;
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightPosition;
uniform vec3 u_spotLightingColor;
uniform vec3 u_shadowAreaCenter;
uniform vec3 u_fogColor;

// Float uniforms
uniform float u_lightIntensities[MAX_LIGHT_COUNT];
uniform float u_lightness;
uniform float u_ambientLightingIntensity;
uniform float u_directionalLightingIntensity;
uniform float u_diffuseMapRepeat;
uniform float u_diffuseMapRepeatR;
uniform float u_diffuseMapRepeatG;
uniform float u_diffuseMapRepeatB;
uniform float u_shadowAreaSize;
uniform float u_fogMinDistance;
uniform float u_fogMaxDistance;
uniform float u_fogThickness;
uniform float u_specularLightingFactor;
uniform float u_specularLightingIntensity;
uniform float u_maxSpotLightingAngle;
uniform float u_spotLightingIntensity;
uniform float u_maxSpotLightingDistance;
uniform float u_shadowLightness;

// Integer uniforms
uniform int u_lightShapes[MAX_LIGHT_COUNT];

// Boolean uniforms
uniform bool u_isWireFramed;
uniform bool u_isSpecularLighted;
uniform bool u_isAmbientLightingEnabled;
uniform bool u_isDirectionalLightingEnabled;
uniform bool u_isSpotLightingEnabled;
uniform bool u_isFogEnabled;
uniform bool u_isShadowsEnabled;
uniform bool u_isShadowFrameRenderEnabled;
uniform bool u_hasDiffuseMap;
uniform bool u_hasNormalMap;
uniform bool u_hasBlendMap;
uniform bool u_hasDiffuseMapR;
uniform bool u_hasDiffuseMapG;
uniform bool u_hasDiffuseMapB;
uniform bool u_hasNormalMapR;
uniform bool u_hasNormalMapG;
uniform bool u_hasNormalMapB;

// Integer uniforms
uniform int u_lightCount;

// Out variables
layout (location = 0) out vec4 o_primaryColor;
layout (location = 1) out vec4 o_secondaryColor;

// Functions
vec3 calculateNormalMapping();
vec3 calculateDiffuseMapping();
vec3 calculateAmbientLighting();
vec3 calculateDirectionalLighting(vec3 normal);
vec3 calculateLights(vec3 normal);
vec3 calculateSpotLighting(vec3 normal);
vec3 calculateFog(vec3 color);
float calculateSpecularLighting(vec3 position, vec3 normal);
float calculateShadows();

// Process fragment
void main()
{
	// Wire frame color
	if(u_isWireFramed)
	{
		o_primaryColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return;
	}

	// Calculate normal mapping
    vec3 normal = calculateNormalMapping();

	// Calculate lighting
    float shadowLighting	 = calculateShadows();
	float shadowOcclusion	 = ((shadowLighting - u_shadowLightness) / (1.0f - u_shadowLightness));
	vec3 ambientLighting	 = (calculateAmbientLighting() * shadowLighting);
	vec3 directionalLighting = (calculateDirectionalLighting(normal) * shadowOcclusion);
	vec3 spotLighting		 = calculateSpotLighting(normal);
	vec3 lights				 = calculateLights(normal);

	// Calculate base color
	vec3 primaryColor = vec3(0.0f);
	primaryColor += calculateDiffuseMapping();
	primaryColor *= u_lightness;
	primaryColor  = clamp(primaryColor, vec3(0.0f), vec3(1.0f));

	// Apply lighting
	vec3 lighting = vec3(0.0f);
	lighting += ambientLighting;
	lighting += directionalLighting;
	lighting += spotLighting;
	lighting += lights;
	primaryColor *= lighting;

	// Apply fog
	primaryColor = calculateFog(primaryColor);

	// Apply gamma correction
	primaryColor = pow(primaryColor, vec3(1.0f / 2.2f));

	// Set final colors
	o_primaryColor = vec4(primaryColor, 1.0f);
	o_secondaryColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

vec3 calculateNormalMapping()
{
    if (u_hasNormalMap || u_hasNormalMapR || u_hasNormalMapG || u_hasNormalMapB)
    {
		if (u_hasBlendMap) // Blendmapped mixed normal
		{
			// Get color values of blendmap (R, G, B)
			vec2 blendUV = f_uv / u_diffuseMapRepeat;
			vec4 blendMapColor = texture(u_blendMap, blendUV);
			float diffuseStrength = (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
			float rStrength = blendMapColor.r;
			float gStrength = blendMapColor.g;
			float bStrength = blendMapColor.b;

			// Calculate total normal vector
			vec3 totalNormal;

			// Diffuse normal map
			if (u_hasNormalMap)
			{
				vec3 normal = texture(u_normalMap, f_uv).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * diffuseStrength;
			}
			else
			{
				totalNormal += f_normal * diffuseStrength;
			}
			
			// BlendR normal map
			if (u_hasNormalMapR)
			{
				vec3 normal = texture(u_normalMapR, blendUV * u_diffuseMapRepeatR).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * rStrength;
			}
			else
			{
				totalNormal += f_normal * rStrength;
			}

			// BlendG normal map
			if (u_hasNormalMapG)
			{
				vec3 normal = texture(u_normalMapG, blendUV * u_diffuseMapRepeatG).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * gStrength;
			}
			else
			{
				totalNormal += f_normal * gStrength;
			}

			// BlendB normal map
			if (u_hasNormalMapB)
			{
				vec3 normal = texture(u_normalMapB, blendUV * u_diffuseMapRepeatB).rgb * 2.0f - 1.0f;
				totalNormal += normalize(f_tbnMatrix * normal) * bStrength;
			}
			else
			{
				totalNormal += f_normal * bStrength;
			}

			// Return
			return totalNormal;
		}
		else // Diffuse normal
		{
			if (u_hasNormalMap)
			{
				// Calculate new normal vector
				vec3 normal = texture(u_normalMap, f_uv).rgb;
				normal = normal * 2.0f - 1.0f;
				normal = normalize(f_tbnMatrix * normal);

				// Return
				return normal;
			}
			else
			{
				return f_normal;
			}
		}        
    }
    else
    {
        return f_normal;
    }
}

vec3 calculateDiffuseMapping()
{
	if (u_hasBlendMap) // Blendmapped mixed texture
	{
		// Get color value of blendmap (R, G, B)
		vec2 blendUV = f_uv / u_diffuseMapRepeat;
		vec4 blendMapColor = texture(u_blendMap, blendUV);

		// Calculate diffuse map color
		vec3 diffuseMapColor = vec3(0.0f);
		if (u_hasDiffuseMap)
		{
			diffuseMapColor = texture(u_diffuseMap, f_uv).rgb* (1.0f - blendMapColor.r - blendMapColor.g - blendMapColor.b);
		}

		// Calculate blending color for every channel
		vec3 rColor = u_hasDiffuseMapR ? (texture(u_diffuseMapR, blendUV * u_diffuseMapRepeatR).rgb * blendMapColor.r) : vec3(0.0f);
		vec3 gColor = u_hasDiffuseMapG ? (texture(u_diffuseMapG, blendUV * u_diffuseMapRepeatG).rgb * blendMapColor.g) : vec3(0.0f);
		vec3 bColor = u_hasDiffuseMapB ? (texture(u_diffuseMapB, blendUV * u_diffuseMapRepeatB).rgb * blendMapColor.b) : vec3(0.0f);
		rColor = pow(rColor, vec3(2.2f));
		gColor = pow(gColor, vec3(2.2f));
		bColor = pow(bColor, vec3(2.2f));

		// Compose final color
		vec3 newColor = (diffuseMapColor + rColor + gColor + bColor);
        
		// Return
		return newColor;
	}
	else if (u_hasDiffuseMap) // Diffuse texture
	{
		// Calculate
		vec3 newColor = texture(u_diffuseMap, vec2(-f_uv.x, f_uv.y)).rgb;
		newColor = pow(newColor, vec3(2.2f));

		// Return
		return newColor;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateAmbientLighting()
{
	if (u_isAmbientLightingEnabled)
	{
		return (u_ambientLightingColor * u_ambientLightingIntensity);
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateDirectionalLighting(vec3 normal)
{
	if (u_isDirectionalLightingEnabled)
	{
        // Calculate lighting strength
        vec3 result = vec3(0.0f);
        vec3 lightDirection = normalize(u_directionalLightPosition - f_pos);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_directionalLightPosition, normal);

        // Apply
        result += vec3(diffuse); // Diffuse
        result += vec3(specular); // Specular
        result *= u_directionalLightColor; // Color
        result *= u_directionalLightingIntensity; // Intensity

        // Return
        return result;
	}
	else
	{
		return vec3(0.0f);
	}
}

vec3 calculateLights(vec3 normal)
{
	vec3 result = vec3(0.0f);
		
    // For every light
	for (int i = 0; i < u_lightCount; i++)
	{
        // Calculate light strength
		vec3 lightDirection = normalize(u_lightPositions[i] - f_pos);
		float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
		float specular = calculateSpecularLighting(u_lightPositions[i], normal);

		// Calculate light attenuation
		float attenuation;
		if (u_lightShapes[i] == 0)
		{
			float fragmentDistance = distance(u_lightPositions[i], f_pos);
			float averageRadius = ((u_lightRadiuses[i].x + u_lightRadiuses[i].y + u_lightRadiuses[i].z) / 3.0f);
			attenuation = max(0.0f, (1.0f - (fragmentDistance / averageRadius)));
		}
		else
		{
			vec3 fragmentDistance = abs(u_lightPositions[i] - f_pos);
			float xAttenuation = max(0.0f, (1.0f - (fragmentDistance.x / u_lightRadiuses[i].x)));
			float yAttenuation = max(0.0f, (1.0f - (fragmentDistance.y / u_lightRadiuses[i].y)));
			float zAttenuation = max(0.0f, (1.0f - (fragmentDistance.z / u_lightRadiuses[i].z)));
			attenuation = min(xAttenuation, min(yAttenuation, zAttenuation));
		}

        // Apply
        vec3 current = vec3(0.0f);
		current += vec3(diffuse); // Diffuse
        current += vec3(specular); // Specular
        current *= u_lightColors[i]; // Color
        current *= (attenuation * attenuation); // Distance
        current *= u_lightIntensities[i]; // Intensity

        // Add to total lighting value
        result += current;
	}

    // Return
	return result;
}

vec3 calculateSpotLighting(vec3 normal)
{
    if (u_isSpotLightingEnabled)
    {
		// Calculate distance
    	float fragmentDistance = distance(u_cameraPosition, f_pos);
        float distanceFactor = fragmentDistance / u_maxSpotLightingDistance;
        distanceFactor = clamp(distanceFactor, 0.0f, 1.0f);
        distanceFactor = 1.0f - distanceFactor;

        // Calculate lighting strength
        vec3 result = vec3(0.0f);
        vec3 lightDirection = normalize(u_cameraPosition - f_pos);
        float smoothingFactor = 0.9f;
        float spotTheta = dot(lightDirection, normalize(-u_cameraFront));
        float epsilon   = u_maxSpotLightingAngle - u_maxSpotLightingAngle * smoothingFactor;
        float intensity = clamp((spotTheta - u_maxSpotLightingAngle * smoothingFactor) / epsilon, 0.0f, 1.0f);  

        // Apply lighting calculations
        float diffuse = clamp(dot(normal, lightDirection), 0.0f, 1.0f);
        float specular = calculateSpecularLighting(u_cameraPosition, normal);
        result += vec3(diffuse * intensity); // Diffuse
        result += vec3(specular * intensity); // Specular
        result *= u_spotLightingColor; // Color
        result *= u_spotLightingIntensity; // Intensity

        // Return
        return (result * distanceFactor);
    }
    else
    {
        return vec3(0.0f);
    }
}

vec3 calculateFog(vec3 color)
{
	if (u_isFogEnabled)
	{
		// Calculate distance to fragment in world space
		float fragmentDistance = distance(f_pos.xyz, u_cameraPosition);

        // Calculate fog intensity
		float distanceDifference = (u_fogMaxDistance - u_fogMinDistance);
		float fragmentPart = clamp(((fragmentDistance - u_fogMinDistance) / distanceDifference), 0.0f, 1.0f);
		float thickness = clamp(u_fogThickness, 0.0f, 1.0f);
		float mixValue = (fragmentPart * thickness);

		// Return
		return mix(color, u_fogColor, mixValue);
	}
	else
	{
		return color;
	}
}

float calculateSpecularLighting(vec3 position, vec3 normal)
{
    if (u_isSpecularLighted)
    {
        // Calculate
        vec3 lightDirection   = normalize(position - f_pos);
        vec3 viewDirection    = normalize(u_cameraPosition - f_pos);
        vec3 halfWayDirection = normalize(lightDirection + viewDirection);
        float result          = pow(clamp(dot(normal, halfWayDirection), 0.0f, 1.0f), u_specularLightingFactor);

        // Return
        return (result * u_specularLightingIntensity);
    }
    else
    {
        return 0.0f;
    }
}

float calculateShadows()
{
	if (u_isShadowsEnabled)
	{
		// Temporary values
		float halfSize = (u_shadowAreaSize / 2.0f);
		float fragmentDistance = distance(f_pos.xz, u_shadowAreaCenter.xz);

		// Check if fragment is within shadow area
		if (fragmentDistance <= halfSize)
		{
			// Variables
			float shadow       = 0.0f;
			vec3 projCoords    = (f_shadowPos.xyz / f_shadowPos.w) * 0.5f + 0.5f;
			float currentDepth = projCoords.z;
			vec2 texelSize     = (vec2(1.0f) / textureSize(u_shadowMap, 0));

			// Skip fragments outside of the depth map
			if (projCoords.z > 1.0f)
			{	
				return 1.0f;
			}
			
			// Calculate PCF shadows
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					float pcfDepth = texture(u_shadowMap, projCoords.xy + (vec2(x, y) * texelSize)).r; 
					shadow += (currentDepth - texelSize.x > pcfDepth) ? u_shadowLightness : 1.0f;        
				}    
			}
            
			// Calculate final shadow value
			shadow /= 9.0f;

			// Limit shadows
			if (shadow > 1.0f)
			{
				shadow = 1.0f;
			}

			// Long-distance shadows fading
			float alpha = (fragmentDistance - (halfSize * 0.9f)); // Only for the outer 10% of the shadowed area
			alpha = clamp(alpha, 0.0f, halfSize * 0.1f); // Cannot be negative
			alpha /= (halfSize * 0.1f); // Convert value to 0.0 - 1.0 range

			// Debug area frame rendering
			if (u_isShadowFrameRenderEnabled)
			{
				if ((fragmentDistance - (halfSize * 0.99f)) > 0.0f)
				{
					return 0.0f;
				}
			}

			// Return
			return mix(shadow, 1.0f, alpha);
		}

		// No shadow
		return 1.0f;
	}
	else
	{
		// No shadow
		return 1.0f;
	}
}