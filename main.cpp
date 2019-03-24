#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>
#include <GL/glew.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

int windowId = 0;

// projection matrix - perspective projection
glm::mat4 projectionMatrix;

// view matrix - orient everything around our preferred view
glm::mat4 viewMatrix;

GLuint programId;
GLuint vertexBuffer;
GLuint indexBuffer;
GLenum positionBufferId;

float xRotation = 0.0f;
float yRotation = 0.0f;
float zRotation = 0.0f;

float yRotationSpeed = 0.1f;

float minArmRotation = 45.0f;
float maxArmRotation = 160.0f;
float upperArmRotation = 45.0f;
float upperArmRotationSpeed = 1.0f;

void drawFinger(glm::vec3 basePosition);
void drawSquare(glm::mat4 modelMatrix, glm::vec4 colour);
static GLuint createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
static GLuint createShader(const GLenum shaderType, const std::string shaderSource);

static const GLfloat vertexPositionData[] = {
    -1.0f, -1.0f,  1.0f,  // front
     1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,

};
static const GLushort indexData[] = {
  0, 1, 2,   // front
  3, 2, 1,

};

// static const GLushort normalData[] = {

// }

int numVertices = 6;

static void createGeometry(void) {
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionData), vertexPositionData, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexData), indexData, GL_STATIC_DRAW);

  //   glGenBuffers(1, &normals_vbo);
  // glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
  // glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(glm::vec3), vertexNormals, GL_STATIC_DRAW);
}

static void update(void) {
    int milliseconds = glutGet(GLUT_ELAPSED_TIME);

    // rotate the entire model, to that we can examine it
    yRotation += yRotationSpeed;

    glutPostRedisplay();
}

static void render(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // turn on depth buffering
  glEnable(GL_DEPTH_TEST);

  // activate our shader program
  glUseProgram(programId);

  // colours
  glm::vec4 red(0.3, 0.0, 1.0, 1.0);

  glm::mat4 modelMatrix = glm::mat4(1.0f);
 
  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));

  modelMatrix = glm::rotate(modelMatrix,glm::radians(90.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,0,1));

  modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
  //modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1, 1.0, 1.0));
  drawSquare(modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -2.5f, 0.0f));

  drawSquare(modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, 0.0f));

  drawSquare(modelMatrix, red);

  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, 0.0f));

  drawSquare(modelMatrix, red);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.25f, 0.0f, 0.0f));

  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(90.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,0,1));

  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.25f, 0.0f, 0.0f));

  drawSquare(modelMatrix, red);

  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, 0.0f));

  drawSquare(modelMatrix, red);

  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, 0.0f));

  drawSquare(modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));

  drawSquare(modelMatrix, red);

  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));

  drawSquare(modelMatrix, red);
  // TODO:  Draw the fingers (and thumb)
  //glm::vec3 base(0.0,0.0,0.0);
  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.25f, 0.0f));

  modelMatrix = glm::rotate(modelMatrix,glm::radians(90.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,0,1));
  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.25f, 0.0f));

  drawSquare(modelMatrix, red);

  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));

  drawSquare(modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));

  drawSquare(modelMatrix, red);

  modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5f, 0.0f, 0.0f));

  drawSquare(modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5f, 0.0f, 0.0f));

  drawSquare(modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -2.5f, 0.0f));

  drawSquare(modelMatrix, red);



  glutSwapBuffers();
}

void drawFinger(glm::vec3 basePosition) {
  // colours
  glm::vec4 colour1(0.8, 0.0, 0.5, 1.0);
  glm::vec4 colour2(0.0, 0.0, 0.8, 1.0);
  glm::vec4 colour3(0.0, 0.5, 0.5, 1.0);

  // TODO:  Draw three transformed cubes to make the finger
  
  glm::mat4 newmodelMatrix = glm::mat4(1.0f);
  newmodelMatrix = glm::scale(newmodelMatrix, glm::vec3(0.5f, 0.8f, 0.5f));
  newmodelMatrix = glm::translate(newmodelMatrix, basePosition + glm::vec3(-3.8f, 0.0f, 0.0f));
  drawSquare(newmodelMatrix, colour1);
  
  // glm::mat4 newmodelMatrix1 = glm::mat4(1.0f);
  // newmodelMatrix1 = glm::scale(newmodelMatrix1, glm::vec3(0.5f, 0.8f, 0.5f));
  // newmodelMatrix1 = glm::translate(newmodelMatrix1, basePosition + glm::vec3(-3.8f, 2.5f, 0.0f));
  // drawSquare(newmodelMatrix1, colour2);

  // glm::mat4 newmodelMatrix2 = glm::mat4(1.0f);
  // newmodelMatrix2 = glm::scale(newmodelMatrix2, glm::vec3(0.5f, 0.8f, 0.5f));
  // newmodelMatrix2 = glm::translate(newmodelMatrix2, basePosition + glm::vec3(-3.8f, 5.0f, 0.0f));
  // drawSquare(newmodelMatrix2, colour3);
  

}

