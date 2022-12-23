// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <stb_image.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// #include <learnopengl/filesystem.h>
// #include <learnopengl/shader_s.h>

// #include <iostream>

// void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// void processInput(GLFWwindow *window);

// void APIENTRY glDebugOutput(GLenum source,
//                             GLenum type,
//                             unsigned int id,
//                             GLenum severity,
//                             GLsizei length,
//                             const char *message,
//                             const void *userParam)
// {
//     if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
//         return; // ignore these non-significant error codes

//     std::cout << "---------------" << std::endl;
//     std::cout << "Debug message (" << id << "): " << message << std::endl;

//     switch (source)
//     {
//     case GL_DEBUG_SOURCE_API:
//         std::cout << "Source: API";
//         break;
//     case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
//         std::cout << "Source: Window System";
//         break;
//     case GL_DEBUG_SOURCE_SHADER_COMPILER:
//         std::cout << "Source: Shader Compiler";
//         break;
//     case GL_DEBUG_SOURCE_THIRD_PARTY:
//         std::cout << "Source: Third Party";
//         break;
//     case GL_DEBUG_SOURCE_APPLICATION:
//         std::cout << "Source: Application";
//         break;
//     case GL_DEBUG_SOURCE_OTHER:
//         std::cout << "Source: Other";
//         break;
//     }
//     std::cout << std::endl;

//     switch (type)
//     {
//     case GL_DEBUG_TYPE_ERROR:
//         std::cout << "Type: Error";
//         break;
//     case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
//         std::cout << "Type: Deprecated Behaviour";
//         break;
//     case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
//         std::cout << "Type: Undefined Behaviour";
//         break;
//     case GL_DEBUG_TYPE_PORTABILITY:
//         std::cout << "Type: Portability";
//         break;
//     case GL_DEBUG_TYPE_PERFORMANCE:
//         std::cout << "Type: Performance";
//         break;
//     case GL_DEBUG_TYPE_MARKER:
//         std::cout << "Type: Marker";
//         break;
//     case GL_DEBUG_TYPE_PUSH_GROUP:
//         std::cout << "Type: Push Group";
//         break;
//     case GL_DEBUG_TYPE_POP_GROUP:
//         std::cout << "Type: Pop Group";
//         break;
//     case GL_DEBUG_TYPE_OTHER:
//         std::cout << "Type: Other";
//         break;
//     }
//     std::cout << std::endl;

//     switch (severity)
//     {
//     case GL_DEBUG_SEVERITY_HIGH:
//         std::cout << "Severity: high";
//         break;
//     case GL_DEBUG_SEVERITY_MEDIUM:
//         std::cout << "Severity: medium";
//         break;
//     case GL_DEBUG_SEVERITY_LOW:
//         std::cout << "Severity: low";
//         break;
//     case GL_DEBUG_SEVERITY_NOTIFICATION:
//         std::cout << "Severity: notification";
//         break;
//     }
//     std::cout << std::endl;
//     std::cout << std::endl;
// }

// // settings
// const unsigned int SCR_WIDTH = 1800;
// const unsigned int SCR_HEIGHT = 1600;

// int main()
// {
//     // glfw: initialize and configure
//     // ------------------------------
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// #ifndef NDEBUG
//     glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // comment this line in a release build!
// #endif

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     // glfw window creation
//     // --------------------
//     GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // glad: load all OpenGL function pointers
//     // ---------------------------------------
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     // enable OpenGL debug context if context allows for debug context
//     int flags;
//     glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
//     if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
//     {
//         std::cout << "Debugging enabled\n";
//         glEnable(GL_DEBUG_OUTPUT);
//         glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
//         glDebugMessageCallback(glDebugOutput, nullptr);
//         glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//     }
//     else
//     {
//         std::cout << "Debugging nto enabled\n";
//     }

//     // build and compile our shader zprogram
//     // ------------------------------------

//     Shader ourShader(FileSystem::getPath("resources/shaders/4.2.texture_comb.vs").c_str(),
//                      FileSystem::getPath("resources/shaders/4.2.texture_comb.fs").c_str());

