#ifndef APP_SESSION_BUILDER_HPP
#define APP_SESSION_BUILDER_HPP

#include "App/GameSceneInfo.hpp"
#include "Core/Session.hpp"
#include "Network/NetworkMessage.hpp"

class SessionBuilder {
public:
    static SessionState Deserialize(NetworkMessage net_msg);
    static SessionState Deserialize(GameSceneInfo info);
};

#endif