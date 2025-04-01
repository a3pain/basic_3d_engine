#pragma once

#include <memory>
#include <string>

namespace Engine {

class Engine {
public:
    Engine();
    ~Engine();

    // Initialize the engine
    bool initialize(const std::string& windowTitle = "Engine", 
                   uint32_t width = 1280, 
                   uint32_t height = 720);

    // Main loop
    void run();

    // Cleanup
    void shutdown();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 