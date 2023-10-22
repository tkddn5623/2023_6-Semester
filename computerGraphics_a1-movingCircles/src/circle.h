#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__

extern ivec2 window_size;

struct circle_t
{
	vec2    center = vec2(0);   // 2D position for translation
	float   radius = 1.0f;      // radius
	float   theta = 0.0f;       // rotation angle
	vec4    color;              // RGBA color in [0,1]
	vec2    velocity = vec2(0);
	float   last_update_time = 0;
	mat4    model_matrix;       // modeling transformation
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

inline float get_width_ratio(const ivec2& window_size) 
{
	if (window_size[0] >= window_size[1]) return (float)window_size[0] / window_size[1];
	else return 1.0f;
}

inline float get_height_ratio(const ivec2& window_size) 
{
	if (window_size[0] <= window_size[1]) return (float)window_size[1] / window_size[0];
	else return 1.0f;
}

inline void reset_circles(std::vector<circle_t>& circles, int size, float glfwTime) // A1: Reset circles
{
	float radius_max = (float)(1.0 / sqrt(size));
	float radius_min = radius_max / 4;
	float width_ratio = get_width_ratio(window_size);
	float height_ratio = get_height_ratio(window_size);
	circle_t c;

	circles.clear();
	for (int i = 0; i < size; i++) {
		// A1 spec: The initial positions of circles avoid overlaps
		// and collisions with the other circles and walls
		bool retry;
		do {
			retry = false;
			do { c.radius = randf(radius_max, 0); } while (c.radius <= radius_min);
			c.center = vec2(randf(width_ratio - c.radius, 1), randf(height_ratio - c.radius, 1));
			for (int j = 0; j < i; j++) {
				circle_t& c_temp = circles.at(j);
				float dist = (c.center - c_temp.center).length();
				if (dist * 0.8f <= c.radius + c_temp.radius) { retry = true; break; }
			}
		} while (retry);
		c.color = vec4(randf(1.0f, 0), randf(1.0f, 0), randf(1.0f, 0), 1.0f);
		c.velocity = vec2(randf(0.0004f, 1) + 0.00005f, randf(0.0004f, 1) + 0.00005f);
		c.last_update_time = glfwTime;
		circles.push_back(c);
	}
}

inline std::vector<circle_t> create_circles(int size, float glfwTime)
{
	std::vector<circle_t> circles;
	reset_circles(circles, size, glfwTime);
	return circles;
}

inline void conflict_circles(std::vector<circle_t>& circles) { // A1: Elastic collision ( every after update() )
	float width_ratio = get_width_ratio(window_size);
	float height_ratio = get_height_ratio(window_size);
	int size = (int)circles.size();
	for (auto& c : circles) {
		if ((c.center[0] + c.radius >= width_ratio && c.velocity[0] > 0) ||
			(c.center[0] - c.radius <= -width_ratio && c.velocity[0] < 0))
			c.velocity[0] = -c.velocity[0];
		if ((c.center[1] + c.radius >= height_ratio && c.velocity[1] > 0) ||
			(c.center[1] - c.radius <= -height_ratio && c.velocity[1] < 0))
			c.velocity[1] = -c.velocity[1];
	}
	for (int i = 0; i < size; i++) for (int j = 0; j < i; j++) {
		circle_t& c1 = circles.at(i);
		circle_t& c2 = circles.at(j);
		float dist = (c1.center - c2.center).length();
		if (dist <= c1.radius + c2.radius) {
			vec2 temp = c1.velocity;
			c1.velocity = c2.velocity;
			c2.velocity = temp;
		}
	}
}

inline void circle_t::update(float glfwTime)
{
	float c = cos(glfwTime), s = sin(glfwTime);
	if (last_update_time > 0.1f) {
		// A1 sepc: use a time difference between consecutive frames
		// to define the movement of circles; so I implement like this
		center += velocity * (glfwTime - last_update_time) * 7000.0f;  
	}
	last_update_time = glfwTime;

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
