// Vertex Shader – file "minimal.vert"

#version 140

in  vec3 in_Position;
in  vec3 in_Color;

uniform mat4 mvp;
uniform mat4 ;
uniform mat4 ;
uniform vec3 ;

out vec3 ex_Color;

void main(void)
{
	gl_Position = mvp * vec4(in_Position, 1.0);
	ex_Color = in_Color;
}