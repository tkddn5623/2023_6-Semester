#include "cgmath.h"     // slee's simple math library
#include "cgut.h"       // slee's OpenGL utility
#include "light.h"      // cg_a4 header
#include "sphere.h"     // circle class definition
#include "trackball.h"	// virtual trackball

//*************************************
// global constants
static const char*  window_name = "a4";
static const char*  vert_shader_path = "shaders/sphere.vert";
static const char*  frag_shader_path = "shaders/sphere.frag";
static const uint   EDGE_LATITUDE = 36;
static const uint   EDGE_LONGITUDE = 72;
static const camera	home = camera(vec3(278, 274.4f,-680), vec3(278, 274.4f, 559), vec3(0, 548.8f, 0));
static const enum	CORNELL_NUM { C_FLOOR, C_CEILING, C_BACK, C_RIGHT, C_LEFT, C_FRONT, } _cn;
static const int	CORNELL_NUM_OF_WALLS = 6;
static const vec3	CORNELL_COORD[] = {
	vec3(552.8f,0,0),
	vec3(0,0,0),
	vec3(0,0,559.2f),
	vec3(549.6f,0,559.2f),
	vec3(556.0f,548.8f,0),
	vec3(556.0f,548.8f,559.2f),
	vec3(0,548.8f,559.2f),
	vec3(0,548.8f,0),
};

//*************************************
// window objects
GLFWwindow* window = nullptr;
ivec2       window_size = cg_default_window_size(); // initial window size

//*************************************
// OpenGL objects
GLuint  program = 0;						// ID holder for GPU program
GLuint  vertex_array_sphere = 0;			// ID holder for sphere VAO
GLuint  vertex_array_cornell[6] = { 0 };	// ID holder for cornell VAO

//*************************************
// global variables
#ifndef GL_ES_VERSION_2_0
bool    b_wireframe = false;
#endif
int     frame			= 0;	// index of rendering frames
float   t				= 0.0f;	// current simulation parameter
bool    b_index_buffer	= true;	// use index buffering?
auto    spheres			= std::move(create_sphere());
GLuint	tex_num[9]		= { 0 };
//*************************************
// scene objects
camera		cam = home;
trackball	tb;
light_t		light = {
	vec4(278.0f,278.0f,0.1f,1.0f), vec4(0.0f,0.0f,0.0f,1.0f), vec4(0.78f,0.78f,0.78f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f)
};
material_t	material_sphere = {
	vec4(0.2f,0.2f,0.2f,1.0f), vec4(0.8f,0.8f,0.8f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f), 1000.0f
};
material_t	material_wall[6] = {
	{vec4(0.2f,0.2f,0.2f,1.0f), vec4(0.725f,0.710f,0.680f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f), 1000.0f},
	{vec4(0.2f,0.2f,0.2f,1.0f), vec4(0.725f,0.710f,0.680f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f), 1000.0f},
	{vec4(0.2f,0.2f,0.2f,1.0f), vec4(0.725f,0.710f,0.680f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f), 1000.0f},
	{vec4(0.2f,0.2f,0.2f,1.0f), vec4(0.137f,0.447f,0.090f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f), 1000.0f},
	{vec4(0.2f,0.2f,0.2f,1.0f), vec4(0.630f,0.065f,0.050f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f), 1000.0f},
	{vec4(0.2f,0.2f,0.2f,1.0f), vec4(0.725f,0.710f,0.680f,1.0f), vec4(1.0f,1.0f,1.0f,1.0f), 1000.0f},
};

// holder of vertices and indices of a unit circle
std::vector<vertex> unit_circle_vertices;		// host-side vertices
std::vector<vertex> unit_cornell_vertices[6];	// cornell vertices

