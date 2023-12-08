#include "windowmain.h"

// window background color
color windowBg;//(0.1f, 0.1f, 0.1f, 1.0f);
GLFWwindow* mainWindow;

void initWindow(int width, int height, std::string windowTitle, color windowBackgroundColor)
{

	windowBg = windowBackgroundColor;

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
	mainWindow = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);
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
};

int showWindow(Renderer *renderer, void (*update)())
{
	renderer->initRenderBuffers();

	// render loop
	// -----------
	while (!glfwWindowShouldClose(mainWindow)) {
		// input
		// -----
		processInput(mainWindow);

		// update
		// ------

		//update();
		update();

		// render
		// ------
		glClearColor(windowBg.r, windowBg.g, windowBg.b, windowBg.a);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer->render();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
};


void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
};