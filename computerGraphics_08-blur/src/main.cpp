#include "cgmath.h"		// slee's simple math library
#include "cgut.h"		// slee's OpenGL utility

//*************************************
// global constants
static const char*	window_name = "cgbase - separable blur";
static const char*	vert_shader_path = "shaders/blur.vert";
static const char*	frag_shader_path = "shaders/blur.frag";
static const char*	image_path = "images/lena.jpg";

//*************************************
// window objects
GLFWwindow*	window = nullptr;
ivec2		window_size = ivec2( 512, 512 );

//*************************************
// OpenGL objects
GLuint	program	= 0;		// ID holder for GPU program
GLuint  vertex_array = 0;	// ID holder for vertex array object
GLuint	fbo = 0;			// framebuffer objects
GLuint	SRC = 0, HORZ=0;	// texture objects

//*************************************
// global variables
int		frame=0;	// index of rendering frames
ivec2	image_size;
vec2	sigma = 0.5f;
struct { bool left=false, right=false, up=false, down=false; operator bool() const { return left||right||up||down;} } b;

//*************************************
void update()
{
	static auto clamp = []( float v, float m, float M )->float { return v<m?m:v>M?M:v; };

	// do not use "else if" to enable key combination
	if(b.left)	sigma.x = clamp( sigma.x-0.5f, 0.5f, 40.0f );
	if(b.right)	sigma.x = clamp( sigma.x+0.5f, 0.5f, 40.0f );
	if(b.up)	sigma.y = clamp( sigma.y+0.5f, 0.5f, 40.0f );
	if(b.down)	sigma.y = clamp( sigma.y-0.5f, 0.5f, 40.0f );

	if(b) printf( "blur kernel size = (% 6.1f, % 6.1f)\r", sigma.x, sigma.y );	
}

void draw_quad()
{
	// clear screen (with background color) and clear depth buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// bind vertex array object
	glBindVertexArray( vertex_array );

	// render quad vertices
	glDrawArrays( GL_TRIANGLES, 0, 6 );
}

void render()
{
	// separable Gaussian filtering
	glUseProgram( program );
	
	// horizontal blur phase using render-to-texture
	glBindFramebuffer( GL_FRAMEBUFFER, fbo );												// bind frame buffer object
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, HORZ, 0 );	// attach texture to frame buffer object
	glUniform1i( glGetUniformLocation( program, "TEX"), 0 );
	glBindTexture( GL_TEXTURE_2D, SRC );
	glUniform1f( glGetUniformLocation( program, "sigma" ), sigma.x );
	glUniform2fv( glGetUniformLocation( program, "texel_offset" ), 1, vec2(1.0f/image_size.x,0) );
	draw_quad(); // off-screen rendering
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 0, 0, 0 );				// detach texture from frame buffer object

	// vertical blur phase and display directly
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );													// unbind frame buffer object: render to the default frame buffer
	glUniform1i( glGetUniformLocation( program, "TEX"), 0 );
	glBindTexture( GL_TEXTURE_2D, HORZ );
	glUniform1f( glGetUniformLocation( program, "sigma" ), sigma.y );
	glUniform2fv( glGetUniformLocation( program, "texel_offset" ), 1, vec2(0,1.0f/image_size.y) );
	draw_quad(); // on-screen rendering
	
	// read-back: uncomment this when you need read back the frame buffer
	// static uchar* buffer = (uchar*) malloc( image_size.x*image_size.y*3 );
	// glReadPixels( 0, 0, image_size.x, image_size.y, GL_RGB, GL_UNSIGNED_BYTE, buffer );
	
	// swap front and back buffers, and display to screen
	glfwSwapBuffers( window );
}

void reshape( GLFWwindow* window, int width, int height )
{
	// set current viewport in pixels (win_x, win_y, win_width, win_height)
	// viewport: the window area that are affected by rendering 
	window_size = ivec2( width, height );
	glViewport( 0, 0, width, height );
	
	// update texture size
	void update_render_target_textures( int width, int height );
	update_render_target_textures( width, height );
}

void print_help()
{
	printf( "[help]\n" );
	printf( "- press ESC or 'q' to terminate the program\n" );
	printf( "- press F1 or 'h' to see help\n" );
	printf( "- press left/right to increase/decrease horizontal blur\n" );
	printf( "- press up/down to increase/decrease vertical blur\n" );
	printf( "\n" );
}