//*************************************
void update()
{
	// update global simulation parameter
	t = float(glfwGetTime());

	// update projection matrix
	cam.aspect = window_size.x / float(window_size.y);
	cam.projection_matrix = mat4::perspective(cam.fovy, cam.aspect, cam.dnear, cam.dfar);

	GLint uloc;
	uloc = glGetUniformLocation(program, "view_matrix");		if (uloc > -1) glUniformMatrix4fv(uloc, 1, GL_TRUE, cam.view_matrix);
	uloc = glGetUniformLocation(program, "projection_matrix");	if (uloc > -1) glUniformMatrix4fv(uloc, 1, GL_TRUE, cam.projection_matrix);

	// setup light properties
	glUniform4fv(glGetUniformLocation(program, "light_position"), 1, light.position);
	glUniform4fv(glGetUniformLocation(program, "Ia"), 1, light.ambient);
	glUniform4fv(glGetUniformLocation(program, "Id"), 1, light.diffuse);
	glUniform4fv(glGetUniformLocation(program, "Is"), 1, light.specular);

	// uniform planet vector (cg_a4)
	std::vector<float> planet_v;
	uloc = glGetUniformLocation(program, "planet");
	if (uloc > -1) {
		for (auto& s : spheres) {
			planet_v.push_back(s.center.x);
			planet_v.push_back(s.center.y);
			planet_v.push_back(s.center.z);
			planet_v.push_back(s.radius);
		}
		glUniform4fv(uloc, (GLsizei)spheres.size(), &planet_v[0]);
	}
	uloc = glGetUniformLocation(program, "planet_size"); if (uloc > -1) glUniform1i(uloc, (int)spheres.size());
}

void render()
{
	GLint uloc;

	// clear screen (with background color) and clear depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// notify GL that we use our own program
	glUseProgram(program);

	// Draw sphere first.
	glBindVertexArray(vertex_array_sphere);

	// setup material properties
	glUniform4fv(glGetUniformLocation(program, "Ka"), 1, material_sphere.ambient);
	glUniform4fv(glGetUniformLocation(program, "Kd"), 1, material_sphere.diffuse);
	glUniform4fv(glGetUniformLocation(program, "Ks"), 1, material_sphere.specular);
	glUniform1f(glGetUniformLocation(program, "shininess"), material_sphere.shininess);

	int idx = 0;
	for (auto& s : spheres)
	{
		// per-sphere update
		s.update(t);

		// update per-sphere uniforms
		uloc = glGetUniformLocation(program, "planet_idx"); if (uloc > -1) glUniform1i(uloc, idx);
		uloc = glGetUniformLocation(program, "model_matrix"); if (uloc > -1) glUniformMatrix4fv(uloc, 1, GL_TRUE, s.model_matrix);

		// setup texture
		glActiveTexture(GL_TEXTURE0);								// select the texture slot to bind
		glBindTexture(GL_TEXTURE_2D, tex_num[idx]);
		glUniform1i(glGetUniformLocation(program, "TEX"), 0);		// GL_TEXTURE0

		idx++;

		// per-sphere draw calls
		if (b_index_buffer) glDrawElements(GL_TRIANGLES, 2 * (EDGE_LATITUDE + 1) * (EDGE_LONGITUDE + 1) * 3, GL_UNSIGNED_INT, nullptr);
		else                glDrawArrays(GL_TRIANGLES, 0, 2 * (EDGE_LATITUDE + 1) * (EDGE_LONGITUDE + 1) * 3); 
	}
	conflict_spheres(spheres);


	// let shader thinks it is a wall
	uloc = glGetUniformLocation(program, "planet_idx"); if (uloc > -1) glUniform1i(uloc, -1);

	// Then draw cornell walls
	for (int i = 0; i < CORNELL_NUM_OF_WALLS; i++) {
		// setup material properties
		glUniform4fv(glGetUniformLocation(program, "Ka"), 1, material_wall[i].ambient);
		glUniform4fv(glGetUniformLocation(program, "Kd"), 1, material_wall[i].diffuse);
		glUniform4fv(glGetUniformLocation(program, "Ks"), 1, material_wall[i].specular);
		glUniform1f(glGetUniformLocation(program, "shininess"), material_wall[i].shininess);

		glBindVertexArray(vertex_array_cornell[i]);
		uloc = glGetUniformLocation(program, "model_matrix"); if (uloc > -1) glUniformMatrix4fv(uloc, 1, GL_TRUE, mat4::identity());
		if (b_index_buffer) glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		else                glDrawArrays(GL_TRIANGLES, 0, 6); 
	}


	// swap front and back buffers, and display to screen
	glfwSwapBuffers(window);
}

