#pragma once
#ifndef __SPHERE_H__
#define __SPHERE_H__

struct sphere_t
{
	vec3    center = vec3(0);   // 3D position for translation
	float   radius = 1.0f;      // radius
	float   phi = 0.0f;       // rotation angle
	vec4    color;              // RGBA color in [0,1]
	mat4    model_matrix;       // modeling transformation

	// public functions
	void    update(float t);
};

inline std::vector<sphere_t> create_sphere()
{
	std::vector<sphere_t> spheres;
	sphere_t c;

	c = { vec3(0),1.0f,0.0f,vec4(1.0f,0.5f,0.5f,1.0f) };
	spheres.emplace_back(c);

	return spheres;
}

inline void sphere_t::update(float p)
{
	//radius = 0.35f + cos(p) * 0.1f;     // simple animation
	radius = 1.0f;
	phi = p;
	float c = cos(phi), s = sin(phi);

	// these transformations will be explained in later transformation lecture
	mat4 scale_matrix =
	{
		radius, 0, 0, 0,
		0, radius, 0, 0,
		0, 0, radius, 0,
		0, 0, 0, 1
	};

	mat4 rotation_matrix =
	{
		c,-s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	mat4 translate_matrix =
	{
		1, 0, 0, center.x,
		0, 1, 0, center.y,
		0, 0, 1, center.z,
		0, 0, 0, 1
	};

	model_matrix = translate_matrix * rotation_matrix * scale_matrix;
}

#endif
