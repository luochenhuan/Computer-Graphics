#version 130

in vec4 varyingColor;

out vec4 frag_Color;

void main()
{
    frag_Color = varyingColor;
    // gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
