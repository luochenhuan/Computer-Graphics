#version 330 

in vec3 vertPos;

uniform mat4 mvpMatrix;
uniform mat4 mvMatrix;

uniform vec4 LightPos; // light position (just put sw behind camera)
uniform vec3 La;
uniform vec3 Ld;
uniform vec3 Ls;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;

uniform mat3 normMat; // getcameraMa() left out perspective matrix

out vec3 Intensity;

void main()
{	
    vec3 VertNorm = vertPos;	
    gl_Position = mvpMatrix * vec4(vertPos, 1.0);
    // gl_Position = ftransform();

    vec3 tnorm = normalize(normMat * VertNorm);
    vec4 surface = mvMatrix * vec4(vertPos, 1.0);
    vec3 s = normalize (vec3(LightPos - surface));
    vec3 v = normalize (-surface.xyz);
    vec3 r = reflect (-s, tnorm);
    vec3 ambient = Ka;
    float SdotN = max(dot(s, tnorm), 0.0);
    vec3 diffuse = Ld * Kd * SdotN;

    vec3 spec = vec3(0.0, 0.0, 0.0);
    if (SdotN > 0)
    {
    	spec =  2.0 * Ks * pow(max(dot(r,v), 0.0), shininess);
    }

    //Intensity =ambient + diffuse + spec;
    Intensity =ambient + diffuse;

}
