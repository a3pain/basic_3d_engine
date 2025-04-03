#pragma once

#include <memory>
#include <Metal/Metal.hpp>

namespace Engine {

/**
 * @description: class provides a Metal-specific implementation of the
 * graphics rendering system
 * 
 * uses the PIMPL pattern to hide implementation details and
 * provide a clean interface for the rest of the engine
 */
class MetalRenderer {
public:
    MetalRenderer();
    ~MetalRenderer();

    bool initialize();
    void cleanup();

    void beginFrame();
    void endFrame();

    void createCommandBuffer();
    void submitCommandBuffer();

    void present();

private:
    /**
     * @description: forward declaration of the implementation class
     * contains Metal-specific implementation details and resource management
     */
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 