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
else()
    set(PLATFORM_METAL OFF)
    set(PLATFORM_VULKAN ON)
endif()

# Core source files that are common across all platforms
set(SOURCES
    src/core/engine.cpp      # Main engine implementation
    src/platform/platform.cpp # Platform abstraction layer
)

# Platform-specific source files
# Metal renderer for macOS
if(PLATFORM_METAL)
    list(APPEND SOURCES
        src/graphics/metal/metal_renderer.cpp
    )
# Vulkan renderer for other platforms
else()
    list(APPEND SOURCES
        src/graphics/vulkan/vulkan_renderer.cpp
    )
endif()

# Header files that define the public API
set(HEADERS
    include/core/engine.hpp      # Main engine interface
    include/platform/platform.hpp # Platform abstraction interface
)

# Platform-specific header files
if(PLATFORM_METAL)
    list(APPEND HEADERS
        include/graphics/metal/metal_renderer.hpp
    )
else()
    list(APPEND HEADERS
        include/graphics/vulkan/vulkan_renderer.hpp
    )
endif()

# Create the main executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set include directories for the project
# This allows including headers using the project name as a prefix
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Platform-specific library configuration
if(PLATFORM_METAL)
    # Find required macOS frameworks
    find_library(METAL_LIBRARY Metal)        # Metal graphics framework
    find_library(FOUNDATION_LIBRARY Foundation) # Core Foundation framework
    find_library(QUARTZCORE_LIBRARY QuartzCore) # Core Animation framework
    
    # Link against required frameworks
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
            ${METAL_LIBRARY}
            ${FOUNDATION_LIBRARY}
            ${QUARTZCORE_LIBRARY}
    )
else()
    # Find and link Vulkan SDK
    find_package(Vulkan REQUIRED)
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
            Vulkan::Vulkan
    )
endif()

# Enable testing and add test subdirectory
enable_testing()
add_subdirectory(tests) 