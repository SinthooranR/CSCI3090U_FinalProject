#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.hpp"
#include "objectModel.cpp"

using namespace glm;

int height = 480;
int width = 640;

glm::mat4 viewMatrix;
glm::vec3 eyePosition(-50, 30, 50);
glm::mat4 projectionMatrix;

// Model related stuff
GLint vertex_attribute;

GLuint positions_vbo = 0;
GLuint textureCoords_vbo = 0;
GLuint normals_vbo = 0;

GLfloat vertices[] = {-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,
                      -1.0f, 1.0f,  1.0f, 1.0f, 1.0f,  1.0f,
                      -1.0f, 1.0f,  1.0f, 1.0f, -1.0f, 1.0f};

static void createObject(std::string objectFile) {


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    objectModel objload(objectFile);

    

    // VERTEX BUFFER OBJECTS (vbo)
    glGenBuffers(1, &positions_vbo);  // Create a buffer
    // Send the buffer to the GPU and make it active
    glBindBuffer(GL_ARRAY_BUFFER, positions_vbo);
    // Upload the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, objload.vertices.size() * sizeof(vec3), &objload.vertices[0], GL_STATIC_DRAW);


        // VERTEX BUFFER OBJECTS (vbo)
    glGenBuffers(1, &textureCoords_vbo);  // Create a buffer
    // Send the buffer to the GPU and make it active
    glBindBuffer(GL_ARRAY_BUFFER, textureCoords_vbo);
    // Upload the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, objload.uvs.size() * sizeof(vec3), &objload.uvs[0] , GL_STATIC_DRAW);

        // VERTEX BUFFER OBJECTS (vbo)
    glGenBuffers(1, &normals_vbo);  // Create a buffer
    // Send the buffer to the GPU and make it active
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    // Upload the data to the buffer
    glBufferData(GL_ARRAY_BUFFER, objload.normals.size() * sizeof(vec3), &objload.normals[0], GL_STATIC_DRAW);


}

static void drawObject(GLuint programID, GLuint objectVbo, glm::mat4 mvp,
                       glm::vec4 colour) {
    glUseProgram(programID);

    GLuint gpuMvp = glGetUniformLocation(programID, "u_MVP_Array");
    glUniformMatrix4fv(gpuMvp, 1, GL_FALSE, &mvp[0][0]);

    GLuint gpuColour = glGetUniformLocation(programID, "u_Colour");
    glUniform4fv(gpuColour, 1, (GLfloat *)&colour[0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, objectVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vertices[0]));
    glDisableVertexAttribArray(0);
}

static void drawSqaures(GLuint programID){

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    //     glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1, 0, 0));
    // modelMatrix =
    //     glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(0, 1, 0));
    // modelMatrix =
    //     glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(0, 0, 1));
    // modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0, 1.0, 1.0));

    // Render the objects


    glm::vec4 red(0.3, 0.0, 1.0, 1.0);

    //drawObject(programID, vbo, projectionMatrix * viewMatrix * modelMatrix, red);



  //glm::mat4 modelMatrix = glm::mat4(1.0f);
 
  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 2.5f, 0.0f));

  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,0,1));

  modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
  //modelMatrix = glm::translate(modelMatrix, glm::vec3(0.1, 1.0, 1.0));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 2.5f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, -2.5f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);
  

  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, 0.0f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);

  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.25f, 0.0f, 0.0f));

  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(90.0f),glm::vec3(0,0,1));

  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.25f, 0.0f, 0.0f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);

  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, 0.0f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);

  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5f, 0.0f, 0.0f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 2.5f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);



  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 2.5f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);

  
  // TODO:  Draw the fingers (and thumb)
  //glm::vec3 base(0.0,0.0,0.0);
  


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 2.25f));

  modelMatrix = glm::rotate(modelMatrix,glm::radians(90.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
  modelMatrix = glm::rotate(modelMatrix,glm::radians(0.0f),glm::vec3(0,0,1));
  
  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 2.25f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 2.5f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 2.5f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);
  

  modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5f, 0.0f, 0.0f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5f, 0.0f, 0.0f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);


  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -2.5f));

  drawObject(programID, positions_vbo, projectionMatrix * viewMatrix * modelMatrix, red);
 
}

static void render(GLFWwindow *window, GLuint programID) {
    // Turn on depth buffering (dont render objects overtop of eachother)
    glEnable(GL_DEPTH_TEST);

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate the model matrix (transformations for the model)
    
    drawSqaures(programID);



}

static GLFWwindow *init_opengl() {
    // The variable to hold the window in
    GLFWwindow *window;

    // Init GLFW
    if (!glfwInit()) exit(EXIT_FAILURE);

    #ifdef __APPLE__
        // We need to explicitly ask for a 3.2 context on MacOS
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif

    // Create the window
    window = glfwCreateWindow(width, height, "IDK PAM STUFF", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    // Make the window active
    glfwMakeContextCurrent(window);
    glewInit();

    return window;
}

int main(void) {
    // Init the scene
    GLFWwindow *window = init_opengl();

    // Create/Load the objects
    createObject("plane.obj");

    // Load the shaders
    GLuint programID = createShaderProgram("vertex.glsl", "fragment.glsl");

    // Calculate the projection
    projectionMatrix = glm::perspective(glm::radians(45.0f),
                                        (float)width / height, 0.1f, 1000.0f);

    // Calculate the view matrix (where we're looking at)
    viewMatrix =
        glm::lookAt(eyePosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    while (!glfwWindowShouldClose(window)) {
        // Render the scene
        render(window, programID);

        // Display the image
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
