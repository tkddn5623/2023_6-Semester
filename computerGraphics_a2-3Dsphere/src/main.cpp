#include "cgmath.h"     // slee's simple math library
#include "cgut.h"       // slee's OpenGL utility
#include "sphere.h"     // circle class definition

//*************************************
// global constants
static const char*  window_name = "a2 - sphere";
static const char*  vert_shader_path = "shaders/sphere.vert";
static const char*  frag_shader_path = "shaders/sphere.frag";
uint                EDGE_LONGITUDE = 72;
uint                EDGE_LATITUDE  = 36;

//*************************************
// window objects
GLFWwindow* window = nullptr;
ivec2       window_size = cg_default_window_size(); // initial window size

//*************************************
// OpenGL objects
GLuint  program = 0;        // ID holder for GPU program
GLuint  vertex_array = 0;   // ID holder for vertex array object

//*************************************
// global variables
int     frame = 0;                      // index of rendering frames
float   t = 0.0f;                       // current simulation parameter
uint    u_frag_color_toggle = 0;        // frag color mode 
bool    b_index_buffer = true;          // use index buffering?
bool    b_rotate = false;               // it rotates?
#ifndef GL_ES_VERSION_2_0
bool    b_wireframe = false;
#endif
auto    spheres = std::move(create_sphere());
float   glfwTime_bias = 0.0f;
//*************************************
// holder of vertices and indices of a unit circle
std::vector<vertex> unit_circle_vertices;   // host-side vertices

//*************************************
void update()
{
	// update global simulation parameter
	if (b_rotate) t = (float(glfwGetTime()) - glfwTime_bias);

	// tricky aspect correction matrix for non-square window
	float aspect = window_size.x / float(window_size.y);
	mat4 aspect_matrix =
	{
		std::min(1 / aspect,1.0f), 0, 0, 0,
		0, std::min(aspect,1.0f), 0, 0,
		0, 0, 1, 0, 
		0, 0, 0, 1
	};

	// update common uniform variables in vertex/fragment shaders
	GLint uloc;

	mat4 view_projection_matrix = aspect_matrix * mat4{ 0,1,0,0,0,0,1,0,-1,0,0,1,0,0,0,1 };
	uloc = glGetUniformLocation(program, "view_projection_matrix");  if (uloc > -1) glUniformMatrix4fv(uloc, 1, GL_TRUE, view_projection_matrix);

	uloc = glGetUniformLocation(program, "u_frag_color_toggle");  if (uloc > -1) glUniform1ui(uloc, u_frag_color_toggle);
	uloc = glGetUniformLocation(program, "aspect_matrix");  if (uloc > -1) glUniformMatrix4fv(uloc, 1, GL_TRUE, aspect_matrix);
}

void render()
{
	// clear screen (with background color) and clear depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// notify GL that we use our own program
	glUseProgram(program);

	// bind vertex array object
	glBindVertexArray(vertex_array);

	// render spheres: trigger shader program to process vertex data
	for (auto& s : spheres)
	{
		// per-sphere update
		s.update(t);

		// update per-sphere uniforms
		GLint uloc;
		uloc = glGetUniformLocation(program, "model_matrix"); if (uloc > -1) glUniformMatrix4fv(uloc, 1, GL_TRUE, s.model_matrix);

		// per-sphere draw calls
		if (b_index_buffer) glDrawElements(GL_TRIANGLES, 2 * EDGE_LATITUDE * EDGE_LONGITUDE * 3, GL_UNSIGNED_INT, nullptr);
		else                glDrawArrays(GL_TRIANGLES, 0, 2 * EDGE_LATITUDE * EDGE_LONGITUDE * 3); // NUM_TESS = N
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
#ifndef GL_ES_VERSION_2_0
	printf("- press 'w' to toggle wireframe\n");
#endif
	printf("- press 'd' to toggle (tc.xy,0) > (tc.xxx) > (tc.yyy)\n");
	printf("- press 'r' to rotate the sphere\n");
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

void update_vertex_buffer(const std::vector<vertex>& vertices, uint latitude, uint longitude)
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
		for (uint i = 0; i < latitude; i++) for (uint j = 0; j < longitude; j++)
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
		for (uint i = 0; i < latitude; i++) for (uint j = 0; j < longitude; j++)
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
	if (vertex_array) glDeleteVertexArrays(1, &vertex_array);
	vertex_array = cg_create_vertex_array(vertex_buffer, index_buffer);
	if (!vertex_array) { printf("%s(): failed to create vertex aray\n", __func__); return; }
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q)    glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_H || key == GLFW_KEY_F1)   print_help();
		else if (key == GLFW_KEY_I)
		{
			b_index_buffer = !b_index_buffer;
			update_vertex_buffer(unit_circle_vertices, 36, 72);
			printf("> using %s buffering\n", b_index_buffer ? "index" : "vertex");
		}
		else if (key == GLFW_KEY_D)
		{
			u_frag_color_toggle = (u_frag_color_toggle + 1) % 3;
			switch (u_frag_color_toggle) {
			case 0: printf("> using (texcoord.xy,0) as color\n"); break;
			case 1: printf("> using (texcoord.xxx) as color\n"); break;
			case 2: printf("> using (texcoord.yyy) as color\n"); break;
			}
		}
		else if (key == GLFW_KEY_R)
		{
			b_rotate = !b_rotate;
			if (b_rotate) {
				glfwTime_bias = (float)glfwGetTime() - glfwTime_bias;
			}
			else {
				glfwTime_bias = t;
			}
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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		dvec2 pos; glfwGetCursorPos(window, &pos.x, &pos.y);
		printf("> Left mouse button pressed at (%d, %d)\n", int(pos.x), int(pos.y));
	}
}

void motion(GLFWwindow* window, double x, double y)
{
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
	update_vertex_buffer(unit_circle_vertices, 36, 72);

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
