# Minimum required CMake version for modern C++ features
cmake_minimum_required(VERSION 3.20)

# Project name and version information
project(Engine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard to C++20 for modern features
# This enables features like concepts, ranges, and coroutines
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform detection for graphics API selection
# On macOS, we use Metal as the primary graphics API
# On other platforms, we use Vulkan
if(APPLE)
    set(PLATFORM_METAL ON)
    set(PLATFORM_VULKAN OFF)
    
    # Enable Objective-C++
    enable_language(OBJCXX)
    set(CMAKE_OBJCXX_STANDARD 20)
    set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)
    set(CMAKE_OBJCXX_EXTENSIONS OFF)
else()
    set(PLATFORM_METAL OFF)
    set(PLATFORM_VULKAN ON)
endif()

# Platform-specific library configuration
if(PLATFORM_METAL)
    # Find required macOS frameworks
    find_library(METAL_LIBRARY Metal)
    find_library(FOUNDATION_LIBRARY Foundation)
    find_library(QUARTZCORE_LIBRARY QuartzCore)
    find_library(COCOA_LIBRARY Cocoa)
    
    # Add Metal framework include path
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Metal.framework/Versions/A/Headers)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Foundation.framework/Headers)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/QuartzCore.framework/Headers)
    include_directories(/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Cocoa.framework/Headers)
    
    # Set platform-specific variables
    set(PLATFORM_LIBRARIES 
        ${METAL_LIBRARY}
        ${FOUNDATION_LIBRARY}
        ${QUARTZCORE_LIBRARY}
        ${COCOA_LIBRARY}
    )
else()
    # Find Vulkan SDK
    find_package(Vulkan REQUIRED)
    
    # Set platform-specific variables
    set(PLATFORM_LIBRARIES Vulkan::Vulkan)
endif()

# Set global include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add src directory to get source files
add_subdirectory(src)

# Create library target for engine code
add_library(engine_lib STATIC ${SOURCES} ${HEADERS})

# Link platform-specific libraries to the engine library
target_link_libraries(engine_lib PRIVATE ${PLATFORM_LIBRARIES})

# Create main executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE engine_lib)

# Enable testing and add test subdirectory
enable_testing()
add_subdirectory(tests) 