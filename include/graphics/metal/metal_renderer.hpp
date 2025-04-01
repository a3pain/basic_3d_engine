#pragma once

#include <memory>
#include <Metal/Metal.hpp>

namespace Engine {

class MetalRenderer {
public:
    MetalRenderer();
    ~MetalRenderer();

    // Initialization
    bool initialize();
    void cleanup();

    // Rendering
    void beginFrame();
    void endFrame();
    void present();

    // Command buffer management
    void createCommandBuffer();
    void submitCommandBuffer();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 