#pragma once

#include "platform/window.hpp"
#include <string>
#include <memory>

namespace Engine {

/**
 * @description: OS-agnostic platform abstraction layer
 * Provides a clean interface for platform-independent functionality
 */
class Platform {
public:
    static Platform& getInstance();

    // Factory methods for platform-specific objects
    std::unique_ptr<Window> createWindow(int width, int height, const std::string& title);
    
    // System information
    std::string getOSName() const;
    std::string getOSVersion() const;
    bool isDebugMode() const;

    // System events
    void pollEvents();
    bool shouldClose() const;

    // Platform capabilities
    bool supportsMetal() const;
    bool supportsVulkan() const;
    bool supportsOpenGL() const;

private:
    Platform();
    ~Platform();
    Platform(const Platform&) = delete;
    Platform& operator=(const Platform&) = delete;

    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 