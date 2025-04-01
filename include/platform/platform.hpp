#pragma once

#include <string>
#include <memory>

namespace Engine {

class Platform {
public:
    Platform();
    ~Platform();

    // Window management
    bool createWindow(const std::string& title, uint32_t width, uint32_t height);
    void destroyWindow();
    bool shouldClose() const;

    // Event handling
    void pollEvents();

    // Platform-specific renderer access
    class Renderer* getRenderer();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 