#version 330 core
out vec4 FragColor;

in vec3 pos;
in vec3 color;
in vec3 normal;
in vec3 fragpos;

uniform vec3 campos;
uniform vec3 camdir;

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;

    float cutOff;
    float outerCutOff;

    int type;
};

#define LIGHTS_COUNT 1
uniform Light lights[LIGHTS_COUNT];

vec3 GlobalLight(Light light, vec3 normal, vec3 viewdir)
{
    vec3 ambient = light.ambient * light.ambientIntensity;
        
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * light.diffuseIntensity;  
        
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewdir, reflectDir), 0.0), 32.0);
    vec3 specular = light.specular * spec * light.specularIntensity;
        
    return ambient + diffuse + specular;
}

vec3 PointLight(Light light, vec3 normal, vec3 viewdir)
{
    vec3 ambient = light.ambient * light.ambientIntensity;
        
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * light.diffuseIntensity;  
        
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewdir, reflectDir), 0.0), 32.0);
    vec3 specular = light.specular * spec * light.specularIntensity;

    float distance = length(light.position - fragpos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                        light.quadratic * (distance * distance));
    return ambient * attenuation + diffuse * attenuation + specular * attenuation;
}

vec3 SpotLight(Light light, vec3 normal, vec3 viewdir)
{
    
    vec3 lightDir = normalize(-light.direction);
    vec3 ambient = light.ambient * light.ambientIntensity;

    float angle = dot(viewdir, lightDir);
    if (angle > light.outerCutOff) {
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * light.diffuseIntensity;  
                
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewdir, reflectDir), 0.0), 32.0);
    vec3 specular = light.specular * spec * light.specularIntensity;

    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    diffuse *= intensity;
    specular *= intensity;

    float distance = length(light.position - fragpos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
                    light.quadratic * (distance * distance));
    return ambient + diffuse * attenuation + specular * attenuation;
    } else {
        return ambient;
    }
}

vec3 CalcLight(Light light, vec3 normal, vec3 viewdir)
{
    if (light.type == 0) {
        return GlobalLight(light, normal, viewdir);
    } else if (light.type == 1) {
        return PointLight(light, normal, viewdir);
    } else if (light.type == 2) {
        return SpotLight(light, normal, viewdir);    
    }
}

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(campos - fragpos);

    vec3 result = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < LIGHTS_COUNT; i++)
        result += CalcLight(lights[i], norm, viewDir) * color.xyz;
    FragColor = vec4(result, 1.0f);
} 