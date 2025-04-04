#include <gtest/gtest.h>
#include "core/engine.hpp"

TEST(EngineTest, Initialization) {
    Engine::Engine engine;
    EXPECT_TRUE(engine.initialize("Test Window", 800, 600));
}

TEST(EngineTest, DoubleInitialization) {
    Engine::Engine engine;
    EXPECT_TRUE(engine.initialize("Test Window", 800, 600));
    EXPECT_TRUE(engine.initialize("Test Window", 800, 600)); // Should return true as already initialized
}

TEST(EngineTest, RunWithoutInitialization) {
    Engine::Engine engine;
    EXPECT_THROW(engine.run(), std::runtime_error);
}

TEST(EngineTest, Shutdown) {
    Engine::Engine engine;
    EXPECT_TRUE(engine.initialize("Test Window", 800, 600));
    engine.shutdown();
    EXPECT_THROW(engine.run(), std::runtime_error); // Should fail as engine is shut down
} 