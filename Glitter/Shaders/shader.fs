#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

// // Coordinates to start the repetition from
uniform float center_u;
uniform float center_v;

// // Set scale for uv coordinates
uniform float scale_u;
uniform float scale_v;

// // Number of elements along each axis
uniform int elements_u;
uniform int elements_v;

uniform float u_angle;

void main()
{
    vec2 center = vec2(center_u, center_v);
    vec2 scale = vec2(scale_u, scale_v);
    float sin_factor = sin(u_angle);
    float cos_factor = cos(u_angle);
    vec2 bounds = vec2(float(elements_u/2), float(elements_v/2));

    //  Compute absolute offset from center
	vec2 offset = scale * (TexCoord - center);
	offset = (offset - TexCoord) * mat2(cos_factor, sin_factor, -sin_factor, cos_factor);
	offset += TexCoord;

    // Do texture lookup based on the vertices texture coordinates
    vec4 bg_color = texture(texture1, TexCoord);
    vec4 quad_texture = texture(texture2, offset);
	if (all(lessThan(abs(offset), bounds))) {
	    FragColor = mix(bg_color,quad_texture, 0.9);
	} else {
	    FragColor = bg_color;
	}
}