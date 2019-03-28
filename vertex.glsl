#version 330 core

uniform mat4 u_MVP_Array;
uniform mat4 u_MV;

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normal;

out vec3 pos_viewspace;
out vec3 norm_viewspace;
out vec2 text_coords;


void main(){

	pos_viewspace = vec3(u_MV * position);
	norm_viewspace = normalize(vec3(u_MV * vec4(normal, 0.0)));
   text_coords = textureCoords;

   // Set the position
   gl_Position = u_MVP_Array * position; 

}
