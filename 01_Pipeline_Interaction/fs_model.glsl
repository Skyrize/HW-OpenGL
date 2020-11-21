#version 450 core

out vec4 color;

in VS_OUT
{
    vec2 tc;
    vec4 normals;
    vec4 fragPos;
	vec4 color;
    float texID;
} fs_in;



uniform mat4 model_matrix;

uniform vec4 lightPosition;
uniform vec4 viewPosition;

uniform sampler2D u_Textures[16];

uniform vec4 dirLightDirection;

uniform vec4 ambientColour;		// Ambient colour
uniform float ambientConst;		// Ambient constant
uniform vec4 diffuseColour;		// diffuse colour
uniform float diffuseConst;		// Diffuse constant
uniform vec4 specularColour;	// specular colour
uniform float specularConst;	// specular constant
uniform float shininess;		// shininess constant

uniform float lightConstant;
uniform float lightLinear;
uniform float lightQuadratic;

vec3 GetLight(vec4 direction, vec4 ia, float ka, vec4 id, float kd, vec4 is, float ks, float kshi)
{
	// Diffuse
	float diff		= max(dot(normalize(fs_in.normals), direction), 0.0);
	vec3 diffuse	= diff * id.rgb * kd;

	// Specular
	vec4 viewDir	= normalize(viewPosition - fs_in.fragPos);
	vec4 reflectDir	= reflect(-direction, normalize(fs_in.normals));
	float spec		= pow(max(dot(viewDir, reflectDir), 0.0), kshi);
	vec3 specular	= ks * is.rgb * spec;

	// Ambient
	vec3 ambient	= ka * ia.rgb;
	
	// Light
	return (ambient + diffuse + specular);
}

vec3 GetAttenuatedLight(vec4 direction, vec4 ia, float ka, vec4 id, float kd, vec4 is, float ks, float kshi, float kc, float kl, float kq)
{
	vec3 light = GetLight(direction, ia, ka, id, kd, is, ks, kshi);
	
	// Attenuation
	float distance	= length(lightPosition - fs_in.fragPos);
	float attenuation = 1.0f / (kc + kl * distance + kq * (distance * distance));

	// Light
	return attenuation * light;
}

void main(void){
	// Directional Light
	vec3 directionalLight = GetLight(normalize(dirLightDirection), ambientColour, ambientConst, diffuseColour, diffuseConst, specularColour, specularConst, shininess);

	// Point Light
	vec3 attenuatedLight = GetAttenuatedLight(normalize(lightPosition - fs_in.fragPos), ambientColour, ambientConst, diffuseColour, diffuseConst, specularColour, specularConst, shininess, lightConstant, lightLinear, lightQuadratic);
	
	// Final Light
	vec4 light		= vec4(attenuatedLight + directionalLight, 1.0);
	light = vec4(directionalLight, 1.0);


	int index		= int(fs_in.texID);
	// Light
	// if (index == 0) {
		color		= light * fs_in.color;
	// } else {
	//	color		= light * texture(u_Textures[index - 1], fs_in.tc);
	//}
}
