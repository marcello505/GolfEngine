#include <doctest.h>

#include "Scene/IPersistable.h"

using namespace GolfEngine::Scene;

namespace PersistableTests{
    class TestPersistable : public IPersistable{
    public:
        bool value {false};

        std::unique_ptr<ISnapshot> saveSnapshot() override {
            Snapshot snapshot {};
            snapshot.value = value;
            return std::make_unique<Snapshot>(snapshot);
        }

        void loadSnapshot(const ISnapshot& rawSnapshot) override {
            auto& snapshot = (Snapshot&)rawSnapshot;
            value = snapshot.value;
        }

    private:
        struct Snapshot : public ISnapshot{
            bool value;
        };
    };
}

TEST_SUITE("Persistable Tests"){
    TEST_CASE("IPersistable correctly saves and loads snapshot"){
        //Arrange
        PersistableTests::TestPersistable testPersistable {};

        //Act
        auto snapshot = testPersistable.saveSnapshot();
        testPersistable.value = true;

        //Assert
        CHECK(testPersistable.value);
        testPersistable.loadSnapshot(*snapshot);
        CHECK_FALSE(testPersistable.value);
    }

}