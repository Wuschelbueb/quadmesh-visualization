// Preprocessor Directives
#ifndef GLITTER_HPP
#define GLITTER_HPP

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Object loader Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>

// Matrix Headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
#include <stb_image.h>

// Additional Headers
#include <shader.hpp>
#include <camera.hpp>
#include <model.hpp>

// Define Some Constants
const int mWidth = 1500;
const int mHeight = 1500;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

// mouse movement
bool leftButtonPressed = false;
int lastMouseX = 0;
int lastMouseY = 0;
float pitch = 0.f;
float yaw = 0.f;

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double mouseX, double mouseY);
void mouse_button(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
unsigned int loadTexture(const char *path);

#endif //~ Glitter Header
