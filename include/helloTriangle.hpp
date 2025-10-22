#include <stdexcept>
#include <string>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class TriangleApp {
private:
    GLFWwindow* window = nullptr;
    VkInstance instance = VK_NULL_HANDLE;

public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanUp();
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
    }

    void initVulkan() {
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanUp() {
        if (instance != VK_NULL_HANDLE)
            vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    // Helper functions

    void glfwDisplayErrorMessage(const int code, const char* description) {
        std::cout << code << "\ndesc: " << description << "\n";
    }

    void createInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        uint32_t vkExtensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, nullptr);
        std::vector<VkExtensionProperties> vkExtensionProperties(vkExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &vkExtensionCount, vkExtensionProperties.data());

        for (uint32_t i=0; i < glfwExtensionCount; ++i) {
            bool found = false;
            for (uint32_t e=0; e < vkExtensionProperties.size(); ++e) {
                if (!strcmp(glfwExtensions[i], vkExtensionProperties[e].extensionName)) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                throw std::runtime_error(std::string("Required GLFW extension is not supported by Vulkan: ") + glfwExtensions[i]);
            }

            std::cout << "Supported extension: " << glfwExtensions[i] << std::endl;
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create vulkan instance\nVkResult: " + std::to_string(result));
        }
    }
};
