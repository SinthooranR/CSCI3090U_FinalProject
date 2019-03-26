#version 330 core

uniform mat4 u_MVP_Array;
uniform vec4 u_Colour;

in vec3 position;
out vec4 v_Colour;

void main(){
    // Set the position
    gl_Position = u_MVP_Array * vec4(position, 1.0);
    v_Colour = u_Colour;
}
