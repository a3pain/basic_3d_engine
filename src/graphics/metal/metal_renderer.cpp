#include "graphics/metal/metal_renderer.hpp"
#include <stdexcept>

namespace Engine {

class MetalRenderer::Impl {
public:
    Impl() : device(nullptr), commandQueue(nullptr), currentCommandBuffer(nullptr) {}

    MTL::Device*                device; 
    MTL::CommandQueue*          commandQueue;
    MTL::CommandBuffer*         currentCommandBuffer;
    MTL::RenderPassDescriptor*  renderPassDescriptor;
    
    bool isInitialized = false;
};

MetalRenderer::MetalRenderer() : pImpl(std::make_unique<Impl>()) {}
MetalRenderer::~MetalRenderer() = default;

bool MetalRenderer::initialize() {
    try{
        return true;
    } catch (const std::exception& e) {
        cleanup();
        return false;
    }
}

void MetalRenderer::cleanup() {

}

void MetalRenderer::createCommandBuffer() {

}

void MetalRenderer::submitCommandBuffer() {

}

void MetalRenderer::beginFrame() {

}

void MetalRenderer::endFrame() {

}

void MetalRenderer::present() {

}



}