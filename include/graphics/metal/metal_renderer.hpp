#pragma once

#include "graphics/renderer.hpp"
#include <memory>

namespace Engine {

class Window;

/**
 * @description: class provides a Metal-specific implementation of the
 * graphics rendering system
 * 
 * uses the PIMPL pattern to hide implementation details and
 * provide a clean interface for the rest of the engine
 */
class MetalRenderer : public Renderer {
public:
    MetalRenderer();
    ~MetalRenderer() override;

    void initialize() override;
    void render() override;
    void cleanup() override;

    void beginFrame();
    void endFrame();

    void createCommandBuffer();
    void submitCommandBuffer();

    void present();

    // Set the window to render to
    void setWindow(Window* window);

private:
    /**
     * @description: forward declaration of the implementation class
     * contains Metal-specific implementation details and resource management
     */
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 