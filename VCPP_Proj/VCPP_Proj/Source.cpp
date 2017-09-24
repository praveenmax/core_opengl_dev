#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

GLFWwindow * initializeGLFWwindow(const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);

//DISPLAY VARS
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	GLFWwindow* window = initializeGLFWwindow(SCR_WIDTH, SCR_HEIGHT);

	// render loop
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.5f,0.5f,0.5f,0);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();

	cout << "Closing GLFW . Bye!"<< endl;
	return 0;
}

/*
	This function creates and assigns a new GLFW Window to the current context.
	Also, loads the OPENGL functions via GLAD
*/
GLFWwindow * initializeGLFWwindow(const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT)
{
	// glfw: initialize and configure
	if (!glfwInit())
	{
		cout << "** ERROR : Failed to initialize GLFW. Terminating now!" << endl;
		return nullptr;
	}
	else
	{
		cout << "Initialized GLFW successfully." << endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Core OpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "** ERROR : Failed to create GLFW window. Terminating now!" << endl;
		glfwTerminate();
		return nullptr;
	}

	//Set this window's context to the calling thread 
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD.Unable to find func pointers for GL functions!" << endl;
		return nullptr;
	}

	return window;
}
