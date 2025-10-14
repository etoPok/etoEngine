#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "helloTriangleConfig.h"
#include "helloTriangle.hpp"

int main() {
    std::cout << "Version " << HelloTriangle_VERSION_MAJOR << "."
                            << HelloTriangle_VERSION_MINOR << std::endl;

    try {
        TriangleApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
