#ifdef GL_ES
	#ifndef GL_FRAGMENT_PRECISION_HIGH	// highp may not be defined
		#define highp mediump
	#endif
	precision highp float; // default precision needs to be defined
#endif

// input from vertex shader
in vec4 epos;
in vec3 norm;
in vec2 tc;

// the only output variable
out vec4 fragColor;

// uniform variables
uniform mat4	view_matrix;
uniform float	shininess;
uniform vec4	light_position, Ia, Id, Is;	// light
uniform vec4	Ka, Kd, Ks;					// material properties
uniform vec4	planet[9];					// planet (wpos, rad) array
uniform int		planet_idx;					// current planet number (-1 means it is a wall)
uniform int		planet_size;				// planet size

// texture sampler
uniform sampler2D TEX;


bool intersect_sphere(vec3 ray_pos, vec3 ray_dir, vec4 plane)
{
	//vec3 planet_epos = (view_matrix * plane).xyz;
	//float planet_erad = plane.w;
	
	//if ((planet_epos - ray_pos).length() >= planet_erad) return true;

	return false;
}
bool is_fragment_in_shadows(vec4 lpos)
{
	return false;

	//vec3 ray_dir = normalize((lpos - epos).xyz);
	//for (int i = 0; i < planet_size; i++) {
	//	if (planet_idx == i) continue;
	//	else if (intersect_sphere(epos.xyz, ray_dir, planet[i])) return true;
	//}
	//return false;
}
vec4 phong( vec3 l, vec3 n, vec3 h, vec4 Kd )
{
	vec4 Ira = Ka*Ia;									// ambient reflection
	vec4 Ird = max(Kd*dot(l,n)*Id,0.0);					// diffuse reflection
	vec4 Irs = max(Ks*pow(dot(h,n),shininess)*Is,0.0);	// specular reflection
	return Ira + Ird + Irs;
}
void main()
{
	// light position in the eye space
	vec4 lpos = view_matrix * light_position;

	vec3 n = normalize(norm);	// norm interpolated via rasterizer should be normalized again here
	vec3 p = epos.xyz;			// 3D position of this fragment
	vec3 l = normalize(lpos.xyz-(lpos.a==0.0?vec3(0):p));	// lpos.a==0 means directional light
	vec3 v = normalize(-p);		// eye-epos = vec3(0)-epos
	vec3 h = normalize(l+v);	// the halfway vector

	vec4 iKd = texture( TEX, tc );	// Kd from image

	if (planet_idx == -1) fragColor = phong(l, n, h, Kd);
	else fragColor = phong(l, n, h, iKd);


	// if (!is_fragment_in_shadows(lpos)) fragColor = phong(l, n, h, iKd);
	// else fragColor = vec4(norm, 1.0);
	
	//fragColor = vec4(norm, 1.0);
}
