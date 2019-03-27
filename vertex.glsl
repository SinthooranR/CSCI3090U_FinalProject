#version 330 core

uniform mat4 u_MVP_Array;
uniform mat4 u_MV;

in vec4 position;
in vec2 textureCoords;
in vec3 normal;

uniform vec4 u_Colour;
uniform vec4 u_DiffuseColour;
uniform vec3 u_LightPos;



out vec4 v_Colour;

void main(){
    // Set the position
    gl_Position = u_MVP_Array * position; 

	vec3 position_viewspace = vec3(u_MV * position);
	vec3 normal_viewspace = normalize(vec3(u_MV * vec4(normal, 0.0)));

	float distance = length(u_LightPos - position_viewspace);

	vec3 lightVector_viewspace = normalize(u_LightPos - position_viewspace);

	// ambient
   vec4 ambientColour = u_Colour * u_DiffuseColour;

   // diffuse
   float diffuse = clamp(dot(normal_viewspace, lightVector_viewspace), 0, 1);
    
		
	v_Colour = u_DiffuseColour * diffuse + ambientColour;
   gl_Position = u_MVP_Array * position;

}
