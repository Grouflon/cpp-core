#version 400

in vec3 aPosition;
in vec3 aNormal;

uniform mat4	uModel;
uniform mat4	uViewProjection;

out float	vLightWeighting;

vec4 transformedLightDirection = uModel * normalize(vec4(1.f, 6.f, .8f, 0.f));
vec4 transformedNormal = uModel * vec4(aNormal, 0.f);
void main()
{
	vLightWeighting = max(dot(transformedNormal.xyz, transformedLightDirection.xyz), 0.0);
	
	gl_Position = uViewProjection * uModel * vec4(aPosition, 1.0);
}