void keyboard( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	if(action==GLFW_PRESS)
	{
		if(key==GLFW_KEY_ESCAPE||key==GLFW_KEY_Q)	glfwSetWindowShouldClose( window, GL_TRUE );
		else if(key==GLFW_KEY_H||key==GLFW_KEY_F1)	print_help();
		else if(key==GLFW_KEY_LEFT)		b.left	= true;
		else if(key==GLFW_KEY_RIGHT)	b.right	= true;
		else if(key==GLFW_KEY_UP)		b.up	= true;
		else if(key==GLFW_KEY_DOWN)		b.down	= true;
	}
	else if(action==GLFW_RELEASE)
	{
		if(key==GLFW_KEY_LEFT)			b.left	= false;
		else if(key==GLFW_KEY_RIGHT)	b.right	= false;
		else if(key==GLFW_KEY_UP)		b.up	= false;
		else if(key==GLFW_KEY_DOWN)		b.down	= false;
	}
}

void mouse( GLFWwindow* window, int button, int action, int mods )
{
}

void motion( GLFWwindow* window, double x, double y )
{
}

void update_render_target_textures( int width, int height )
{
	if(HORZ) glDeleteTextures( 1, &HORZ );

	// since we are using render-to-texture, we resize the textures by the window size
	glGenTextures( 1, &HORZ);
	glBindTexture( GL_TEXTURE_2D, HORZ );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
}

bool user_init()
{
	// log hotkeys
	print_help();

	// init GL states
	glClearColor( 39/255.0f, 40/255.0f, 34/255.0f, 1.0f );	// set clear color
	glEnable( GL_CULL_FACE );			// turn on backface culling
	glEnable( GL_DEPTH_TEST );			// turn on depth tests
	glEnable( GL_TEXTURE_2D );			// enable texturing
	glActiveTexture( GL_TEXTURE0 );		// notify GL the current texture slot is 0

	// create corners and vertices
	vertex corners[4];
	corners[0].pos=vec3(-1.0f, -1.0f, 0.0f);	corners[0].tex = vec2(0.0f, 0.0f);
	corners[1].pos=vec3(+1.0f, -1.0f, 0.0f);	corners[1].tex = vec2(1.0f, 0.0f);
	corners[2].pos=vec3(+1.0f, +1.0f, 0.0f);	corners[2].tex = vec2(1.0f, 1.0f);
	corners[3].pos=vec3(-1.0f, +1.0f, 0.0f);	corners[3].tex = vec2(0.0f, 1.0f);
	vertex vertices[6] = { corners[0], corners[1], corners[2], corners[0], corners[2], corners[3] };

	// generation of vertex buffer is the same, but use vertices instead of corners
	GLuint vertex_buffer;
	glGenBuffers( 1, &vertex_buffer );
	glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// generate vertex array object, which is mandatory for OpenGL 3.3 and higher
	if(vertex_array) glDeleteVertexArrays(1,&vertex_array);
	vertex_array = cg_create_vertex_array( vertex_buffer );
	if(!vertex_array){ printf("%s(): failed to create vertex aray\n",__func__); return false; }

	// create a frame buffer object for render-to-texture
	glGenFramebuffers( 1, &fbo );
	glBindFramebuffer( GL_FRAMEBUFFER, fbo );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	// load the image with vertical flipping
	image* i = cg_load_image( image_path ); if(!i) return false;
	image_size = i->size;
	
	// create a src texture (Lena texture)
	SRC = cg_create_texture( i, false, GL_REPEAT ); if(!SRC) return false;

	// update render target textures by the window size
	update_render_target_textures( window_size.x, window_size.y );
	
	return true;
}

void user_finalize()
{
}

int main( int argc, char* argv[] )
{
	// create window and initialize OpenGL extensions
	if(!(window = cg_create_window( window_name, window_size.x, window_size.y ))){ glfwTerminate(); return 1; }
	if(!cg_init_extensions( window )){ glfwTerminate(); return 1; }	// version and extensions

	// initializations and validations
	if(!(program=cg_create_program( vert_shader_path, frag_shader_path ))){ glfwTerminate(); return 1; }	// create and compile shaders/program
	if(!user_init()){ printf( "Failed to user_init()\n" ); glfwTerminate(); return 1; }					// user initialization

	// register event callbacks
	glfwSetWindowSizeCallback( window, reshape );	// callback for window resizing events
    glfwSetKeyCallback( window, keyboard );			// callback for keyboard events
	glfwSetMouseButtonCallback( window, mouse );	// callback for mouse click inputs
	glfwSetCursorPosCallback( window, motion );		// callback for mouse movement

	// enters rendering/event loop
	for( frame=0; !glfwWindowShouldClose(window); frame++ )
	{
		glfwPollEvents();	// polling and processing of events
		update();			// per-frame update
		render();			// per-frame render
	}
	
	// normal termination
	user_finalize();
	cg_destroy_window(window);

	return 0;
}
