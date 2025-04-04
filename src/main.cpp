#include "core/engine.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Engine::Engine engine;
        
        // Initialize engine with a window
        if (!engine.initialize("Engine Demo", 1280, 720)) {
            std::cerr << "Failed to initialize engine" << std::endl;
            return 1;
        }

        // Run the engine (this will block until the window is closed)
        engine.run();

        // Clean up
        engine.shutdown();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
} 