#include "platform/platform.hpp"
#include <Cocoa/Cocoa.h>
#include <objc/runtime.h>

namespace Engine {

class Platform::Impl {
public:
    Impl() : shouldCloseFlag(false) {
        // Initialize Cocoa application
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        
        // Set up application delegate to handle window close
        id delegate = [[NSObject alloc] init];
        class_addMethod([delegate class], 
                       @selector(applicationShouldTerminate:),
                       (IMP)applicationShouldTerminate,
                       "l@:@");
        [NSApp setDelegate:delegate];
    }

    ~Impl() {
        // Cleanup Cocoa application
        [NSApp terminate:nil];
    }

    std::unique_ptr<Window> createWindow(int width, int height, const std::string& title) {
        auto window = std::make_unique<Window>(width, height, title);
        NSWindow* nsWindow = static_cast<NSWindow*>(window->getNativeHandle());
        
        // Don't release the window when closed
        [nsWindow setReleasedWhenClosed:NO];
        
        // Set up window close button to trigger application termination
        NSButton* closeButton = [nsWindow standardWindowButton:NSWindowCloseButton];
        [closeButton setTarget:NSApp];
        [closeButton setAction:@selector(terminate:)];
        
        // Make window key and order front
        [nsWindow makeKeyAndOrderFront:nil];
        
        return window;
    }

    std::string getOSName() const {
        return "macOS";
    }

    std::string getOSVersion() const {
        NSProcessInfo* processInfo = [NSProcessInfo processInfo];
        NSString* version = [processInfo operatingSystemVersionString];
        return std::string([version UTF8String]);
    }

    bool isDebugMode() const {
#ifdef DEBUG
        return true;
#else
        return false;
#endif
    }

    void pollEvents() {
        NSEvent* event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                         untilDate:nil
                                            inMode:NSDefaultRunLoopMode
                                           dequeue:YES])) {
            [NSApp sendEvent:event];
            [NSApp updateWindows];
        }
    }

    bool shouldClose() const {
        return shouldCloseFlag;
    }

    void setShouldClose(bool value) {
        shouldCloseFlag = value;
    }

    bool supportsMetal() const {
        return true; // macOS always supports Metal
    }

    bool supportsVulkan() const {
        return false; // macOS doesn't support Vulkan natively
    }

    bool supportsOpenGL() const {
        return true; // macOS supports OpenGL (though deprecated)
    }

private:
    bool shouldCloseFlag;

    static NSApplicationTerminateReply applicationShouldTerminate(id self, SEL _cmd, NSApplication* sender) {
        Platform::getInstance().pImpl->shouldCloseFlag = true;
        return NSTerminateCancel;
    }
};

// Platform singleton implementation
Platform& Platform::getInstance() {
    static Platform instance;
    return instance;
}

// Platform interface implementation
Platform::Platform() : pImpl(std::make_unique<Impl>()) {}
Platform::~Platform() = default;

std::unique_ptr<Window> Platform::createWindow(int width, int height, const std::string& title) {
    return pImpl->createWindow(width, height, title);
}

std::string Platform::getOSName() const {
    return pImpl->getOSName();
}

std::string Platform::getOSVersion() const {
    return pImpl->getOSVersion();
}

bool Platform::isDebugMode() const {
    return pImpl->isDebugMode();
}

void Platform::pollEvents() {
    pImpl->pollEvents();
}

bool Platform::shouldClose() const {
    return pImpl->shouldClose();
}

bool Platform::supportsMetal() const {
    return pImpl->supportsMetal();
}

bool Platform::supportsVulkan() const {
    return pImpl->supportsVulkan();
}

bool Platform::supportsOpenGL() const {
    return pImpl->supportsOpenGL();
}

void Platform::setShouldClose(bool value) {
    pImpl->setShouldClose(value);
}

} // namespace Engine 