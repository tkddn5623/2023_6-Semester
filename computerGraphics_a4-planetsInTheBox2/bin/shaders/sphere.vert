// input attributes of vertices
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texcoord;

// outputs
out vec3 norm;	// the second output: not used yet
out vec2 tc;	// the third output: not used yet

// uniform variables
uniform mat4	model_matrix;	// 4x4 transformation matrix: explained later in the lecture
uniform mat4	view_matrix;
uniform mat4	projection_matrix;

void main()
{
	vec4 wpos = model_matrix * vec4(position,1);
	vec4 epos = view_matrix * wpos;
	gl_Position = projection_matrix * epos;

	norm = normal;
	// norm = normalize(mat3(view_matrix*model_matrix)*normal);
}