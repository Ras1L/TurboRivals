#include "UI/UIManager.hpp"
#include "rlImGui.h"

void UIManager::Init()
{
    rlImGuiSetup(true);
    rlImGuiBeginInitImGui();
    // do smth
    rlImGuiEndInitImGui();
}

void UIManager::Begin()
{
    rlImGuiBegin();
}

void UIManager::End()
{
    rlImGuiEnd();
}

void UIManager::Deinit()
{
    rlImGuiShutdown();
}