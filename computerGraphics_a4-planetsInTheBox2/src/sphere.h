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
	float	t_last_render = 0;
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

inline std::vector<sphere_t> create_sphere(int num = 9)
{
	std::vector<sphere_t> spheres;
	sphere_t s;
	for (int i = 0; i < num; i++) {
		s.radius = 7.0f * (i + 1);
		bool retry;
		do {
			retry = false;
			float bias = s.radius * 1.1f;
			s.center = vec3(randf(480 - 2 * bias, 0) + bias, randf(480 - 2 * bias, 0) + bias, randf(480 - 2 * bias, 0) + bias);
			for (int j = 0; j < i; j++) {
				sphere_t& s_temp = spheres.at(j);
				float dist = (s.center - s_temp.center).length();
				if (dist * 0.7 <= s.radius + s_temp.radius) { retry = true; break; }
			}
		} while (retry);
		s.velocity = vec3(randf(0.05f, 1), randf(0.04f, 1), randf(0.03f, 1));
		//c.last_update_time = glfwTime;
		spheres.push_back(s);
	}
	return spheres;
}

inline void sphere_t::update(float p)
{
	phi = p;
	float c = cos(phi), s = sin(phi);

	// The animation should use timestamps instead of the frame counter
	if (phi - t_last_render >= 0.0005f) {
		t_last_render = phi;
		center += velocity;
	}

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

	// model_matrix = translate_matrix * rotation_matrix * scale_matrix;
	model_matrix = translate_matrix * scale_matrix;
}

inline void conflict_spheres(std::vector<sphere_t>& spheres) { // A1: Elastic collision ( every after update() )
	static const vec3 CORNELL_COORD[] = {
	vec3(552.8f,0,0),
	vec3(0,0,0),
	vec3(0,0,559.2f),
	vec3(549.6f,0,559.2f),
	vec3(556.0f,548.8f,0),
	vec3(556.0f,548.8f,559.2f),
	vec3(0,548.8f,559.2f),
	vec3(0,548.8f,0),
	};
	for (auto& s : spheres) {
		vec3 plane_norm;
		float distance;

		// Floor
		plane_norm = ((CORNELL_COORD[1] - CORNELL_COORD[0]).cross(CORNELL_COORD[2] - CORNELL_COORD[0])).normalize();
		distance = plane_norm.dot((s.center - CORNELL_COORD[0]));
		distance = distance >= 0 ? distance : -distance;
		if (distance <= s.radius) s.velocity = -s.velocity;
		
		// Ceiling
		plane_norm = ((CORNELL_COORD[5] - CORNELL_COORD[4]).cross(CORNELL_COORD[6] - CORNELL_COORD[4])).normalize();
		distance = plane_norm.dot((s.center - CORNELL_COORD[4]));
		distance = distance >= 0 ? distance: -distance;
		if (distance <= s.radius) s.velocity = -s.velocity;
		
		// Back
		plane_norm = ((CORNELL_COORD[3] - CORNELL_COORD[2]).cross(CORNELL_COORD[5] - CORNELL_COORD[2])).normalize();
		distance = plane_norm.dot((s.center - CORNELL_COORD[2]));
		distance = distance >= 0 ? distance: -distance;
		if (distance <= s.radius) s.velocity = -s.velocity;

		// Right
		plane_norm = ((CORNELL_COORD[2] - CORNELL_COORD[1]).cross(CORNELL_COORD[6] - CORNELL_COORD[1])).normalize();
		distance = plane_norm.dot((s.center - CORNELL_COORD[1]));
		distance = distance >= 0 ? distance: -distance;
		if (distance <= s.radius) s.velocity = -s.velocity;

		// Left
		plane_norm = ((CORNELL_COORD[3] - CORNELL_COORD[0]).cross(CORNELL_COORD[4] - CORNELL_COORD[0])).normalize();
		distance = plane_norm.dot((s.center - CORNELL_COORD[0]));
		distance = distance >= 0 ? distance : -distance;
		if (distance <= s.radius) s.velocity = -s.velocity;

		// Front
		plane_norm = ((CORNELL_COORD[1] - CORNELL_COORD[0]).cross(CORNELL_COORD[4] - CORNELL_COORD[0])).normalize();
		distance = plane_norm.dot((s.center - CORNELL_COORD[0]));
		distance = distance >= 0 ? distance : -distance;
		if (distance <= s.radius) s.velocity = -s.velocity;

	}
	int size = (int)spheres.size();
	for (int i = 0; i < size; i++) for (int j = 0; j < i; j++) {
		sphere_t& s1 = spheres.at(i);
		sphere_t& s2 = spheres.at(j);
		float dist = (s1.center - s2.center).length();
		if (dist <= s1.radius + s2.radius) {
			vec3 temp = s1.velocity;
			s1.velocity = s2.velocity;
			s2.velocity = temp;
		}
	}
}

#endif
