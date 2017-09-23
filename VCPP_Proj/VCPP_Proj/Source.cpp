

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW. Terminating now!" << endl;
		return -1;
	}
	else
	{
		cout << "Initialized GLFW successfully." << endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD.Unable to find func pointers for GL functions!" << endl;
		return -1;
	}

	// render loop
	while (!glfwWindowShouldClose(window))
	{

		// render
		// ------
		glClearColor(0.5f,0.5f,0.5f,0);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.

	glfwTerminate();

	cout << "Closing GLFW . Bye!"<< endl;
	return 0;
}