void reshape(GLFWwindow* window, int width, int height)
{
	// set current viewport in pixels (win_x, win_y, win_width, win_height)
	// viewport: the window area that are affected by rendering 
	window_size = ivec2(width, height);
	glViewport(0, 0, width, height);
}

void print_help()
{
	printf("[help]\n");
	printf("- press ESC or 'q' to terminate the program\n");
	printf("- press F1 or 'h' to see help\n");
	printf("- press 'i' to toggle between index buffering and simple vertex buffering\n");
	printf("- press Home to reset camera\n");
#ifndef GL_ES_VERSION_2_0
	printf("- press 'w' to toggle wireframe\n");
#endif
	printf("\n");
}

std::vector<vertex> create_sphere_vertices(uint latitude, uint longitude)
{
	std::vector<vertex> v;
	for (uint i = 0; i <= latitude; i++) for (uint j = 0; j <= longitude; j++) 
	{
		float t = PI * 1.0f * i / float(latitude), p = PI * 2.0f * j / float(longitude);
		float st = sin(t), ct = cos(t), sp = sin(p), cp = cos(p);
		v.push_back({ vec3(st * cp,st * sp,ct),vec3(st * cp, st * sp, ct), vec2(p / 2, PI - t) / PI });
	}
	return v;
}

std::vector<vertex> create_cornell_vertices(uint num)
{
	std::vector<vertex> v;
	vec3 norm;
	switch (num) {
	case C_FLOOR:
		norm = (CORNELL_COORD[2] - CORNELL_COORD[1]).cross(CORNELL_COORD[0] - CORNELL_COORD[1]).normalize();
		v.push_back({ CORNELL_COORD[0],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[1],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[2],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[3],norm,vec2(0) });
		break;
	case C_CEILING:
		norm = (CORNELL_COORD[6] - CORNELL_COORD[5]).cross(CORNELL_COORD[4] - CORNELL_COORD[5]).normalize();
		v.push_back({ CORNELL_COORD[4],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[5],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[6],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[7],norm,vec2(0) });
		break;
	case C_BACK:
		norm = (CORNELL_COORD[6] - CORNELL_COORD[2]).cross(CORNELL_COORD[3] - CORNELL_COORD[2]).normalize();
		v.push_back({ CORNELL_COORD[3],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[2],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[6],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[5],norm,vec2(0) });
		break;
	case C_RIGHT:
		norm = (CORNELL_COORD[7] - CORNELL_COORD[1]).cross(CORNELL_COORD[2] - CORNELL_COORD[1]).normalize();
		v.push_back({ CORNELL_COORD[2],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[1],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[7],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[6],norm,vec2(0) });
		break;
	case C_LEFT:
		norm = (CORNELL_COORD[5] - CORNELL_COORD[3]).cross(CORNELL_COORD[0] - CORNELL_COORD[3]).normalize();
		v.push_back({ CORNELL_COORD[0],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[3],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[5],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[4],norm,vec2(0) });
		break;
	case C_FRONT:
		norm = (CORNELL_COORD[4] - CORNELL_COORD[0]).cross(CORNELL_COORD[1] - CORNELL_COORD[0]).normalize();
		v.push_back({ CORNELL_COORD[1],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[0],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[4],norm,vec2(0) });
		v.push_back({ CORNELL_COORD[7],norm,vec2(0) });
		break;
	}
	return v;
}

