#include "core/engine.hpp"
#include "platform/platform.hpp"
#include "graphics/metal/metal_renderer.hpp"

#include <stdexcept>

namespace Engine {

class Engine::Impl {
public:
    Impl() : platform(&Platform::getInstance()) {}

    Platform* platform;
    std::unique_ptr<Window> window;
    std::unique_ptr<MetalRenderer> renderer;
    bool isRunning = false;
    bool isInitialized = false;
};

// Engine Constructor implementation
Engine::Engine() : pImpl(std::make_unique<Impl>()) {}

// Engine Destructor implementation
Engine::~Engine() = default;

// Engine initialization
bool Engine::initialize(const std::string& windowTitle, uint32_t width, uint32_t height) {
    if (pImpl->isInitialized) {
        return true;
    }

    try {
        // Create window
        pImpl->window = pImpl->platform->createWindow(width, height, windowTitle);
        if (!pImpl->window) {
            throw std::runtime_error("Failed to create window");
        }

        // Initialize renderer
        pImpl->renderer = std::make_unique<MetalRenderer>();
        pImpl->renderer->initialize();
        pImpl->renderer->setWindow(pImpl->window.get());

        pImpl->isInitialized = true;
        return true;
    } catch (const std::exception& e) {
        // Log error and cleanup
        shutdown();
        throw;
    }
}

void Engine::run() {
    if (!pImpl->isInitialized) {
        throw std::runtime_error("Engine not initialized");
    }

    pImpl->isRunning = true;
    pImpl->window->show();

    // Main loop
    while (pImpl->isRunning && !pImpl->platform->shouldClose()) {
        // Process platform events
        pImpl->platform->pollEvents();

        // Render frame
        pImpl->renderer->render();
    }
}

void Engine::shutdown() {
    if (pImpl->renderer) {
        pImpl->renderer->cleanup();
        pImpl->renderer.reset();
    }

    if (pImpl->window) {
        pImpl->window->close();
        pImpl->window.reset();
    }

    pImpl->isInitialized = false;
    pImpl->isRunning = false;
}

} // namespace Engine