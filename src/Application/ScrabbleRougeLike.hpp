#pragma once
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <nlohmann/json.hpp>

#include "../Core/SDLBackend/Renderer.hpp"
#include "../Core/SDLBackend/Texture.hpp"
#include "../Core/SDLBackend/Window.hpp"
#include "EventSystem/EventDispatcher.hpp"

#include "LayerSystem/LayerStack.hpp"

#include "StateManager.hpp"

namespace App
{
class Application
{
  public:
    Application();
    void run();
    ~Application();

  private:
    void ImGuiPreRender();
    void ImGuiPostRender();
    void ImGuiTheme();

  private:
    std::unique_ptr<Core::SDLBackend::Window> m_window;
    std::unique_ptr<Core::SDLBackend::Renderer> m_renderer;
    std::shared_ptr<Core::SDLBackend::Texture> m_menuTex;

    std::function<void(SDL_Event* e)> mf_ImGuiEventCallback;

    std::unique_ptr<EventSystem::EventDispatcher> m_eventDispatcher;
    std::unique_ptr<LayerSystem::LayerStack> m_layerStack;
    std::unique_ptr<StateManager> m_stateManager;

    bool m_fullscreen = false;
    bool m_devMode = false;
};
} // namespace App
