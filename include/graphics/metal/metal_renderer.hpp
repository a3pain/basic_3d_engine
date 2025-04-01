#pragma once

#include <memory>
#include <Metal/Metal.hpp>

namespace Engine {

/**
 * @brief Metal-specific renderer implementation for macOS
 * 
 * The MetalRenderer class provides a Metal-specific implementation of the
 * graphics rendering system. It handles:
 * - Metal device and command queue management
 * - Command buffer creation and submission
 * - Render pass setup and execution
 * - Resource management for Metal-specific objects
 * 
 * This class uses the PIMPL pattern to hide implementation details and
 * provide a clean interface for the rest of the engine.
 */
class MetalRenderer {
public:
    /**
     * @brief Construct a new MetalRenderer instance
     * 
     * Initializes internal state but does not set up Metal resources.
     * Call initialize() to set up the Metal device and command queue.
     */
    MetalRenderer();

    /**
     * @brief Destroy the MetalRenderer instance
     * 
     * Ensures proper cleanup of all Metal resources and command buffers.
     */
    ~MetalRenderer();

    /**
     * @brief Initialize Metal-specific resources
     * 
     * @return true if initialization was successful
     * @return false if initialization failed
     * 
     * This method:
     * 1. Creates the Metal device
     * 2. Sets up the command queue
     * 3. Initializes default command buffers
     * 4. Prepares render pass descriptors
     */
    bool initialize();

    /**
     * @brief Cleanup Metal resources
     * 
     * Performs cleanup of all Metal-specific resources:
     * 1. Releases command buffers
     * 2. Destroys command queue
     * 3. Releases device resources
     */
    void cleanup();

    /**
     * @brief Begin a new render frame
     * 
     * Prepares for rendering a new frame by:
     * 1. Creating a new command buffer
     * 2. Setting up render pass
     * 3. Configuring viewport and scissor rect
     */
    void beginFrame();

    /**
     * @brief End the current render frame
     * 
     * Finalizes the current frame by:
     * 1. Ending the render pass
     * 2. Preparing command buffer for submission
     */
    void endFrame();

    /**
     * @brief Present the rendered frame
     * 
     * Displays the rendered frame by:
     * 1. Submitting the command buffer
     * 2. Presenting the drawable
     * 3. Releasing resources
     */
    void present();

    /**
     * @brief Create a new command buffer
     * 
     * Creates and configures a new Metal command buffer for rendering.
     * This is typically called at the start of a frame or when
     * additional command buffers are needed.
     */
    void createCommandBuffer();

    /**
     * @brief Submit the current command buffer
     * 
     * Submits the current command buffer to the GPU for execution.
     * This is typically called at the end of a frame or when
     * immediate execution is required.
     */
    void submitCommandBuffer();

private:
    /**
     * @brief Forward declaration of the implementation class
     * 
     * Contains Metal-specific implementation details and resource management.
     */
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 