#include <doctest.h>
#include "Core/GameLoop.h"

//This DummyInputService has been added to help Test GameLoop
namespace GameLoopTests{
    class DummyInputService : public InputService{
    public:

        //InputService
        void handleInputs() override {
            callCount++;
            if(callCount >= 100){
                gameLoop->stop();
            }
        }

        //Fields
        int callCount {0};
        GameLoop* gameLoop {nullptr};
    private:
    };

    class DummyRenderService : public RenderService{
    public:
        //Fields
        std::chrono::duration<GameTic, std::milli> targetTime {1000};
        std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> totalTime {};
        int renderCalls {0};
        GameLoop* gameLoop {nullptr};

        //Methods
        void render() override {
            auto current = std::chrono::steady_clock::now();
            auto elapsed = current - previous;
            previous = current;
            totalTime += elapsed;
            renderCalls++;

            if(totalTime >= targetTime){
                gameLoop->stop();
            }
        }

        //Unused
        void addDrawable(const Drawable& drawable) override {}
        void removeDrawable(const Drawable& drawable) override {}
        void setScreenSize(int width, int height) override {}
    };

    class DummyPhysicsService : public PhysicsService{
    public:
        //Fields
        std::chrono::duration<GameTic, std::milli> targetTime {1000.f};
        std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> totalTime {0.f};
        int physicsCalls {0};
        GameLoop* gameLoop {nullptr};

        //Methods
        void update() override {
            auto current = std::chrono::steady_clock::now();
            auto elapsed = current - previous;
            previous = current;
            totalTime += elapsed;
            physicsCalls++;

            if(totalTime >= targetTime){
                gameLoop->stop();
            }

        }

        //Unused
        void addRigidBody(const RigidBody& rigidBody) override {}
        void removeRigidBody(const RigidBody& rigidBody) override {}
    };
}

TEST_CASE("GameLoop.start() calls dummy InputService"){
    //Arrange
    auto* dummyService = new GameLoopTests::DummyInputService {};
    GameLoop gameLoop {};
    dummyService->gameLoop = &gameLoop;
    gameLoop.setInputService(dummyService);

    //Act
    gameLoop.start();

    //Assert
    CHECK_GT(dummyService->callCount, 0);
}

TEST_CASE("GameLoop.start() calls dummy RenderService as much as possible"){
    //Arrange
    auto* dummyService = new GameLoopTests::DummyRenderService {};
    GameLoop gameLoop {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setRenderService(dummyService);

    //Act
    gameLoop.start();

    //Assert
    CHECK_GE(gameLoop.time->getRenderFps(), 60); // Atleast 60FPS
    CHECK_GE(dummyService->renderCalls, 60); //Atleast 60FPS
}

TEST_CASE("GameLoop.start() calls dummy PhysicsService at a consistent framerate"){
    //Arrange
    GameLoop gameLoop {};
    auto* dummyService = new GameLoopTests::DummyPhysicsService {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setPhysicsService(dummyService);

    //Act
    gameLoop.start();

    //Assert
    // Physics calls should be around 60 fps.
    // Since this is based on system performance we allow a small margin of error
    CHECK_GE(gameLoop.time->getPhysicsFps(), 59);
    CHECK_LE(gameLoop.time->getPhysicsFps(), 61);
    CHECK_GT(dummyService->physicsCalls, 0);
}

TEST_CASE("Time.getPhysicsDeltaTime() give a consistent delta time"){
    //Arrange
    GameLoop gameLoop {};
    auto* dummyService = new GameLoopTests::DummyPhysicsService {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setPhysicsService(dummyService);

    //Act
    gameLoop.start();

    //Assert
    // Physics DeltaTime should be 0.016666667.
    // Since this is based on system performance we allow a small margin of error
    CHECK_GE(gameLoop.time->getPhysicsDeltaTime(), 0.015f);
    CHECK_LE(gameLoop.time->getPhysicsDeltaTime(), 0.017f);
}

TEST_CASE("Time.getRenderDeltaTime() is as fast as possible"){
    //Arrange
    GameLoop gameLoop {};
    auto* dummyService = new GameLoopTests::DummyPhysicsService {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setPhysicsService(dummyService);

    //Act
    gameLoop.start();

    //Assert
    // Render DeltaTime should be 0.016666667 or less.
    CHECK_LE(gameLoop.time->getRenderDeltaTime(), 0.016667f);
    CHECK_GT(gameLoop.time->getRenderDeltaTime(), 0.f);
}