//     // set up vertex data (and buffer(s)) and configure vertex attributes
//     // ------------------------------------------------------------------
//     float vertices[] = {
//         // BL
//         -0.5f,
//         -0.5f,
//         0.f,
//         0.f,
//         0.f,
//         // BR
//         0.5f,
//         -0.5f,
//         0.f,
//         1.f,
//         0.f,
//         // TR
//         0.5f,
//         0.5f,
//         0.f,
//         1.f,
//         1.f,
//         // TL
//         -0.5f,
//         0.5f,
//         0.f,
//         0.f,
//         1.f,
//     };
//     unsigned int indices[] = {
//         0, 1, 2, // first triangle
//         0, 2, 3  // second triangle
//     };
//     unsigned int VBO, VAO, EBO;
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//     // position attribute
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
//     glEnableVertexAttribArray(0);
//     // texture coord attribute
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);

//     // load and create a texture
//     // -------------------------
//     unsigned int texture1, texture2;
//     // texture 1
//     // ---------
//     glGenTextures(1, &texture1);
//     glBindTexture(GL_TEXTURE_2D, texture1);
//     // set the texture wrapping parameters
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     // set texture filtering parameters
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     // load image, create texture and generate mipmaps
//     int width, height, nrChannels;
//     stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//     // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//     unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/block_solid.png").c_str(), &width, &height, &nrChannels, 0);
//     if (data)
//     {
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);
//     // texture 2
//     // ---------
//     glGenTextures(1, &texture2);
//     glBindTexture(GL_TEXTURE_2D, texture2);

//     // set the texture wrapping parameters
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     // set texture filtering parameters
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     // load image, create texture and generate mipmaps
//     data = stbi_load(FileSystem::getPath("resources/textures/quadTexture.png").c_str(), &width, &height, &nrChannels, 0);
//     if (data)
//     {
//         // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         glGenerateMipmap(GL_TEXTURE_2D);
//     }
//     else
//     {
//         std::cout << "Failed to load texture" << std::endl;
//     }
//     stbi_image_free(data);

//     // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//     // -------------------------------------------------------------------------------------------
//     // make sure to initialize matrix to identity matrix first

//     ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
//                      // either set it manually like so:
//                      // glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
//                      // or set it via the texture class
//     ourShader.setInt("texture1", 0);
//     ourShader.setInt("texture2", 1);
//     // how many elements of quad textures are repeated
//     ourShader.setFloat("scale_u", 10.f);
//     ourShader.setFloat("scale_v", 10.f);

//     // Center refers to the uv coordinates of vertices
//     ourShader.setFloat("center_u", 0.5f);
//     ourShader.setFloat("center_v", 0.5f);
//     // how many elements of quad texture have to be seen
//     ourShader.setInt("elements_u", 4.f);
//     ourShader.setInt("elements_v", 4.f);

//     ourShader.setFloat("u_angle", 0.78f);

//     // render loop
//     // -----------
//     while (!glfwWindowShouldClose(window))
//     {
//         // input
//         // -----
//         processInput(window);

//         // render
//         // ------
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // bind textures on corresponding texture units
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, texture1);
//         glActiveTexture(GL_TEXTURE1);
//         glBindTexture(GL_TEXTURE_2D, texture2);

//         // render container
//         ourShader.use();
//         glBindVertexArray(VAO);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//         // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//         // -------------------------------------------------------------------------------
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // optional: de-allocate all resources once they've outlived their purpose:
//     // ------------------------------------------------------------------------
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteBuffers(1, &VBO);
//     glDeleteBuffers(1, &EBO);

//     // glfw: terminate, clearing all previously allocated GLFW resources.
//     // ------------------------------------------------------------------
//     glfwTerminate();
//     return 0;
// }

// // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// // ---------------------------------------------------------------------------------------------------------
// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);

//     if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
//     {
//         std::cout << "Hello Reload function\n";
//     }
// }

// // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// // ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {
//     // make sure the viewport matches the new window dimensions; note that width and
//     // height will be significantly larger than specified on retina displays.
//     glViewport(0, 0, width, height);
// }