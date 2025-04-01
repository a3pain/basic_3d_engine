cmake_minimum_required(VERSION 3.20)
project(Engine VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform detection
if(APPLE)
    set(PLATFORM_METAL ON)
    set(PLATFORM_VULKAN OFF)
else()
    set(PLATFORM_METAL OFF)
    set(PLATFORM_VULKAN ON)
endif()

# Add source files
set(SOURCES
    src/core/engine.cpp
    src/platform/platform.cpp
)

if(PLATFORM_METAL)
    list(APPEND SOURCES
        src/graphics/metal/metal_renderer.cpp
    )
else()
    list(APPEND SOURCES
        src/graphics/vulkan/vulkan_renderer.cpp
    )
endif()

# Add header files
set(HEADERS
    include/core/engine.hpp
    include/platform/platform.hpp
)

if(PLATFORM_METAL)
    list(APPEND HEADERS
        include/graphics/metal/metal_renderer.hpp
    )
else()
    list(APPEND HEADERS
        include/graphics/vulkan/vulkan_renderer.hpp
    )
endif()

# Create main executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Platform-specific settings
if(PLATFORM_METAL)
    # Metal-specific settings
    find_library(METAL_LIBRARY Metal)
    find_library(FOUNDATION_LIBRARY Foundation)
    find_library(QUARTZCORE_LIBRARY QuartzCore)
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
            ${METAL_LIBRARY}
            ${FOUNDATION_LIBRARY}
            ${QUARTZCORE_LIBRARY}
    )
else()
    # Vulkan-specific settings
    find_package(Vulkan REQUIRED)
    target_link_libraries(${PROJECT_NAME} 
        PRIVATE 
            Vulkan::Vulkan
    )
endif()

# Add tests
enable_testing()
add_subdirectory(tests) 