void drawSquare(glm::mat4 modelMatrix, glm::vec4 colour) {
  // model-view-projection matrix
  glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
  GLuint mvpMatrixId = glGetUniformLocation(programId, "u_MVP");
  glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvp[0][0]);

  // cube colour
  GLuint colourId = glGetUniformLocation(programId, "u_colour");
  glUniform4fv(colourId, 1, (GLfloat*)&colour[0]);
	
  // 	// find the names (ids) of each vertex attribute
	// GLint positionAttribId = glGetAttribLocation(programId, "position");
	// GLint textureCoordsAttribId = glGetAttribLocation(programId, "textureCoords");
	// GLint normalAttribId = glGetAttribLocation(programId, "normal");

  // // the position of our light
	// GLuint lightPosId = glGetUniformLocation(programId, "u_LightPos");
	// glUniform3f(lightPosId, 1, 8 + lightOffsetY, -2);

	// // the colour of our object
	// GLuint diffuseColourId = glGetUniformLocation(programId, "u_DiffuseColour");
	// glUniform4f(diffuseColourId, d_Colour.x, d_Colour.y, d_Colour.z, 1.0);

	// // provide the vertex positions to the shaders
	// glBindBuffer(GL_ARRAY_BUFFER, positions_vbo);
	// glEnableVertexAttribArray(positionAttribId);
	// glVertexAttribPointer(positionAttribId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// // provide the vertex texture coordinates to the shaders
	// glBindBuffer(GL_ARRAY_BUFFER, textureCoords_vbo);
	// glEnableVertexAttribArray(textureCoordsAttribId);
	// glVertexAttribPointer(textureCoordsAttribId, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	// // provide the vertex normals to the shaders
	// glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	// glEnableVertexAttribArray(normalAttribId);
	// glVertexAttribPointer(normalAttribId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // enable the vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

  // configure the attribute array (the layout of the vertex buffer)
  glVertexAttribPointer(positionBufferId, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void *)0);
  glEnableVertexAttribArray(positionBufferId);

  // draw the triangle strip
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_SHORT, (void*)0);

  // disable the attribute array
  glDisableVertexAttribArray(positionBufferId);
}

static void reshape(int width, int height) {
    float aspectRatio = (float)width / (float)height;
    projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);

    // if using perpsective projection, update projection matrix
    glViewport(0, 0, width, height);
}

static void drag(int x, int y) {
}

static void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {

    }
}

static void keyboard(unsigned char key, int x, int y) {
    if (key == 'r') {
      if (yRotationSpeed > 0.0) {
        yRotationSpeed = 0.0;
      } else {
        yRotationSpeed = 0.1;
      }
    } else if (key == 27) {
      glutDestroyWindow(windowId);
      exit(0);
    }
    std::cout << "Key pressed: " << key << std::endl;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    windowId = glutCreateWindow("Lab 02");
    glutIdleFunc(&update);
    glutDisplayFunc(&render);
    glutReshapeFunc(&reshape);
    glutMotionFunc(&drag);
    glutMouseFunc(&mouse);
    glutKeyboardFunc(&keyboard);

    glewInit();
    if (!GLEW_VERSION_2_0) {
        std::cerr << "OpenGL 2.0 not available" << std::endl;
        return 1;
    }
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "Using OpenGL " << glGetString(GL_VERSION) << std::endl;

    createGeometry();
    programId = createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

    // create the view matrix (position and orient the camera)
    viewMatrix = glm::lookAt(
        glm::vec3(-50,30,50), // eye/camera location
        glm::vec3(0,-2,0),    // where to look
        glm::vec3(0,3,0)     // up
    );

    glutMainLoop();

    return 0;
}

static GLuint createShader(const GLenum shaderType, const std::string shaderFilename) {
  // load the shader source code
  std::ifstream fileIn(shaderFilename.c_str());

	if (!fileIn.is_open()) {
		return -1;
	}

	std::string shaderSource;
	std::string line;
	while (getline(fileIn, line)) {
		shaderSource.append(line);
		shaderSource.append("\n");
	}

	const char* sourceCode = shaderSource.c_str();

	// create a shader with the specified source code
	GLuint shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &sourceCode, nullptr);

	// compile the shader
	glCompileShader(shaderId);

	// check if there were any compilation errors
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int errorLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &errorLength);
		char *errorMessage = new char[errorLength];

		glGetShaderInfoLog(shaderId, errorLength, &errorLength, errorMessage);
		std::cout << "Shader compilation failed: " << errorMessage << std::endl;

		delete[] errorMessage;

		glDeleteShader(shaderId);

		return 0;
	}

	return shaderId;
}

static GLuint createShaderProgram(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename) {
	// create and compile a shader for each
	GLuint vShaderId = createShader(GL_VERTEX_SHADER, vertexShaderFilename);
	GLuint fShaderId = createShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);

	// create and link the shaders into a program
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);
	glLinkProgram(programId);
	glValidateProgram(programId);

	// delete the shaders
	glDetachShader(programId, vShaderId);
	glDetachShader(programId, fShaderId);
	glDeleteShader(vShaderId);
	glDeleteShader(fShaderId);

	return programId;
}
