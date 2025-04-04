#include "platform/window.hpp"
#include <Cocoa/Cocoa.h>

namespace Engine {

class Window::Impl {
public:
    Impl(int width, int height, const std::string& title) 
        : window(nullptr), width(width), height(height), visible(false) {
        // Create window
        NSRect frame = NSMakeRect(0, 0, width, height);
        window = [[NSWindow alloc] initWithContentRect:frame
                                           styleMask:NSWindowStyleMaskTitled |
                                                    NSWindowStyleMaskClosable |
                                                    NSWindowStyleMaskMiniaturizable |
                                                    NSWindowStyleMaskResizable
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
        [window setTitle:[NSString stringWithUTF8String:title.c_str()]];
    }

    ~Impl() {
        if (window) {
            [window close];
            [window release];
        }
    }

    void resize(int newWidth, int newHeight) {
        if (window) {
            width = newWidth;
            height = newHeight;
            NSRect frame = [window frame];
            frame.size = NSMakeSize(width, height);
            [window setFrame:frame display:YES];
        }
    }

    void show() {
        if (window) {
            [window makeKeyAndOrderFront:nil];
            visible = true;
        }
    }

    void hide() {
        if (window) {
            [window orderOut:nil];
            visible = false;
        }
    }

    void close() {
        if (window) {
            [window close];
            visible = false;
        }
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool isVisible() const { return visible; }
    void* getNativeHandle() const { return window; }

private:
    NSWindow* window;
    int width;
    int height;
    bool visible;
};

// C++ interface implementation
Window::Window(int width, int height, const std::string& title)
    : pImpl(std::make_unique<Impl>(width, height, title)) {}

Window::~Window() = default;

void Window::resize(int width, int height) {
    pImpl->resize(width, height);
}

void Window::show() {
    pImpl->show();
}

void Window::hide() {
    pImpl->hide();
}

void Window::close() {
    pImpl->close();
}

int Window::getWidth() const {
    return pImpl->getWidth();
}

int Window::getHeight() const {
    return pImpl->getHeight();
}

bool Window::isVisible() const {
    return pImpl->isVisible();
}

void* Window::getNativeHandle() const {
    return pImpl->getNativeHandle();
}

} // namespace Engine 