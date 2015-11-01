#version 400

in float	vLightWeighting;

out vec4	oResult;

const vec4	ambientColor = vec4(0.3, 0.3, 0.3, 1.0);

void main()
{
	oResult = ambientColor + (vec4(1.0, 1.0, 1.0, 1.0) * vLightWeighting);
}