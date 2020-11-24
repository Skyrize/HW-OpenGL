#version 450 core

out vec4 color;

in VS_OUT
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
} fs_in;

struct Light {
	int type;
	vec3 position;
	vec3 direction;
	float intensity;
	vec3 color;
	float lightConstant;
	float lightLinear;
	float lightQuadratic;
};
#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2
#define AREA_LIGHT 3

#define LIGHTS 2
uniform Light lights[LIGHTS];


//
//struct DirectionalLight {
//	vec4 direction;
//	float intensity;
//	vec4 color;
//};
//
//uniform DirectionalLight directionalLight;
//
//struct PointLight {
//	vec4 position;
//	float intensity;
//	vec4 color;
//	float lightConstant;
//	float lightLinear;
//	float lightQuadratic;
//};
//
//#define POINTLIGHTS 1
//uniform PointLight pointLights[POINTLIGHTS];
//
struct Material {
	vec3 ambient;		// Ambient color
	vec3 diffuse;		// diffuse color
	vec3 specular;	// specular color
	float shininess;		// shininess constant
	sampler2D u_Texture;
};

uniform Material mat;

uniform mat4 model_matrix;
uniform vec4 viewPosition;

vec3 GetAmbient(vec3 color, float intensity)
{
	return color * intensity;
}

vec3 GetDiffuse(vec3 color, float intensity, vec4 direction)
{
	float diff		= max(dot(normalize(fs_in.normals), direction), 0.0);

	return diff * color * intensity;
}

vec3 GetSpecular(vec3 color, float intensity, vec4 direction, float shininess)
{
	vec4 viewDir	= normalize(viewPosition - fs_in.fragPos);
	vec4 reflectDir	= reflect(-direction, normalize(fs_in.normals));
	float spec		= pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	return color * intensity * spec;
}

float GetAttenuation(vec4 position, float constant, float linear, float quadratic)
{
	float distance	= length(position - fs_in.fragPos);

	return 1.0f / (constant + linear * distance + quadratic * (distance * distance));
}

void main(void){

	vec3 ambientTotal;
	vec3 diffuseTotal;
	vec3 specularTotal;

	for (int i = 0; i != LIGHTS; i++) {
		vec4 direction;
		if (lights[i].type == DIRECTIONAL_LIGHT) {
			direction = vec4(-lights[i].direction, 1);
		} else if (lights[i].type == POINT_LIGHT) {
			direction = normalize(vec4(lights[i].position, 1) - fs_in.fragPos);
		}
		vec3 ambient = GetAmbient(lights[i].color, lights[i].intensity);
		vec3 diffuse = GetDiffuse(lights[i].color, lights[i].intensity, direction);
		vec3 specular = GetSpecular(lights[i].color, lights[i].intensity, direction, mat.shininess);
		
		if (lights[i].type != DIRECTIONAL_LIGHT) {
			float attenuation = GetAttenuation(vec4(lights[i].position, 1), lights[i].lightConstant, lights[i].lightLinear, lights[i].lightQuadratic);
			
			ambient *= attenuation;
			diffuse *= attenuation;
			specular *= attenuation;
			ambient /= attenuation;
			diffuse /= attenuation;
			specular /= attenuation;
		}
		ambientTotal += ambient;
		diffuseTotal += diffuse;
		specularTotal += specular;

	}
	ambientTotal *= mat.ambient;
	diffuseTotal *= mat.diffuse;
	specularTotal *= mat.specular;
	
	vec4 light = vec4(ambientTotal + diffuseTotal + specularTotal, 1);

	color		= light * texture(mat.u_Texture, fs_in.tc);
//
//	vec4 directionalAmbient = GetAmbient(directionalLight.color, directionalLight.intensity);
//	vec4 directionalDiffuse = GetDiffuse(directionalLight.color, directionalLight.intensity, directionalLight.direction);
//	vec4 directionalSpecular = GetSpecular(directionalLight.color, directionalLight.intensity, directionalLight.direction, mat.shininess);
//
//	
//	vec4 pointAmbientTotal;
//	vec4 pointDiffuseTotal;
//	vec4 pointSpecularTotal;
//
//	for (int i = 0; i != POINTLIGHTS; i++) {
//		vec4 pointDirection = normalize(pointLights[i].position - fs_in.fragPos);
//		vec4 pointAmbient = GetAmbient(pointLights[i].color, pointLights[i].intensity);
//		vec4 pointDiffuse = GetDiffuse(pointLights[i].color, pointLights[i].intensity, pointDirection);
//		vec4 pointSpecular = GetSpecular(pointLights[i].color, pointLights[i].intensity, pointDirection, mat.shininess);
//		float attenuation = GetAttenuation(pointLights[i].position, pointLights[i].lightConstant, pointLights[i].lightLinear, pointLights[i].lightQuadratic);
//
//		pointAmbient *= attenuation;
//		pointDiffuse *= attenuation;
//		pointSpecular *= attenuation;
//
//		pointAmbientTotal += pointAmbient;
//		pointDiffuseTotal += pointDiffuse;
//		pointSpecularTotal += pointSpecular;
//	}
//	
//	vec4 ambientLight = directionalAmbient + pointAmbientTotal;
//	ambientLight *= mat.ambient;
//	
//	vec4 diffuseLight = directionalDiffuse + pointDiffuseTotal;
//	diffuseLight *= mat.diffuse;
//	
//	vec4 specularLight = directionalSpecular + pointSpecularTotal;
//	specularLight *= mat.specular;
//
//	vec4 light = ambientLight + diffuseLight + specularLight;
//
//	color		= light * texture(mat.u_Texture, fs_in.tc);
}