void update_sphere_vertex_buffer(const std::vector<vertex>& vertices, uint latitude, uint longitude)
{
	static GLuint vertex_buffer = 0;    // ID holder for vertex buffer
	static GLuint index_buffer = 0;     // ID holder for index buffer

	// clear and create new buffers
	if (vertex_buffer)  glDeleteBuffers(1, &vertex_buffer); vertex_buffer = 0;
	if (index_buffer)   glDeleteBuffers(1, &index_buffer);  index_buffer = 0;

	// check exceptions
	if (vertices.empty()) { printf("[error] vertices is empty.\n"); return; }

	// create buffers
	if (b_index_buffer)
	{
		std::vector<uint> indices;
		for (uint i = 0; i <= latitude; i++) for (uint j = 0; j <= longitude; j++)
		{
			indices.push_back(i * (longitude + 1) + j);
			indices.push_back((i + 1) * (longitude + 1) + j);
			indices.push_back(i * (longitude + 1) + j + 1);
			
			indices.push_back(i * (longitude + 1) + j + 1);
			indices.push_back((i + 1) * (longitude + 1) + j);
			indices.push_back((i + 1) * (longitude + 1) + j + 1);
		}

		// generation of vertex buffer: use vertices as it is
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		// geneation of index buffer
		glGenBuffers(1, &index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}
	else
	{
		std::vector<vertex> v; // triangle vertices
		for (uint i = 0; i <= latitude; i++) for (uint j = 0; j <= longitude; j++)
		{
			v.push_back(vertices[i * (longitude + 1) + j]);
			v.push_back(vertices[(i + 1) * (longitude + 1) + j]);
			v.push_back(vertices[i * (longitude + 1) + j + 1]);

			v.push_back(vertices[i * (longitude + 1) + j + 1]);
			v.push_back(vertices[(i + 1) * (longitude + 1) + j]);
			v.push_back(vertices[(i + 1) * (longitude + 1) + j + 1]);
		}

		// generation of vertex buffer: use triangle_vertices instead of vertices
		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * v.size(), &v[0], GL_STATIC_DRAW);
	}

	// generate vertex array object, which is mandatory for OpenGL 3.3 and higher
	if (vertex_array_sphere) glDeleteVertexArrays(1, &vertex_array_sphere);
	vertex_array_sphere = cg_create_vertex_array(vertex_buffer, index_buffer);
	if (!vertex_array_sphere) { printf("%s(): failed to create vertex aray\n", __func__); return; }
}
void update_cornell_vertex_buffer(const std::vector<vertex>& vertices, int num)
{
	static GLuint vertex_buffer[6];    // ID holder for vertex buffer
	static GLuint index_buffer[6];     // ID holder for index buffer

	// clear and create new buffers
	if (vertex_buffer[num])  glDeleteBuffers(1, &vertex_buffer[num]); vertex_buffer[num] = 0;
	if (index_buffer[num])   glDeleteBuffers(1, &index_buffer[num]);  index_buffer[num] = 0;

	// check exceptions
	if (vertices.empty()) { printf("[error] vertices is empty.\n"); return; }

	// create buffers
	if (b_index_buffer)
	{
		std::vector<uint> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
		// generation of vertex buffer: use vertices as it is
		glGenBuffers(1, &vertex_buffer[num]);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[num]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		// geneation of index buffer
		glGenBuffers(1, &index_buffer[num]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer[num]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}
	else
	{
		std::vector<vertex> v; // triangle vertices
		v.push_back(vertices[0]);
		v.push_back(vertices[1]);
		v.push_back(vertices[2]);

		v.push_back(vertices[0]);
		v.push_back(vertices[2]);
		v.push_back(vertices[3]);
		// generation of vertex buffer: use triangle_vertices instead of vertices
		glGenBuffers(1, &vertex_buffer[num]);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[num]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * v.size(), &v[0], GL_STATIC_DRAW);
	}

	// generate vertex array object, which is mandatory for OpenGL 3.3 and higher
	if (vertex_array_cornell[num]) glDeleteVertexArrays(1, &vertex_array_cornell[num]);
	vertex_array_cornell[num] = cg_create_vertex_array(vertex_buffer[num], index_buffer[num]);
	if (!vertex_array_cornell[num]) { printf("%s(): failed to create vertex aray\n", __func__); return; }
}
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)    glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_H || key == GLFW_KEY_F1)   print_help();
		else if (key == GLFW_KEY_HOME) {
			cam = home;
		}
		else if (key == GLFW_KEY_I)
		{
			b_index_buffer = !b_index_buffer;
			update_sphere_vertex_buffer(unit_circle_vertices, 36, 72);
			for (int i = 0; i < CORNELL_NUM_OF_WALLS; i++) {
				update_cornell_vertex_buffer(unit_cornell_vertices[i], i);
			}
			printf("> using %s buffering\n", b_index_buffer ? "index" : "vertex");
		}
#ifndef GL_ES_VERSION_2_0
		else if (key == GLFW_KEY_W)
		{
			b_wireframe = !b_wireframe;
			glPolygonMode(GL_FRONT_AND_BACK, b_wireframe ? GL_LINE : GL_FILL);
			printf("> using %s mode\n", b_wireframe ? "wireframe" : "solid");
		}
