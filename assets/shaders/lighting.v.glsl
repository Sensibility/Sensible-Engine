#version 450 core

layout(location = 0) in vec3 vPos_M;
layout(location = 1) in vec2 vUV_M;
layout(location = 2) in vec3 vNorm_M;
layout(location = 3) in vec3 vTan_M;
layout(location = 3) in vec3 vBiTan_M;

out vec2 UV;
out vec3 vPos_W;
//out vec3 vNorm_C;
out vec3 eyeDir_C;
out vec3 lDir_C;
out vec3 lDir_T;
out vec3 eyeDir_T;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 lPos_W;

void main() {
	gl_Position = MVP * vec4(vPos_M, 1);

	vPos_W = (M * vec4(vPos_M, 1)).xyz;

	vec3 vPos_C = (V * M * vec4(vPos_M, 1)).xyz;
	eyeDir_C = vec3(0, 0, 0) - vPos_C;

	// Assuming M is ident
	vec3 lPos_C = (V * vec4(lPos_W, 1)).xyz;
	lDir_C = lPos_C + eyeDir_C;

	//vNorm_T = (V * M * vec4(vNorm_M, 0)).xyz; 
	// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	UV = vUV_M;
	mat3 tempMVP = mat3(MVP);

	vec3 vTan_C = tempMVP * vTan_M;
	vec3 vBiTan_C = tempMVP * vBiTan_M;
	vec3 vNorm_C = tempMVP * vNorm_M;

	mat3 TBN = transpose(mat3(
		vTan_C, vBiTan_C, vNorm_C));

	lDir_T = TBN * lDir_C;
	eyeDir_T = TBN * eyeDir_C;
}