# Core source files that are common across all platforms
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/core/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/platform.cpp
)

# Platform-specific source files
if(PLATFORM_METAL)
    list(APPEND SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics/metal/metal_renderer.cpp
    )
else()
    list(APPEND SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics/vulkan/vulkan_renderer.cpp
    )
endif()

# Header files that define the public API
set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/core/engine.hpp
    ${CMAKE_SOURCE_DIR}/include/platform/platform.hpp
)

# Platform-specific header files
if(PLATFORM_METAL)
    list(APPEND HEADERS
        ${CMAKE_SOURCE_DIR}/include/graphics/metal/metal_renderer.hpp
    )
else()
    list(APPEND HEADERS
        ${CMAKE_SOURCE_DIR}/include/graphics/vulkan/vulkan_renderer.hpp
    )
endif()

# Make variables visible to parent scope
set(SOURCES ${SOURCES} PARENT_SCOPE)
set(HEADERS ${HEADERS} PARENT_SCOPE) 