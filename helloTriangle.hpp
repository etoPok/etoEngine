#include <GL/gl.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vulkan/vulkan.hpp>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class TriangleApp {
private:
    GLFWwindow* window = nullptr;

public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanUp();
    }

    void glfwDisplayErrorMessage(const int code, const char* description) {
        std::cout << code << "\ndesc: " << description << "\n";
    }

private:
    void initWindow() {
        // if (glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) == GLFW_FALSE) {
        //     std::cout << "glfw platform not supported\n";
        // } else {
        //     glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_DISABLE_LIBDECOR);
        //     glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
        // }

        if (glfwInit() == GLFW_TRUE) {
            std::cout << "glfw initialized succesfully\n";
        } else {
            std::cout << "error initializing glfw\n";
            const char* description;
            int code = glfwGetError(&description);
            glfwDisplayErrorMessage(code, description);
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        int platform = glfwGetPlatform();
        std::cout << "Platform: " << platform << "\n";

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

        if (window == nullptr) {
            std::cout << "null window\n";
        } else {
            std::cout << "god window\n";
        }

        int w, h;
        glfwGetWindowSize(window, &w, &h);
        std::cout << "w: " << w << " h: " << h <<std::endl;
    }

    void initVulkan() {
    }

    void mainLoop() {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);
        }
    }

    void cleanUp() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }
};
