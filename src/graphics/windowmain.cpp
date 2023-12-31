#include "windowmain.h"

// window background color
color windowBg;//(0.1f, 0.1f, 0.1f, 1.0f);
GLFWwindow* mainWindow;

// mouse relative screen pos
// updates every frame
double mousePosX, mousePosY;

void initWindow(int width, int height, std::string windowTitle, color windowBackgroundColor)
{
	windowBg = windowBackgroundColor;

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GLFW_TRUE); // GLFW_FALSE // enable system window frame
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // window transparency
	//glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE); //  ignore mouse click and let it pass to the windows behind

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

int showWindow(FluidRenderer *renderer, void (*update)(), int updateSpeed)
{
	renderer->initRenderBuffers();

	int ticks = 0;
	int time = 0;

	// render loop
	// -----------
	while (!glfwWindowShouldClose(mainWindow)) {

		time++;

		if (time % updateSpeed != 0)
		{
			continue;
		}

		// input
		// -----
		processInput(mainWindow);

		// update
		// ------

		//update();
		update();

		// render
		// ------

		//clear background
		glClearColor(windowBg.r, windowBg.g, windowBg.b, windowBg.a);
		glClear(GL_COLOR_BUFFER_BIT);

		//ebable alpha
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

		renderer->render();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(mainWindow);
		glfwPollEvents();

		ticks++;
		//std::cout << "ticks: " << ticks << std::endl;
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
};

glm::vec2 getMousePosition() 
{
	return glm::vec2(mousePosX, mousePosY);
}

void processInput(GLFWwindow* window) {

	// exit 
	// ------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, true);
	}

	// mouse
	// -----
	int winWidth, winHeight;
	double xpos, ypos;

	glfwGetWindowSize(window, &winWidth, &winHeight);
	glfwGetCursorPos(window, &xpos, &ypos);

	mousePosX = (xpos / winWidth - 0.5f) * 2;
	mousePosY = (ypos / winHeight - 0.5f) * 2;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
};