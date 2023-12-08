/*
* main_window.h
* manages window creation and open gl features
*/
#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "misc/color.h"

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window);

/// <summary>
/// configures opengl
/// </summary>
/// <returns></returns>
void initWindow(int width, int height, std::string windowTitle);

/// <summary>
/// method for simulation instructions
/// </summary>
void update();

/// <summary>
/// method for render instructions
/// </summary>
void render();

/// <summary>
/// starts render loop
/// </summary>
/// <returns></returns>
int showWindow();