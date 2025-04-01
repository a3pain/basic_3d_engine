#pragma once

#include <string>
#include <memory>

namespace Engine {

/**
 * @brief Platform abstraction layer for window management and system events
 * 
 * The Platform class handles platform-specific functionality such as:
 * - Window creation and management
 * - Event processing
 * - System-specific input handling
 * - Platform-specific renderer initialization
 * 
 * This class uses the PIMPL pattern to hide platform-specific implementation details
 * while providing a clean, platform-independent interface.
 */
class Platform {
public:
    /**
     * @brief Construct a new Platform instance
     * 
     * Initializes platform-specific subsystems but does not create a window.
     * Call createWindow() to create the application window.
     */
    Platform();

    /**
     * @brief Destroy the Platform instance
     * 
     * Ensures proper cleanup of platform-specific resources and subsystems.
     */
    ~Platform();

    /**
     * @brief Create the application window
     * 
     * @param title Window title
     * @param width Window width in pixels
     * @param height Window height in pixels
     * @return true if window creation was successful
     * @return false if window creation failed
     * 
     * This method:
     * 1. Creates the native window
     * 2. Sets up the window event handling
     * 3. Initializes platform-specific input systems
     */
    bool createWindow(const std::string& title, uint32_t width, uint32_t height);

    /**
     * @brief Destroy the application window
     * 
     * Performs cleanup of window-related resources and subsystems.
     */
    void destroyWindow();

    /**
     * @brief Check if the window should close
     * 
     * @return true if the window close button was pressed or system shutdown requested
     * @return false if the window should continue running
     */
    bool shouldClose() const;

    /**
     * @brief Process pending platform events
     * 
     * This method:
     * 1. Processes window events (resize, close, etc.)
     * 2. Updates input state
     * 3. Handles system messages
     * 
     * Should be called once per frame in the main loop.
     */
    void pollEvents();

    /**
     * @brief Get the platform-specific renderer
     * 
     * @return Renderer* Pointer to the platform-specific renderer implementation
     * 
     * Returns the appropriate renderer (Metal for macOS, Vulkan for others)
     * for the current platform.
     */
    class Renderer* getRenderer();

private:
    /**
     * @brief Forward declaration of the implementation class
     * 
     * Contains platform-specific implementation details hidden from the public API.
     */
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 