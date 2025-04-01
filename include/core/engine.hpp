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
    /**
     * @brief Construct a new Engine instance
     * 
     * Initializes internal state but does not start the engine.
     * Call initialize() to fully start the engine.
     */
    Engine();

    /**
     * @brief Destroy the Engine instance
     * 
     * Ensures proper cleanup of all subsystems and resources.
     */
    ~Engine();

    /**
     * @brief Initialize the engine and its subsystems
     * 
     * @param windowTitle The title of the application window
     * @param width Initial window width in pixels
     * @param height Initial window height in pixels
     * @return true if initialization was successful
     * @return false if initialization failed
     * 
     * This method:
     * 1. Creates the application window
     * 2. Initializes the graphics subsystem (Metal/Vulkan)
     * 3. Sets up input handling
     * 4. Prepares resource management systems
     */
    bool initialize(const std::string& windowTitle = "Engine", 
                   uint32_t width = 1280, 
                   uint32_t height = 720);

    /**
     * @brief Main engine loop
     * 
     * Runs the main engine loop which:
     * 1. Processes input events
     * 2. Updates game/application state
     * 3. Renders the current frame
     * 4. Presents the rendered frame
     * 
     * This method blocks until the engine is shut down.
     */
    void run();

    /**
     * @brief Shutdown the engine and cleanup resources
     * 
     * Performs an orderly shutdown of all subsystems:
     * 1. Stops the main loop
     * 2. Releases graphics resources
     * 3. Closes the application window
     * 4. Cleans up all allocated resources
     */
    void shutdown();

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