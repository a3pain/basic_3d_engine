#pragma once

#include <memory>
#include <string>

namespace Engine {

/**
 * @brief Main engine class that coordinates all subsystems
 * 
 * The Engine class serves as the central coordinator for all engine subsystems,
 * including graphics, input handling, and resource management. It implements
 * the PIMPL (Pointer to Implementation) pattern to hide platform-specific details
 * and provide a clean public interface.
 */
class Engine {
public:
    // calls initialize() to start engine
    Engine();

    ~Engine();

    // creates window, initializes graphics subsystems (Metal/Vulkan), sets up input handling. prepares resource management systems
    bool initialize(const std::string& windowTitle = "Engine", uint32_t width = 1280, uint32_t height = 720);

    // main engine loop, run until engine is shut down
    void run();

    // shuts down engine, cleans up resources
    void shutdown();

    // returns whether the engine is currently running
    bool isRunning() const;

private:
    /**
     * @brief Forward declaration of the implementation class
     * 
     * The actual implementation details are hidden in the .cpp file
     * to maintain ABI stability and hide platform-specific code.
     */
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 