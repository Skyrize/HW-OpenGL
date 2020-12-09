#version 450 core

out vec4 color;

in VS_OUT
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
} fs_in;

struct Light {
	bool enabled;
	int type;
	vec3 position;
	vec3 direction;
	float intensity;
	vec3 color;
	float innerAngle;
	float outerAngle;
};
#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2
#define AREA_LIGHT 3

#define LIGHTS 3
uniform Light lights[LIGHTS];

struct Material {
	vec3 ambient;		// Ambient color
	vec3 diffuse;		// diffuse color
	vec3 specular;	// specular color
	float shininess;		// shininess constant
	float transparency;
	sampler2D u_Texture;
};

uniform Material mat;

uniform mat4 model_matrix;
uniform vec4 viewPosition;
uniform bool outlined = false;

vec3 GetAmbient(vec3 color, float intensity)
{
	return color * (intensity / 10);
}

vec3 GetDiffuse(vec3 color, float intensity, vec4 direction)
{
	float diff		= max(dot(fs_in.normals, direction), 0.0);

	return diff * color * intensity;
}
/*
PHONG
vec3 GetSpecular(vec3 color, float intensity, vec4 direction, float shininess)
{
	vec4 viewDir	= normalize(viewPosition - fs_in.fragPos);
	vec4 reflectDir	= reflect(-direction, fs_in.normals);
	float spec		= pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	return color * (intensity / 2) * spec;
}
*/

//Blinn-Phong
vec3 GetSpecular(vec3 color, float intensity, vec4 direction, float shininess)
{
	vec4 viewDir	= normalize(viewPosition - fs_in.fragPos);
	vec4 halfwayDir = normalize(direction + viewDir);
	float spec		= pow(max(dot(fs_in.normals, halfwayDir), 0.0), shininess);

	return color * (intensity / 2) * spec;
}

float GetAttenuation(vec4 position, float constant, float linear, float quadratic)
{
	float distance	= length(position - fs_in.fragPos);

	return 1.0f / (constant + linear * distance + quadratic * (distance * distance));
}

float GetAttenuation(vec4 position)
{
	float distance	= length(position - fs_in.fragPos);

	return clamp(10.0 / distance, 0.0, 1.0);
}

void main(void){

	vec3 ambientTotal;
	vec3 diffuseTotal;
	vec3 specularTotal;
	
	for (int i = 0; i != LIGHTS; i++) {
		if (!lights[i].enabled)
			continue;
		vec4 direction;
		if (lights[i].type == DIRECTIONAL_LIGHT) {
			direction = normalize(-vec4(lights[i].direction, 0));
		} else {
			direction = normalize(vec4(lights[i].position, 1) - fs_in.fragPos);
		}

		vec3 ambient = GetAmbient(lights[i].color, lights[i].intensity);
		vec3 diffuse = GetDiffuse(lights[i].color, lights[i].intensity, direction);
		vec3 specular = GetSpecular(lights[i].color, lights[i].intensity, direction, mat.shininess);
		
		if (lights[i].type != DIRECTIONAL_LIGHT) {
			float attenuation;

			if (lights[i].type == SPOT_LIGHT) {
				float theta = dot(direction, normalize(vec4(-lights[i].direction, 0)));
				attenuation = smoothstep(cos(lights[i].outerAngle), cos(lights[i].innerAngle), theta);
			} else {
				attenuation = GetAttenuation(vec4(lights[i].position, 1));
			}
			
			ambient *= attenuation;
			diffuse *= attenuation;
			specular *= attenuation;
			
		}
		ambientTotal += ambient;
		diffuseTotal += diffuse;
		specularTotal += specular;

	}
	ambientTotal *= mat.ambient;
	diffuseTotal *= mat.diffuse;
	specularTotal *= mat.specular;
	
	vec4 light = vec4(ambientTotal + diffuseTotal + specularTotal, mat.transparency);
	vec4 viewDir	= normalize(viewPosition - fs_in.fragPos);

	if (outlined) {
//		float nDot = dot(fs_in.normals, viewDir);
//		if (nDot > 0.4) {
//			color		= light * texture(mat.u_Texture, fs_in.tc);
//		} else {

			color		= light  * texture(mat.u_Texture, fs_in.tc) * vec4(1, 0.5, 0.5, 1);
//		}
	} else {
			color		= light * texture(mat.u_Texture, fs_in.tc);
	}

}
