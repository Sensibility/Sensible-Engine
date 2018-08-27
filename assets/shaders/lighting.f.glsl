#version 450 core

in vec2 UV;
in vec3 vPos_W;
//in vec3 vNorm_C;
in vec3 eyeDir_C;
in vec3 lDir_C;

in vec3 lDir_T;
in vec3 eyeDir_T;

out vec4 color;

uniform sampler2D normSample;
uniform sampler2D diffSample;
uniform sampler2D specSample;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lPos_W;

void main() {

	vec3 LightColor = vec3(1, 1, 1);
	float LightPower = 5.0f;

	vec3 mDiffuseColor = texture(diffSample, UV).rgb;
	vec3 mAmbiantColor = vec3(0.1, 0.1, 0.1) * mDiffuseColor;
	vec3 mSpecularColor = texture(specSample, UV).rgb * 0.3;

	//we flip uvs for dds files, assume normal is TGA so we need to unflip
	vec3 tNorm_T = normalize(texture(normSample, vec2(UV.x, -UV.y)).rgb*2.0 - 1.0);

	// Distance to the light
	float distance = length(lPos_W - vPos_W);

	// Normal of the computed fragment, in camera space
	vec3 n = tNorm_T;
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize(lDir_T);
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot(n, l), 0, 1);

	// Eye vector (towards the camera)
	vec3 E = normalize(eyeDir_T);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l, n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp(dot(E, R), 0, 1);

	color =
		vec4(
		// Ambiant : simulates indirect lighting
		mAmbiantColor +
		// Diffuse : "color" of the object
		mDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		mSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance*distance),
	 1);
}