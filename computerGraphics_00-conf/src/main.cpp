#include "gl/glad/glad.h"	// https://github.com/Dav1dde/glad
#define GLFW_INCLUDE_NONE
#include "gl/glfw/glfw3.h"	// http://www.glfw.org
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Hello OpenGL!\n\n");

	// initialization
	if (GLFW_TRUE != glfwInit()) { printf("Failed in glfwInit()\n"); return EXIT_FAILURE; }

	// create invisible window for OpenGL context
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
#ifdef GL_ES_VERSION_2_0	// minimum requirement for modern OpenGL ES (2.0)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__linux__) 	// minimum requirement for linux
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
	GLFWwindow* window = glfwCreateWindow(100, 100, "cgconf - Hello OpenGL", nullptr, nullptr);
	if (!window) { printf("Failed in glfwCreateWindow()\n"); glfwTerminate(); return EXIT_FAILURE; }

	// make the current context and load GL extensions
	glfwMakeContextCurrent(window);
#ifdef GL_ES_VERSION_2_0
	if (!gladLoadGLES2(glfwGetProcAddress)) { printf("Failed in gladLoadGLES2()\n"); glfwTerminate(); return EXIT_FAILURE; }
#else
	if (!gladLoadGL(glfwGetProcAddress)) { printf("Failed in gladLoadGL()\n"); glfwTerminate(); return EXIT_FAILURE; }
#endif

	// check renderer and vendor
	printf("You are using\n");
#ifdef GL_ES_VERSION_2_0
	printf(" - %s\n", glGetString(GL_VERSION));
	printf(" - %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
#else
	printf(" - OpenGL: %s\n", glGetString(GL_VERSION));
	printf(" - OpenGL Shading Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
	printf(" - GPU: %s\n", glGetString(GL_RENDERER));
	printf(" - Vendor: %s\n", glGetString(GL_VENDOR));
	printf("\n");

	glfwDestroyWindow(window);
	glfwTerminate();

#ifdef _MSC_VER
	system("pause");
#endif

	return EXIT_SUCCESS;
}

// in-code linking to glfw lib
#if defined(_glfw3_h_) && defined(_MSC_VER)
#if _MSC_VER>=1920 && !defined(_DLL)
#if defined _M_X64
#pragma comment( lib, "glfw3.x64.lib" ) // static lib for VC2019 or higher
#endif
#else // dynamic lib for other VC version
#if defined _M_X64
#pragma comment( lib, "glfw3dll.x64.lib" ) // dynamic lib for VC2019 or higher
#endif
#endif
#endif

// generate glad implemetation
#define GLAD_GL_IMPLEMENTATION
#ifdef _MSC_VER
#pragma warning( disable: 4551 ) // suppress erroneous warning
#endif
#include "gl/glad/glad.h"	// https://github.com/Dav1dde/glad