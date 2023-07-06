#version 400

out vec4 FragColor;

in vec3 Color;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 ViewPos;

struct Light{
    vec4 vector;
	vec3 color;
	float power;
 };
uniform Light light;
float strenght = 0.1;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

void main(void)
{
    
    vec3 ambient = 0.05* Color;
    vec3 lightDir = normalize(light.vector.xyz - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(lightDir, normal),0.0);
    vec3 diffuse = diff * Color;
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color

    
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    //ourColor = aColor;
}
