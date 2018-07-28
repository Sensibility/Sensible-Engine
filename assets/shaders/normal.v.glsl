layout(location = 0) in vec3 vPosition_Model;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal_Model;
layout(location = 3) in vec3 vTangent_Model;
layout(location = 4) in vec3 vBiTangent_Model;

out vec2 UV;
out vec3 pos_World;
out vec3 eyeDir_Camera;
out vec3 lightDir_Camera;
out vec3 lightDir_Tangent;
out vec3 eyeDir_Tangent;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat4 MV3x3;
uniform vec3 lightPos_World;

//normal = 2*texel_color - 1
void main() {
	gl_Position = MVP * vec4(vPosition_Model, 1);

	pos_World = (M * vec4(vPosition_Model, 1)).xyz;

	vec3 vPosition_Camera = (V * M * vec4(vPosition_Model, 1)).xyz;
	eyeDir_Camera = vec3(0, 0, 0) - vPosition_Camera;

	vec3 lightPos_Camera = (V * vec4(lightPos_World, 1)).xyz;
	lightDir_Camera = lightPos_Camera + eyeDir_Camera;

	UV = vUV;

	vec3 vTangent_Camera = MV3x3 * vTangent_Model;
	vec3 vBiTangent_Camera = MV3x3 * vBiTangent_Model;
	vec3 vNormal_Camera = MV3x3 * vNormal_Model;

	//tangent bitangent normal
	mat3 TBN = transpose(mat3(
		vTanget_Camera,
		vBiTangent_Camera,
		vNormal_Camera
	));

	lightDir_Tangent = TBN * lightDir_Camera;
	eyeDir_Tangent = TBN * eyeDir_Camera;
}