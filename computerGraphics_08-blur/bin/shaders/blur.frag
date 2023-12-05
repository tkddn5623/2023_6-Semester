#version 330

// input from vertex shader
in vec2 tc;

// the only output variable
out vec4 fragColor;

uniform sampler2D	TEX;
uniform float		sigma;
uniform vec2		texel_offset;

void main()
{	
	fragColor = vec4(0);
	for( float x=-4.0*sigma, max=4.0*sigma; x<=max; x+=1.0 )
	{
		float weight = exp(-0.5*(x*x)/(sigma*sigma));
		vec4 texel = texture( TEX, tc+x*texel_offset );
		fragColor += vec4( texel.rgb, 1 )*weight;
	}
	fragColor /= fragColor.a;
}
