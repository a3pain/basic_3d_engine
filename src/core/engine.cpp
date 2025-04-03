#include "core/engine.hpp"
#include "platform/platform.hpp"

#include <stdexcept>

namespace Engine {

class Engine::Impl {
public:
    Impl() : platform(std::make_unique<Platform>()) {}

    std::unique_ptr<Platform> platform;
    bool isRunning      = false;
    bool isInitialized  = false;
};

// Engine Constructor implementation
Engine::Engine() : pImpl(std::make_unique<Impl>()) {}

// Engine Destructor implementaiton
Engine::~Engine() = default;

// Engine initialization
bool Engine::initialize(const std::string& windowTitle, uint32_t width, uint32_t height){
    return false;
}

void Engine::run(){

}

void Engine::shutdown(){

}


}