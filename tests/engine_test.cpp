#include <gtest/gtest.h>
#include "core/engine.hpp"
#include "platform/platform.hpp"

TEST(EngineTest, Initialization) {
    Engine::Engine engine;
    EXPECT_TRUE(engine.initialize());
}

TEST(EngineTest, DoubleInitialization) {
    Engine::Engine engine;
    EXPECT_TRUE(engine.initialize());
    EXPECT_FALSE(engine.initialize()); // Should return false as already initialized
}

TEST(EngineTest, RunWithoutInitialization) {
    Engine::Engine engine;
    engine.run();
    EXPECT_FALSE(engine.isRunning());
}

TEST(EngineTest, Shutdown) {
    Engine::Engine engine;
    EXPECT_TRUE(engine.initialize());
    engine.shutdown();
    EXPECT_FALSE(engine.isRunning());
}

TEST(EngineTest, WindowClosing) {
    Engine::Engine engine;
    EXPECT_TRUE(engine.initialize());
    
    // Simulate window close event
    Engine::Platform::getInstance().setShouldClose(true);
    
    // Run one frame to process the close event
    engine.run();
    
    // Verify the engine has stopped
    EXPECT_FALSE(engine.isRunning());
} 