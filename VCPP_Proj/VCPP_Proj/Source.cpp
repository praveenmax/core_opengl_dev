#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
using namespace std;

GLFWwindow * initializeGLFWwindow(const unsigned int SCREEN_WIDTH, const unsigned int SCREEN_HEIGHT);
void InitializeShaders();

//DISPLAY VARS
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//SHADER VARS
int shaderProgram;
unsigned int VBO, VAO;

int main()
{
	GLFWwindow* window = initializeGLFWwindow(SCR_WIDTH, SCR_HEIGHT);

	//Create a VBO to store vertices
	InitializeShaders();




	// render loop
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.5f,0.5f,0.5f,0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//We tell the renderer to use our compiled shader.
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

		// draw our first triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);


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

void InitializeShaders()
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n\0";

		// build and compile our shader program
		// ------------------------------------
		// vertex shader
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		// check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// fragment shader
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		// check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// link shaders
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// check for linking errors
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, // left  
			0.5f, -0.5f, 0.0f, // right 
			0.0f,  0.5f, 0.0f  // top   
		};


		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//We tell opengl how to interpret vertices data from the current VBO .
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		// Binding '0' as buffer resets the VAO  
		glBindVertexArray(0);
}
