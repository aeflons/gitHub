
#version 410 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    //vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    //点光源的二次项系数,不再main中设置了
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    float distance = length(light.position - FragPos);
    float attebustion = 1.0 / (constant + linear * distance + quadratic * pow(distance, 2));
    // ambient
    float cutOff = 0.9985f;
    float outerCutOff = 0.97f;

    //vec3 ambient = light.ambient * material.ambient;
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction);//平行光
    float diff = max(dot(norm, lightDir), 0.0);
   // vec3 diffuse = light.diffuse * (diff * material.diffuse);
    //当使用纹理光照时的代码
    vec3 diffuse = light.diffuse * diff *  texture(material.diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = min(max(dot(viewDir, reflectDir), 0.0),0.2);
    vec3 specular = light.specular  * spec * texture(material.specular, TexCoords).rgb;
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (cutOff - outerCutOff);
    float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    //点光源计算
    vec3 result = ambient + attebustion * diffuse + attebustion * specular;
    //聚光和手电筒
    
    FragColor = vec4(result, 1.0);
}
