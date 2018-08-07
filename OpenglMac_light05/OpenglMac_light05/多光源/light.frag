#version 410 core
out vec4 FragColor;
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
//平行光
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//点光
struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};
//聚光手电筒
struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform SpotLight spotLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
  
    // 属性
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // 第一阶段：定向光照
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // 第二阶段：点光源
    for(int i = 0; i < NR_POINT_LIGHTS; i++){
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
    // 第三阶段：聚光
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    FragColor = vec4(result, 1.0);
}
//定向光
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    //漫反射着色
    float diff = max(dot(normal,lightDir),0.0);
   //镜面反射着色
    vec3 reflectDir = reflect(-lightDir,normal);
 float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);    //合并结果
    vec3 ambient = light.ambient * texture(material.diffuse,TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    return (ambient + diffuse + specular);
}
//点光源
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(-light.position - fragPos);
    //漫反射着色
    float diff = max(dot(normal,lightDir),0.0);
    //镜面反射着色
    vec3 reflectDir = reflect(-lightDir,normal);
 float spec = max(pow(max(dot(viewDir,reflectDir),0.0),material.shininess),1.0f);
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance));
    
    //合并结果
    vec3 ambient = light.ambient * texture(material.diffuse,TexCoords).rgb * attenuation;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb * attenuation;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb * attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    vec3 lightDir = normalize(-light.position - fragPos);
    //漫反射着色
    float diff = max(dot(normal,lightDir),0.0);
    //镜面反射着色
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = 1.0;
    
    // 衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                               light.quadratic * (distance * distance)) * 100;
    
    //合并结果
    vec3 ambient = light.ambient * texture(material.diffuse,TexCoords).rgb * attenuation;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb * attenuation;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb * attenuation;
    
//    float theta = dot(lightDir, normalize(-light.direction));
//    float epsilon = (light.cutOff - light.outerCutOff);
//    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    float cutOff = 0.9985f;
    float outerCutOff = 0.98f;
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (cutOff - outerCutOff);
    float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    return (ambient + diffuse + specular);

}
