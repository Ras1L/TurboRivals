#ifndef APP_ISCENE_HPP
#define APP_ISCENE_HPP

class IScene {
public:
    virtual void Load() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() const = 0;
    virtual void Unload() = 0;
};

#endif