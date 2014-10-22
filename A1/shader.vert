#version 130 

in vec3 vert;
uniform mat4 mvpMatrix;

in vec3 color;
out vec4 varyingColor;

void main()
{	
    gl_Position = mvpMatrix * vec4(vert, 1.0);
    // gl_Position = ftransform();
    varyingColor = vec4(color,1.0);
}
