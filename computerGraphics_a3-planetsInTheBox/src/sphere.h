#pragma once
#ifndef __SPHERE_H__
#define __SPHERE_H__

struct sphere_t
{
	vec3    center = vec3(0);   // 3D position for translation
	float   radius = 10.0f;     // radius
	float   phi = 0.0f;         // rotation angle
	vec4    color;              // RGBA color in [0,1]
	vec3	velocity = vec3(0); // Return of velocity of A1!
	mat4    model_matrix;       // modeling transformation

	// public functions
	void    update(float t);
};

inline float randf(float bound, int type) // A1: Pesudo random
{
	static bool _init = 0;
	if (!_init) { _init = 1; srand((unsigned)time(NULL)); }
	if (type == 0) return ((float)rand() / RAND_MAX) * 0.999f * bound;
	else return (((float)rand() / RAND_MAX) * 1.999f * bound) - bound;
}

inline std::vector<sphere_t> create_sphere()
{
	std::vector<sphere_t> spheres;
	sphere_t c;
	for (int i = 0; i < 1; i++) {
		c = { vec3(250,250,250),20.0f,0.0f,vec4(1.0f,0.5f,0.5f,1.0f),vec3(0.0f,0.0f,0.0f)};
	}
	
	spheres.emplace_back(c);

	return spheres;
}

inline void sphere_t::update(float p)
{
	phi = p;
	float c = cos(phi), s = sin(phi);
	center += velocity;
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

inline void conflict_spheres(std::vector<sphere_t>& spheres) { // A1: Elastic collision ( every after update() )
	int size = (int)spheres.size();
	for (auto& c : spheres) {
		
	}
	/*for (int i = 0; i < size; i++) for (int j = 0; j < i; j++) {
		circle_t& c1 = spheres.at(i);
		circle_t& c2 = spheres.at(j);
		float dist = (c1.center - c2.center).length();
		if (dist <= c1.radius + c2.radius) {
			vec2 temp = c1.velocity;
			c1.velocity = c2.velocity;
			c2.velocity = temp;
		}
	}*/
}

#endif
