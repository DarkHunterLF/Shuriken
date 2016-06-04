#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

void main()
{
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0.0; //2d mode
	gl_Position.w = 1.0; // normalised coordinates

	fragmentPosition = vertexPosition;
	
	fragmentColor = vertexColor;
	
	fragmentUV = vertexUV;
}