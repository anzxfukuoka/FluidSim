#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//

#include "misc/color.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings

// window background color
color windowBg(0.1f, 0.1f, 0.1f, 1.0f);

// ------------

GLFWwindow* mainWindow;

/// <summary>
/// configures opengl
/// </summary>
/// <returns></returns>
void initWindow(int width, int height)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	mainWindow = glfwCreateWindow(width, height, "Fluids", NULL, NULL);
	if (mainWindow == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(mainWindow);
	glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

/// <summary>
/// method for simulation instructions
/// </summary>
void update()
{
}

/// <summary>
/// method for render instructions
/// </summary>
void render()
{

}

/// <summary>
/// starts render loop
/// </summary>
/// <returns></returns>
int showWindow() 
{
	// render loop
	// -----------
	while (!glfwWindowShouldClose(mainWindow)) {
		// input
		// -----
		processInput(mainWindow);

		// update
		// ------

		update();

		// render
		// ------
		glClearColor(windowBg.r, windowBg.g, windowBg.b, windowBg.a);
		glClear(GL_COLOR_BUFFER_BIT);

		render();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



int main() {
	
	initWindow(600, 800);

	int excode = showWindow();

	return excode;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}