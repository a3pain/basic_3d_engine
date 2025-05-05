#include "graphics/metal/metal_renderer.hpp"
#include "platform/window.hpp"
#include <Metal/Metal.h>
#include <Foundation/Foundation.h>
#include <QuartzCore/QuartzCore.h>
#include <Cocoa/Cocoa.h>

namespace Engine {

// Forward declare the Objective-C++ implementation class
class MetalRenderer::Impl {
private:
    id<MTLDevice> device;
    id<MTLCommandQueue> commandQueue;
    CAMetalLayer* layer;
    Window* window;

public:
    Impl() : device(nullptr), commandQueue(nullptr), layer(nullptr), window(nullptr) {}
    ~Impl() { cleanup(); }

    void initialize() {
        // Create Metal device
        device = MTLCreateSystemDefaultDevice();
        if(!device) {
            throw std::runtime_error("Failed to create Metal Device");
        }

        // Create command queue
        commandQueue = [device newCommandQueue];
        if(!commandQueue) {
            throw std::runtime_error("Failed to create command queue");
        }
    }

    void setWindow(Window* newWindow) {
        window = newWindow;
        if (!window) {
            return;
        }

        // Get the native window handle
        NSWindow* nsWindow = static_cast<NSWindow*>(window->getNativeHandle());
        if (!nsWindow) {
            return;
        }

        // Create Metal layer
        layer = [CAMetalLayer layer];
        layer.device = device;
        layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        layer.framebufferOnly = YES;
        
        // Add layer to window
        NSView* view = [[NSView alloc] initWithFrame:[nsWindow frame]];
        view.wantsLayer = YES;
        view.layer = layer;
        nsWindow.contentView = view;
    }

    void render() {
        if (!layer || !device || !commandQueue) return;

        // Create drawable
        id<CAMetalDrawable> drawable = [layer nextDrawable];
        if (!drawable) return;

        // Create command buffer
        id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
        
        // Create render pass descriptor
        MTLRenderPassDescriptor* renderPassDesc = [MTLRenderPassDescriptor renderPassDescriptor];
        renderPassDesc.colorAttachments[0].texture = drawable.texture;
        renderPassDesc.colorAttachments[0].loadAction = MTLLoadActionClear;
        renderPassDesc.colorAttachments[0].storeAction = MTLStoreActionStore;
        renderPassDesc.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);

        // Create command encoder
        id<MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDesc];
        [encoder endEncoding];

        // Present and commit
        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
    }

    void cleanup() {
        if (layer) {
            layer = nullptr;
        }
        if (commandQueue) {
            [commandQueue release];
            commandQueue = nullptr;
        }
        if (device) {
            [device release];
            device = nullptr;
        }
    }
};

// C++ interface implementation
MetalRenderer::MetalRenderer() : pImpl(std::make_unique<Impl>()) {}
MetalRenderer::~MetalRenderer() = default;

void MetalRenderer::initialize() {
    pImpl->initialize();
}

void MetalRenderer::render() {
    pImpl->render();
}

void MetalRenderer::cleanup() {
    pImpl->cleanup();
}

void MetalRenderer::setWindow(Window* window) {
    pImpl->setWindow(window);
}

} // namespace Engine 