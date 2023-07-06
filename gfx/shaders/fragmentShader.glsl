#version 400

in vec4 ourColor;
in vec3 N,V;

out vec4 FragColor;

struct Light{
    vec4 vector;
	vec3 color;
	float power;
 };
uniform Light light;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

vec3 calcDirLight(Light l, vec3 normal, vec3 viewDir){
    float strength = 0.1;

    vec3 L = normalize(-l.vector.xyz);

    vec3 R = reflect(-L,N);  //Costruisce la direzione riflessa di L rispesso alla normale

    vec3 lightCont = l.power / 10 * l.color;
    
    vec3 ambient = strength * lightCont * material.ambient + vec3(0.5);

    float diff = max(dot(N, L),0.0);
    vec3 diffuse = diff * lightCont * material.diffuse;

    float spec = pow(max(dot(V, R), 0.0), material.shininess);
    vec3 specular = strength * spec * lightCont;

    return (ambient + diffuse ) * material.diffuse;
}


void main(void)
{
    vec3 res = calcDirLight(light, N, V);
    FragColor = vec4(res,1);
}
