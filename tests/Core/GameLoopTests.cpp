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

        [[nodiscard]] bool hasReceivedQuitSignal() const override{
            return _hasReceivedQuitSignal;
        }
        //Fields
        bool _hasReceivedQuitSignal {false};
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
        void setScreenSize(int width, int height) override {}
        void removeDrawable(Drawable& drawable) override {}
        void addDrawable(Drawable& drawable) override {}
        void setFullScreen(bool fullScreen) override {};
        std::optional<std::reference_wrapper<Camera>> getMainCamera() const override { return {};}
        void setMainCamera(Camera& camera) override {}
        bool isRegistered(Drawable& drawable) override {return false;}
        int getScreenSizeWidth() const override {return 0;}
        int getScreenSizeHeight() const override {return 0;}
        Vector2 getCameraOffset() const override {return Vector2();}
        void setWindowTitle(const std::string& title) override {}
        int screenSizeHeight() const override { return 0; }
        int screenSizeWidth() const override { return 0; }
    };

    class DummyPhysicsService : public PhysicsService{
    public:
        //Fields
        std::chrono::duration<GameTic, std::milli> targetTime {1000};
        std::chrono::steady_clock::time_point previous = std::chrono::steady_clock::now();
        std::chrono::duration<GameTic, std::milli> totalTime {0.f};
        int physicsCalls {0};
        GameLoop* gameLoop {nullptr};

        //Methods
        void update(GameTic timeStep) override {
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
        void addRigidBody(RigidBody* pRigidBody) override {}
        void removeRigidBody(RigidBody* pRigidBody) override {}
        void setGravity(const Vector2& vec2) override {}
        void applyWorldForceToCenter(RigidBody* pRigidBody, const Vector2& force) override {}
        void setTransform(RigidBody* pRigidBody, const Transform& transform) override {}
        void setEnabled(RigidBody* pRigidBody, bool enabled) override {}
        void setLinearDamping(RigidBody* pRigidBody, float linearDamping) override {}
        void setAngularDamping(RigidBody* pRigidBody, float angularDamping) override {}
        void setFixedRotation(RigidBody* pRigidBody, bool fixedRotation) override {}
        void setGravityScale(RigidBody* pRigidBody, float gravityScale) override {}
        Vector2 getLinearVelocity(RigidBody* pBody) override { return {};}
        void setLinearVelocity(RigidBody* pRigidBody, const Vector2& velocity) override {}
        float getAngularVelocity(RigidBody* pBody) override {return 0;}
        void setAngularVelocity(RigidBody* pRigidBody, float omega) override {}
        void applyLocalForceToCenter(RigidBody* pRigidBody, const Vector2& force) override {}
        std::vector<Collider*> getStaticColliders() override { return {}; }
        bool raycastWorld(RigidBody* start, RigidBody* target) override { return false; }
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

    //Clean up (needs to be done because otherwise the service will interfere with other tests)
    gameLoop.setInputService(nullptr);
}

TEST_CASE("GameLoop.start() calls dummy RenderService"){
    //Arrange
    auto* dummyService = new GameLoopTests::DummyRenderService {};
    GameLoop gameLoop {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setRenderService(dummyService);

    //Act
    gameLoop.start();

    //Assert
    SUBCASE("RenderFps is atleast 60"){
        CHECK_GE(gameLoop.time->getRenderFps(), 60); // Atleast 60FPS
    }
    SUBCASE("DummyService RenderCalls is atleast 60"){
        CHECK_GE(dummyService->renderCalls, 60); //Atleast 60FPS
    }
    SUBCASE("RenderDeltaTime is 60fps or faster"){
        CHECK_LE(gameLoop.time->getRenderDeltaTime(), 0.016667f);
        CHECK_GT(gameLoop.time->getRenderDeltaTime(), 0.f);
    }

    //Clean up (needs to be done because otherwise the service will interfere with other tests)
    gameLoop.setRenderService(nullptr);
}

TEST_CASE("GameLoop.start() calls dummy PhysicsService"){
    //Arrange
    GameLoop gameLoop {};
    auto* dummyService = new GameLoopTests::DummyPhysicsService {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setPhysicsService(dummyService);

    //Act
    gameLoop.start();

    //Assert
    SUBCASE("Physics FPS is around 60 fps"){
        // Since this is based on system performance we allow a small margin of error
        CHECK_GE(gameLoop.time->getPhysicsFps(), 59);
        CHECK_LE(gameLoop.time->getPhysicsFps(), 61);
    }
    SUBCASE("DummyService gets called"){
        CHECK_GT(dummyService->physicsCalls, 0);
    }
    SUBCASE("Physics DeltaTime should be around 0.0167"){
        // Since this is based on system performance we allow a small margin of error
        CHECK_GE(gameLoop.time->getPhysicsDeltaTime(), 0.015f);
        CHECK_LE(gameLoop.time->getPhysicsDeltaTime(), 0.017f);
    }

    //Clean up (needs to be done because otherwise the service will interfere with other tests)
    gameLoop.setPhysicsService(nullptr);
}

TEST_CASE("Setting timescale"){
    // Arrange
    GameLoop gameLoop {};
    auto* dummyService = new GameLoopTests::DummyPhysicsService {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setPhysicsService(dummyService);

    // Act
    GolfEngine::Time::setTimeScale(0.5f);
    gameLoop.start();

    // Assert
    SUBCASE("Physics FPS is around 30 fps with 0.5 timescale"){
        // Since this is based on system performance we allow a small margin of error
        CHECK_GE(gameLoop.time->getPhysicsFps(), 29);
        CHECK_LE(gameLoop.time->getPhysicsFps(), 32);
    }

    //Clean up (needs to be done because otherwise the service will interfere with other tests)
    gameLoop.setPhysicsService(nullptr);

    // Arrange
    gameLoop  = GameLoop{};
    dummyService = new GameLoopTests::DummyPhysicsService {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyService->gameLoop = &gameLoop;
    gameLoop.setPhysicsService(dummyService);

    // Act
    GolfEngine::Time::setTimeScale(2.0f);
    gameLoop.start();

    // Assert
    SUBCASE("Physics FPS is around 120 fps with 2 timescale"){
        // Since this is based on system performance we allow a small margin of error
        CHECK_GE(gameLoop.time->getPhysicsFps(), 119);
        CHECK_LE(gameLoop.time->getPhysicsFps(), 121);
    }

    //Clean up (needs to be done because otherwise the service will interfere with other tests)
    gameLoop.setPhysicsService(nullptr);

    // Arrange
    gameLoop  = GameLoop{};
    dummyService = new GameLoopTests::DummyPhysicsService {};
    auto* dummyRenderService = new GameLoopTests::DummyRenderService {};
    gameLoop.setFramesPerSeccond(60.f);
    dummyRenderService->gameLoop = &gameLoop;
    dummyService->gameLoop = &gameLoop;
    gameLoop.setRenderService(dummyRenderService);
    gameLoop.setPhysicsService(dummyService);

    // Act
    GolfEngine::Time::setTimeScale(0.0f);
    gameLoop.start();

    // Assert
    SUBCASE("Physics FPS is 0 fps with a timescale of 0.0"){
        CHECK_EQ(gameLoop.time->getPhysicsFps(), 0);
        CHECK_GT(gameLoop.time->getRenderFps(), 0);
    }

    //Clean up (needs to be done because otherwise the service will interfere with other tests)
    gameLoop.setRenderService(nullptr);
    gameLoop.setPhysicsService(nullptr);
}
