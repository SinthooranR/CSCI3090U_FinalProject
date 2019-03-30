#version 330 core

out vec4 outColor;
in vec2 text_coords;
in vec3 pos_viewspace;
in vec3 norm_viewspace;

uniform vec3 u_LightPos;
uniform sampler2D textureSampler;

uniform vec4 u_Colour;
uniform vec4 u_DiffuseColour;
uniform bool u_ShaderTextureSwap;

void main(){
	vec3 lightVector_viewspace = normalize(u_LightPos - pos_viewspace);
  vec4 ambientColour = u_Colour * u_DiffuseColour;
  float diffuse = clamp(dot(norm_viewspace, lightVector_viewspace), 0, 1);

  if(u_ShaderTextureSwap){
  outColor = vec4(texture(textureSampler, text_coords).rgb, 1.0);
  }
  else{
  outColor = u_DiffuseColour * diffuse + ambientColour;;
  }
}
