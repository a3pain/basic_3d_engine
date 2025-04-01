#pragma once

#include <memory>
#include <vulkan/vulkan.hpp>

namespace Engine {

/**
 * @brief Vulkan-specific renderer implementation for non-macOS platforms
 * 
 * The VulkanRenderer class provides a Vulkan-specific implementation of the
 * graphics rendering system. It handles:
 * - Vulkan instance and device management
 * - Command pool and buffer management
 * - Swap chain creation and management
 * - Render pass and pipeline setup
 * - Resource management for Vulkan-specific objects
 * 
 * This class uses the PIMPL pattern to hide implementation details and
 * provide a clean interface for the rest of the engine.
 */
class VulkanRenderer {
public:
    /**
     * @brief Construct a new VulkanRenderer instance
     * 
     * Initializes internal state but does not set up Vulkan resources.
     * Call initialize() to set up the Vulkan instance and device.
     */
    VulkanRenderer();

    /**
     * @brief Destroy the VulkanRenderer instance
     * 
     * Ensures proper cleanup of all Vulkan resources, including:
     * - Command pools and buffers
     * - Swap chain
     * - Device and instance
     */
    ~VulkanRenderer();

    /**
     * @brief Initialize Vulkan-specific resources
     * 
     * @return true if initialization was successful
     * @return false if initialization failed
     * 
     * This method:
     * 1. Creates the Vulkan instance
     * 2. Selects and creates the physical device
     * 3. Creates logical device and command pools
     * 4. Sets up the swap chain
     * 5. Creates render pass and pipeline
     * 6. Initializes command buffers
     */
    bool initialize();

    /**
     * @brief Cleanup Vulkan resources
     * 
     * Performs cleanup of all Vulkan-specific resources:
     * 1. Waits for device idle
     * 2. Destroys command pools and buffers
     * 3. Destroys swap chain
     * 4. Destroys logical device
     * 5. Destroys instance
     */
    void cleanup();

    /**
     * @brief Begin a new render frame
     * 
     * Prepares for rendering a new frame by:
     * 1. Acquiring next swap chain image
     * 2. Creating command buffer
     * 3. Beginning render pass
     * 4. Setting up viewport and scissor
     */
    void beginFrame();

    /**
     * @brief End the current render frame
     * 
     * Finalizes the current frame by:
     * 1. Ending render pass
     * 2. Submitting command buffer
     * 3. Presenting the frame
     */
    void endFrame();

    /**
     * @brief Present the rendered frame
     * 
     * Displays the rendered frame by:
     * 1. Submitting command buffer to graphics queue
     * 2. Presenting the frame to the swap chain
     * 3. Handling swap chain recreation if needed
     */
    void present();

    /**
     * @brief Create a new command buffer
     * 
     * Creates and configures a new Vulkan command buffer for rendering.
     * This is typically called at the start of a frame or when
     * additional command buffers are needed.
     */
    void createCommandBuffer();

    /**
     * @brief Submit the current command buffer
     * 
     * Submits the current command buffer to the graphics queue for execution.
     * This is typically called at the end of a frame or when
     * immediate execution is required.
     */
    void submitCommandBuffer();

    /**
     * @brief Handle window resize events
     * 
     * Recreates the swap chain and related resources when the window
     * size changes. This ensures proper rendering at the new resolution.
     */
    void handleResize();

private:
    /**
     * @brief Forward declaration of the implementation class
     * 
     * Contains Vulkan-specific implementation details and resource management.
     */
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 