#version 400

layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
layout (location = 2 ) in vec3 vertexNormal; // Attributo Normale 2

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 viewPos;

out vec3 Color; // output a color to the fragment shader
out vec3 FragPos;
out vec3 Normal;

void main(void)
{
    FragPos = aPos;
    Normal = vertexNormal;
    Color = vec3(aColor);
    gl_Position = Projection*View*Model*vec4(aPos, 1.0);
    
}
