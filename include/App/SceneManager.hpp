#ifndef APP_SCENE_MANAGER_HPP
#define APP_SCENE_MANAGER_HPP

#include "App/ApplicationContext.hpp"
#include "App/IScene.hpp"
#include "Network/NetworkManager.hpp"
#include <memory>

struct Context {
    NetworkManager& network;
};

class SceneManager {
public:
    SceneManager(ApplicationContext& context);

    template <class S, class... Args>
    void Set(Args&&... args)
    {
        if (current) {
            current -> Unload();
        }
        current = std::make_unique<S>(std::forward<Args>(args)...);
        current -> Load();
    }

    void Update(float dt);
    void Render() const;
    void Reset();

private:
    std::unique_ptr<IScene> current;
    ApplicationContext&     context;
};

#endif