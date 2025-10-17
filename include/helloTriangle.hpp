// #define GLFW_INCLUDE_VULKAN
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
        if (glfwInit() != GLFW_TRUE) {
            std::cout << "error initializing glfw\n";
            const char* description;
            int code = glfwGetError(&description);
            glfwDisplayErrorMessage(code, description);
        }

        std::cout << "GLFW version " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << "\n";

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

        // int w, h;
        // glfwGetWindowSize(window, &w, &h);
        // std::cout << "w: " << w << " h: " << h <<std::endl;
    }

    void initVulkan() {
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanUp() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }
};
