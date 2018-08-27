#version 450 core

layout(location = 0) in vec4 vPos_M;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 vNorm;


uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 Normal;

out vec4 vPos_C;
out vec4 vOutNorm;
out vec4 vOutColor;

void main() {
	vOutColor = vColor;
	vOutNorm = normalize(Normal * vNorm);
	vPos_C = MV * vPos_M;
	gl_Position = MVP * vPos_M;
}