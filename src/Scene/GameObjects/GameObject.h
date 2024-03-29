//
// Created by conner on 11/21/2022.
//

#ifndef GOLFENGINE_GAMEOBJECT_H
#define GOLFENGINE_GAMEOBJECT_H


#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "../Transform.h"
#include "../IPersistable.h"
#include "../Components/Component.h"

namespace GolfEngine::Scene {
    // Forward declaration
    class Component;

    class GameObject : public IPersistable {
    private:
        struct Snapshot : public ISnapshot {
            bool active{};
            Transform localTransform{};
            std::vector<std::unique_ptr<ISnapshot>> componentSnapshots{};
        };
    protected:
        bool _active;
        std::unique_ptr<std::reference_wrapper<GameObject>> _parent;
        std::vector<std::reference_wrapper<GameObject>> _children;
        std::vector<std::unique_ptr<Component>> _components;
        Transform _localTransform{};
        const bool _recordable;
    public:
        std::string name;
        std::string tag;
        std::uint32_t layer;

    public:
        /// GameObject constructor
        /// \param name The name of the GameObject (nullptr is results in "")
        /// \param tag The tag of the GameObject (nullptr results in "default")
        GameObject(const char *name = nullptr, const char *tag = nullptr, bool recordable = true);

        virtual ~GameObject();

        /// Function creates a new Component for the GameObject
        /// \tparam C Component to create
        /// \tparam Args Arguments needed for constructor of C
        /// \return A reference to newly created component
        template<typename C, typename ... Args>
        C &addComponent(Args... args) {
            C &newComp = dynamic_cast<C &>(*_components.emplace_back(std::make_unique<C>(args...)));
            newComp.setParentGameObject(*this);
            newComp.setActive(true);
            return newComp;
        };

        /// Function retrieves a reference to a component of type C
        /// \tparam C Component to retrieve
        /// \return A reference to the found component, or nullptr when component is not found
        template<typename C>
        C &getComponent() const {
            if (!_components.empty()) {
                for (auto &comp: _components) {
//                 auto temp = dynamic_cast<typeof(comp.get())>(*comp);
                    // Try to cast to desired component
                    auto *castedComp = dynamic_cast<C *>(comp.get());
                    // Return if cast was successful
                    if (castedComp)
                        return dynamic_cast<C &>(*comp);
                }
            }
            throw std::runtime_error("No component found of given type in " + name);
        };

        /// Removes component from GameObject
        /// \tparam C Component to remove
        template<typename C>
        void removeComponent() {
            if (!_components.empty()) {
                for (auto comp = _components.begin(); comp < _components.end(); comp++) {
                    // Try to cast to desired component
                    auto *castedComp = dynamic_cast<C *>((*comp).get());
                    // Return if cast was successful
                    if (castedComp)
                        _components.erase(comp);
                }
            }
        }

        /// Checks if the GameObject has a component of type C
        /// \tparam C The type of component to check
        /// \return true if component is present in GameObject
        template<typename C>
        bool hasComponent() {
            if (!_components.empty()) {
                for (auto &comp: _components) {
                    // Try to cast to desired component
                    auto *castedComp = dynamic_cast<C *>(comp.get());
                    // Return if cast was successful
                    if (castedComp)
                        return true;
                }
            }
            return false;
        }

        /// Function retrieves a list of references to components of type C
        /// \tparam C Components to retrieve
        /// \return A list of references to the found components, or an empty list when no components are found
        template<typename C>
        std::vector<std::reference_wrapper<C>> getComponents() {
            std::vector<std::reference_wrapper<C>> components{};
            if (!_components.empty()) {
                for (auto &comp: _components) {
                    // Try to cast to desired component
                    auto *castedComp = dynamic_cast<C *>(comp.get());
                    // Add to list if cast was successful
                    if (castedComp)
                        components.push_back(dynamic_cast<C &>(*comp));
                }
            }
            return std::move(components);
        }

        /// Check whether the gameObject is currently active
        /// \return true if gameObject is active
        [[nodiscard]] bool getActive() const;

        /// Set active state of gameObject (calls onActive on all attached components)
        /// \param active new active state
        void setActive(bool active);

        /// Calls onStart on all attached components
        virtual void onStart();

        /// Calls onUpdate on all attached components
        virtual void onUpdate();

        /// Get attached children
        /// \return list of references to chidren attached to this gameObject
        std::vector<std::reference_wrapper<GameObject>> &children();

        /// Get child from children at a specific index
        /// \param index of child
        /// \return reference to child gameObject
        GameObject &childAt(int index);

        /// Get parent of this gameObject
        /// \return reference to gameObject of parent
        [[nodiscard]] GameObject &parent() const;

        /// Set the parent of this gameObject
        /// \param parent to be set
        void setParent(GameObject &parent);

        /// Link child object to this gameObject
        /// \param child to be set
        void addChild(GameObject &child);

        /// Return the local transform
        /// \return const Transform reference to the local transform
        const Transform &getLocalTransform() const;

        void setLocalTransform(const Transform &rTransform);

        void setLocalPosition(const Vector2 &rPosition);

        void setLocalRotation(const float &rotation);

        /// Calculates the current world transform and returns it
        /// \return A Transform instance which is the current world transform
        Transform getWorldTransform() const;

        /// Sets the current local transform so that it matches the given world transform
        /// \param rTransform the world transform that should be set
        void setWorldTransform(const Transform &rTransform);

        // IPersistable overrides
        std::unique_ptr<ISnapshot> saveSnapshot() override;

        void loadSnapshot(const ISnapshot &rawSnapshot) override;

        /// Get the recordable property of this gameObject
        /// \return true if gameObject is recordable
        bool isRecordable() const;
    };
}


#endif //GOLFENGINE_GAMEOBJECT_H
