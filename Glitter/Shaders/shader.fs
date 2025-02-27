#version 330 core
out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    //vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform Material material;
uniform Light light;

// texture samplers
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;

// // Coordinates to start the repetition from
uniform float center_u;
uniform float center_v;

// // Set scale for uv coordinates
uniform float scale_u;
uniform float scale_v;

// Number of elements along each axis
uniform int elements_u;
uniform int elements_v;

uniform float u_angle;

void main()
{
    vec2 center = vec2(center_u, center_v);
    vec2 scale = vec2(scale_u, scale_v);
    float sin_factor = sin(u_angle);
    float cos_factor = cos(u_angle);
    vec2 bounds = vec2(float(elements_u/2), float(elements_u/2));

    //  Compute absolute offset from center
	vec2 offset = scale * (TexCoord - center);

    // ambient
    vec3 ambient = light.ambient * light.diffuse; // * texture(material.diffuse, TexCoord).rgb; 
      	
    // diffuse 
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff; // * texture(material.diffuse, TexCoord).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec; // * texture(material.specular, TexCoord).rgb;

    // Do texture lookup based on the vertices texture coordinates
    // color of U coord
    float texCoordX = TexCoord.x;
    float texCoordY = TexCoord.y;
    float tempX = texCoordX - int(texCoordX);
    float tempY = texCoordY - int(texCoordY);
    int fracPartX = int(tempX*10);
    int fracPartY = int(tempY*10);
    vec3 color = vec3(0.0, 0.0, 0.0);
    switch (fracPartX) {
        case 0:
            color += vec3(0.0, 1.0, 0.0);
            break;
        case 1:
            color += vec3(0.0, 0.1, 0.0);
            break;
        case 2:
            color += vec3(0.0, 0.2, 0.0);
            break;
        case 3:
            color += vec3(0.0, 0.3, 0.0);
            break;
        case 4:
            color += vec3(0.0, 0.4, 0.0);
            break;
        case 5:
            color += vec3(0.0, 0.5, 0.0);
            break;
        case 6:
            color += vec3(0.0, 0.6, 0.0);
            break;
        case 7:
            color += vec3(0.0, 0.7, 0.0);
            break;
        case 8:
            color += vec3(0.0, 0.8, 0.0);
            break;
        case 9:
            color += vec3(0.0, 0.9, 0.0);
            break;
        default:
            color += vec3(0.0, 0.0, 0.0);
    }
    // frag color for v coord
    switch (fracPartY) {
        case 0:
            color += vec3(1.0, 0.0, 0.0);
            break;
        case 1:
            color += vec3(0.1, 0.0, 0.0);
            break;
        case 2:
            color += vec3(0.2, 0.0, 0.0);
            break;
        case 3:
            color += vec3(0.3, 0.0, 0.0);
            break;
        case 4:
            color += vec3(0.4, 0.0, 0.0);
            break;
        case 5:
            color += vec3(0.5, 0.0, 0.0);
            break;
        case 6:
            color += vec3(0.6, 0.0, 0.0);
            break;
        case 7:
            color += vec3(0.7, 0.0, 0.0);
            break;
        case 8:
            color += vec3(0.8, 0.0, 0.0);
            break;
        case 9:
            color += vec3(0.9, 0.0, 0.0);
            break;
        default:
            color += vec3(0.0, 0.0, 0.0);
    }

    vec4 bg_color = texture(texture_diffuse1, TexCoord);
    vec3 tempLighting = (ambient + diffuse + specular);
    vec4 quad_texture = texture(texture_diffuse2, offset);
    vec4 bgColorEnd = vec4(tempLighting * objectColor, 1.0) * bg_color;
    vec4 quadTexEnd = vec4(tempLighting*color, 1.0) * quad_texture;
	if (all(lessThan(abs(offset), bounds))) {
	    FragColor = mix(bgColorEnd,quadTexEnd, 1.0);
	}else {
        FragColor = bgColorEnd;
    }
}