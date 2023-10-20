#ifdef GL_ES
	#ifndef GL_FRAGMENT_PRECISION_HIGH	// highp may not be defined
		#define highp mediump
	#endif
	precision highp float; // default precision needs to be defined
#endif

in vec3 vertex_color;	// the second input from vertex shader
out vec4 fragColor;		// define output variable to be shown in the display

// uniform variables will be globally shared among all the fragments
uniform bool	b_solid_color;
uniform vec4	solid_color;
uniform float	theta;	// shared with theta in the vertex shader

void main()
{
	fragColor = b_solid_color ? solid_color : vec4(vertex_color,1);
	fragColor *= abs(sin(theta*4.0)); // modulate color by theta
}
