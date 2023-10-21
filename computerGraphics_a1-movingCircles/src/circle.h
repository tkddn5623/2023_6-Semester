#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#define CIRCLE_COOLTIME (0.00031)

struct circle_t
{
	vec2    center = vec2(0);   // 2D position for translation
	float   radius = 1.0f;      // radius
	float   theta = 0.0f;       // rotation angle
	vec4    color;              // RGBA color in [0,1]
	vec2    velocity = vec2(0);
	mat4    model_matrix;       // modeling transformation
	double  last_conflict = 0.0f;
	// public functions
	void    update(float theta);
};

inline float randf(float bound, int type) // A1: Pesudo random
{
	static bool _init = 0;
	if (!_init) { _init = 1; srand((unsigned)time(NULL)); }
	if (type == 0) return ((float)rand() / RAND_MAX) * 0.999f * bound;
	else return (((float)rand() / RAND_MAX) * 1.999f * bound) - bound;
}
inline void reset_circles(std::vector<circle_t>& circles, int size);
inline std::vector<circle_t> create_circles(int size)
{
	std::vector<circle_t> circles;
	circle_t c;

	//c = { vec2(0.0f,0.0f),0.1f,0.0f,vec4(1.0f,0.5f,0.5f,1.0f), vec2(0.0003f, 0.0001f) };
	//circles.push_back(c);

	//c = { vec2(+1.0f,+0.50f),0.5f,0.0f,vec4(0.5f,1.0f,1.0f,1.0f), vec2(-0.0000f, -0.0000f) };
	//circles.push_back(c);
	reset_circles(circles, 40);

	return circles;
}

inline void reset_circles(std::vector<circle_t>& circles, int size) // A1 : Reset circles
{
	float radius_max = (float)(1.0 / sqrt(size));
	float radius_min = radius_max / 7;
	circle_t c;

	circles.clear();
	for (int i = 0; i < size; i++) {
		float x, y;
		bool retry;
		do {
			retry = false;
			do { c.radius = randf(radius_max, 0); } while (c.radius <= radius_min);
			x = randf(1.5f - c.radius, 1);
			y = randf(1.0f - c.radius, 1);
			c.center = vec2(x, y);
			for (int j = 0; j < i; j++) {
				circle_t& c_temp = circles.at(j);
				float dist = (c.center - c_temp.center).length();
				if (dist <= c.radius + c_temp.radius) { retry = true; break; }
			}
		} while (retry);
		c.color = vec4(0.5f, 1.0f, 1.0f, 1.0f);
		c.velocity = vec2(randf(0.0002f, 1), randf(0.0002f, 1));
		circles.push_back(c);
	}
}

inline void conflict_circles(std::vector<circle_t>& circles) { // A1: Elastic collision ( every after update() )
	int size = (int)circles.size();
	for (int i = 0; i < size; i++) for (int j = 0; j < i; j++) {
		circle_t& c1 = circles.at(i);
		circle_t& c2 = circles.at(j);
		float dist = (c1.center - c2.center).length();
		double t1 = glfwGetTime();
		if (dist <= c1.radius + c2.radius && t1 - c1.last_conflict > CIRCLE_COOLTIME && t1 - c2.last_conflict > CIRCLE_COOLTIME) {
			vec2 temp = c1.velocity;
			c1.velocity = c2.velocity;
			c2.velocity = temp;
			double t2 = glfwGetTime();
			c1.last_conflict = t2;
			c2.last_conflict = t2;
		}
	}
	for (auto& c : circles) {
		if ((c.center[0] + c.radius >= 1.5f && c.velocity[0] > 0) ||
			(c.center[0] - c.radius <= -1.5f && c.velocity[0] < 0))
			c.velocity[0] = -c.velocity[0];
		if ((c.center[1] + c.radius >= 1.0f && c.velocity[1] > 0) ||
			(c.center[1] - c.radius <= -1.0f && c.velocity[1] < 0))
			c.velocity[1] = -c.velocity[1];
	}
}

inline void circle_t::update(float theta)
{
	//radius = 0.35f + cos(theta) * 0.1f;     // simple animation
	float c = cos(theta), s = sin(theta);
	center += velocity;                       // A1: Center move

	// these transformations will be explained in later transformation lecture
	mat4 scale_matrix =
	{
		radius, 0, 0, 0,
		0, radius, 0, 0,
		0, 0, 1, 0,
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
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	model_matrix = translate_matrix * rotation_matrix * scale_matrix;
}

#endif
