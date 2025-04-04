#pragma once

namespace Engine {
    class Renderer {
    public:
        virtual ~Renderer() = default;

        virtual void initialize() = 0;
        virtual void render() = 0;
        virtual void cleanup() = 0;
    };
} 