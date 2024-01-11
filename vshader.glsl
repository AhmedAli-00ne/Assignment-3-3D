#version 150
in vec3 vertexPosition, vertexNormal;
in vec2 vertexTexture;


uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct,
LightPosition;
uniform float Shininess;
out vec3 fE, fN, fL;


uniform mat4 model, view, projection;

out vec3 normal, position;
out vec2 texCoord;

void main()
{
 fN = normalize( model*vec4(vertexNormal, 0.0) ).xyz;
 fE = - vertexPosition.xyz;
 fL = LightPosition.xyz;
 if( LightPosition.w != 0.0 )
 {
 fL = LightPosition.xyz - vertexPosition.xyz;
 }
normal = mat3(transpose(inverse(model))) * vertexNormal;
position = vec3(model * vec4(vertexPosition, 1.0));
texCoord = vertexTexture;
gl_Position = projection * view * vec4(position, 1.0);
}