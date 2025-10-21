#include <iostream>
#include <stdexcept>

#include "vulkan/vulkan_core.h"
#include <vulkan/vulkan.hpp>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_raii.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class TriangleApp {
private:
    GLFWwindow* window = nullptr;
    vk::raii::Context context;
    vk::raii::Instance instance = nullptr;

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

        // int w, h;
        // glfwGetWindowSize(window, &w, &h);
        // std::cout << "w: " << w << " h: " << h <<std::endl;
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
        glfwDestroyWindow(window);

        glfwTerminate();
    }

    // Helper functions

    void glfwDisplayErrorMessage(const int code, const char* description) {
        std::cout << code << "\ndesc: " << description << "\n";
    }

    void createInstance() {
        constexpr vk::ApplicationInfo appInfo = vk::ApplicationInfo(
            "Hello Triangle",
            VK_MAKE_VERSION(1, 0, 0),
            "No Engine",
            VK_MAKE_VERSION(1, 0, 0),
            vk::ApiVersion14
        );

        // Get the required instance extensions from GLFW
        uint32_t glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // Check if the required GLFW extensions are supported by the vulkan implementation
        auto extensionProperties = context.enumerateInstanceExtensionProperties();

        for (uint32_t i = 0; i < glfwExtensionCount; ++i) {
            if (std::ranges::none_of(extensionProperties,
                                     [glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
                                     { return strcmp(extensionProperty.extensionName, glfwExtension); }))
            {
                throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
            }

            std::cout << "Supported extension: " << extensionProperties[i].extensionName << '\n';
        }

        vk::InstanceCreateInfo createInfo;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        try {
            instance = vk::raii::Instance(context, createInfo);
        } catch (vk::SystemError const& err) {
            throw std::runtime_error(std::string("Failed to create vulkan instance: ") + err.what());
        } catch (const std::exception e) {
            throw;
        }
    }
};