#endif
	}
}

void mouse(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		dvec2 pos; glfwGetCursorPos(window, &pos.x, &pos.y);
		vec2 npos = cursor_to_ndc(pos, window_size);
		tb.button = button;
		tb.mods = mods;
		if (action == GLFW_PRESS)			tb.begin(cam, npos);
		else if (action == GLFW_RELEASE)	tb.end();
	}
}

void motion(GLFWwindow* window, double x, double y)
{
	if (!tb.is_tracking()) return;
	vec2 npos = cursor_to_ndc(dvec2(x, y), window_size);
	if (tb.button == GLFW_MOUSE_BUTTON_LEFT && tb.mods == 0)
		cam = tb.update(npos);
	else if (tb.button == GLFW_MOUSE_BUTTON_MIDDLE ||
		(tb.button == GLFW_MOUSE_BUTTON_LEFT && (tb.mods & GLFW_MOD_CONTROL)))
		cam = tb.update_pan(npos);
	else if (tb.button == GLFW_MOUSE_BUTTON_RIGHT ||
		(tb.button == GLFW_MOUSE_BUTTON_LEFT && (tb.mods & GLFW_MOD_SHIFT)))
		cam = tb.update_zoom(npos);
}

bool user_init()
{
	// log hotkeys
	print_help();

	// init GL states
	glLineWidth(1.0f);
	glClearColor(39 / 255.0f, 40 / 255.0f, 34 / 255.0f, 1.0f);  // set clear color
	glEnable(GL_CULL_FACE);                                     // turn on backface culling
	glEnable(GL_DEPTH_TEST);                                    // turn on depth tests

	// define the position of four corner vertices
	unit_circle_vertices = std::move(create_sphere_vertices(36, 72));

	// create vertex buffer; called again when index buffering mode is toggled
	update_sphere_vertex_buffer(unit_circle_vertices, 36, 72);
	for (int i = 0; i < CORNELL_NUM_OF_WALLS; i++) {
		unit_cornell_vertices[i] = std::move(create_cornell_vertices(i));
		update_cornell_vertex_buffer(unit_cornell_vertices[i], i);
	}
	// load texture
	tex_num[0] = cg_create_texture("textures/mercury.jpg", true);
	tex_num[1] = cg_create_texture("textures/venus.jpg", true);
	tex_num[2] = cg_create_texture("textures/earth.jpg", true);
	tex_num[3] = cg_create_texture("textures/mars.jpg", true);
	tex_num[4] = cg_create_texture("textures/jupiter.jpg", true);
	tex_num[5] = cg_create_texture("textures/saturn.jpg", true);
	tex_num[6] = cg_create_texture("textures/uranus.jpg", true);
	tex_num[7] = cg_create_texture("textures/neptune.jpg", true);
	tex_num[8] = cg_create_texture("textures/sun.jpg", true);

	return true;
}

void user_finalize()
{
}

int main(int argc, char* argv[])
{
	// create window and initialize OpenGL extensions
	if (!(window = cg_create_window(window_name, window_size.x, window_size.y))) { glfwTerminate(); return 1; }
	if (!cg_init_extensions(window)) { glfwTerminate(); return 1; } // init OpenGL extensions

	// initializations and validations of GLSL program
	if (!(program = cg_create_program(vert_shader_path, frag_shader_path))) { glfwTerminate(); return 1; }  // create and compile shaders/program
	if (!user_init()) { printf("Failed to user_init()\n"); glfwTerminate(); return 1; }                 // user initialization

	// register event callbacks
	glfwSetWindowSizeCallback(window, reshape); // callback for window resizing events
	glfwSetKeyCallback(window, keyboard);       // callback for keyboard events
	glfwSetMouseButtonCallback(window, mouse);  // callback for mouse click inputs
	glfwSetCursorPosCallback(window, motion);   // callback for mouse movements

	// enters rendering/event loop
	for (frame = 0; !glfwWindowShouldClose(window); frame++)
	{
		glfwPollEvents();   // polling and processing of events
		update();           // per-frame update
		render();           // per-frame render
	}

	// normal termination
	user_finalize();
	cg_destroy_window(window);
}
