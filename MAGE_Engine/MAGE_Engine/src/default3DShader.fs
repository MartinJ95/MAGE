#version 330 core

struct pointLight
{
	vec3 m_position;
	vec3 m_intensity;
	float m_radius;
};

in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

uniform sampler2D Texture;
uniform pointLight pointLights[25];
uniform int numPointLights;
uniform vec3 cameraPosition;
uniform vec3 cameraDirection;
uniform vec3 ambientLighting;

vec3 surfaceDiffuse;
vec3 surfaceSpecular;
vec3 finalColour = vec3(0, 0, 0);
vec3 normal;

vec3 getPointLightDiffuse(pointLight light)
{
	float distance = length(light.m_position - Position);
	float attenuation = smoothstep(light.m_radius, light.m_radius / 2, distance);
	vec3 L = normalize(light.m_position - Position);
	float diffuse_intensity = max(0, dot(L, normal));
	return (diffuse_intensity * surfaceDiffuse) * attenuation;
}

vec3 getPointLightSpecular(pointLight light)
{
	float distance = length(light.m_position - Position);
	float attenuation = smoothstep(light.m_radius, light.m_radius / 2, distance);
	vec3 L = normalize(light.m_position - Position);
	vec3 viewDir = normalize(cameraPosition - Position);
	vec3 reflectDir = reflect(-L, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.f);
	return spec * surfaceSpecular * attenuation;
}

void main()
{
	normal = normalize(Normal);

	surfaceDiffuse = texture(Texture, TexCoord).xyz;

	//without specular
	//for (int i = 0; i < numPointLights; i++)
	//{
		//finalColour += pointLights[i].m_intensity * (getPointLightDiffuse(pointLights[i]));
	//}

	//with specular
	for(int i = 0; i < numPointLights; i++)
	{
		vec3 diffuse = getPointLightDiffuse(pointLights[i]);
		vec3 specular = getPointLightSpecular(pointLights[i]);
		finalColour += pointLights[i].m_intensity * (diffuse + specular);
	}

	vec3 reflectedLight = (ambientLighting) + finalColour;

	//gl_FragColor = vec4(1, 0, 0, 1);
	gl_FragColor = vec4(reflectedLight, 1.0);
	//gl_FragColor = vec4(vec3(1, 1, 1) * normal, 1.0);
	//gl_FragColor = texture(Texture, TexCoord).xyz;
}