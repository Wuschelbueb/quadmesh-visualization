#define STB_IMAGE_IMPLEMENTATION

#include "glitter.hpp"
// Standard Headers
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // Check for Valid Context
    if (mWindow == nullptr)
    {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSetMouseButtonCallback(mWindow, mouse_button);
    glfwSetScrollCallback(mWindow, scroll_callback);
    gladLoadGL();

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // this path has to be like this because the shader class searches from the build/glitter folder for files
    Shader ourShader("../../Glitter/Shaders/shader.vs", "../../Glitter/Shaders/shader.fs");

    // load models
    Model ourModel("../../Glitter/Resources/square/object.obj");
    glm::vec3 origin = ourModel.GetObjCenter();
    glm::vec3 cameraStartPosition = origin + glm::vec3(0.0f, 0.0f, 4.0f);
    camera.Position = (cameraStartPosition);

    // shader configuration
    ourShader.use();

    // how many elements of quad textures are repeated
    ourShader.setFloat("scale_u", 1.f);
    ourShader.setFloat("scale_v", 1.f);
    ourShader.setVec3("objectColor", 0.5f, 0.5f, 0.5f);

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false)
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(mWindow);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // be sure to activate shader when setting uniforms/drawing objects
        ourShader.use();
        ourShader.setVec3("viewPos", camera.Position);
        // light properties
        ourShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
        ourShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        // material properties
        ourShader.setFloat("material.shininess", 32.0f);
        // rotation and translation of object
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 translation1 = glm::translate(glm::mat4(1.0f), -origin);
        glm::mat4 pitchRot = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 yawRot = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotation = pitchRot * yawRot;
        glm::mat4 translation2 = glm::translate(glm::mat4(1.0f), origin);
        // dont change order, this matters
        model = translation2 * rotation * translation1 * model;

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)mWidth / (float)mHeight, 0.1f, 100.0f);
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        //
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime*2);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime*2);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_callback(GLFWwindow *window, double mouseX, double mouseY)
{
    // Calculate the change in mouse position since the last frame
    float deltaX = mouseX - lastMouseX;
    float deltaY = lastMouseY - mouseY;
    const float sensitivity = 0.1f;

    // Update the mouse position for the next frame
    lastMouseX = mouseX;
    lastMouseY = mouseY;

    deltaX *= sensitivity;
    deltaY *= sensitivity;

    // Check if the left mouse button is pressed
    if (leftButtonPressed)
    {
        // Update the pitch and yaw angles
        yaw += deltaX;
        pitch += deltaY;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
}

void mouse_button(GLFWwindow *window, int button, int action, int mods)
{
    // Check if the left mouse button was pressed
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        // Update the left button pressed flag
        if (action == GLFW_PRESS)
        {
            leftButtonPressed = true;
        }
        else if (action == GLFW_RELEASE)
            leftButtonPressed = false;
    }
}