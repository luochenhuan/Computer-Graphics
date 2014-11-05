#version 330

uniform vec3 frag_color;
uniform int isShading;
in vec3 Intensity;

out vec4 finalColor;

void main()
{
    if (isShading > 0)
    	finalColor = vec4(Intensity, 1.0);
else
	finalColor = vec4(frag_color, 1.0);
}
