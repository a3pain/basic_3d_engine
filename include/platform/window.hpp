#pragma once

#include <string>
#include <memory>

namespace Engine {

/**
 * @description: Platform-agnostic window interface
 * Provides a clean interface for window management across different platforms
 */
class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    // Window management
    void resize(int width, int height);
    void show();
    void hide();
    void close();

    // Window state
    int getWidth() const;
    int getHeight() const;
    bool isVisible() const;

    // Platform-specific
    void* getNativeHandle() const;  // Returns platform-specific window handle

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace Engine 