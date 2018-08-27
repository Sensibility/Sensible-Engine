#version 450 core

struct Light {
	bool enabled_, local_, spot_;
	vec3 color_, position_, half_, cone_;
	float sCosCutoff_, sExponent_, atten_, linAtten_, quadAtten_;
};
#define MAX_LIGHTS 10

in vec4 vPos_M;
in vec4 vColor;
in vec4 vNorm;


uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 Normal;
uniform Light Lights[MAX_LIGHTS];
uniform vec4 eyeDir_C;

out vec4 color;

void main() {
	vec3 ambient = vec3(0.0);
	vec3 reflect = ambient;

	for (int i = 0; i < MAX_LIGHTS; ++i) {
		if (!Lights[i].enabled_)
			continue;

		vec3 halfway, lightDir;
		lightDir = Lights[i].position_;
		float atten = 1.0;

		if (Lights[i].local_) {
			lightDir = lightDir - vec3(vPos_M);
			float distance = length(lightDir);
			lightDir = lightDir / distance;

			atten = 1.0 /
				(Lights[i].atten_
					+ Lights[i].linAtten_ * distance
					+ Lights[i].quadAtten_ * distance * distance);

			if (Lights[i].spot_) {
				float spotCos = dot(lightDir, -Lights[i].cone_);
				if (spotCos < Lights[i].sCosCutoff_)
					atten = 0.0;
				else
					atten *= pow(spotCos, Lights[i].sExponent_);
			}

			halfway = normalize(lightDir + eyeDir_C);
		}
		else
			halfway = Lights[i].half_;

		float diffuse = max(0.0, dot(vNorm, lightDir));
		float specular = max(0.0, dot(vNorm, halfway));

		if (diffuse == 0.0)
			specular = 0.0;
		else
			specular = pow(specular, 1) * 1; //Shinines, Strength

		ambient += Lights[i].ambient_ * atten +
			Lights[i].color * diffuse * atten;
		reflect += Lights[i].color * specular * atten;
	}

	vec3 rgb = min(vColor.rgb * ambient + reflect, vec3(1.0));
	color = vec4(rgb, vColor.a);
}