#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include <imgui.h>
#include <nlohmann/json.hpp>

#include "../EventSystem/BasicEventObserver.hpp"
#include "Core/SDLBackend/Renderer.hpp"
#include "Core/SDLBackend/SpriteSheet.hpp"
#include "ModifierManager.hpp"

namespace App
{
namespace Shop
{
class Shop : public EventSystem::BasicEventObserver
{
  public:
    enum class UIDisabled
    {
        true_,
        false_
    };

  public:
    Shop(Core::SDLBackend::Renderer& renderer, ModifierManager* manager);

    void populateShop();

    void render(const Core::SDLBackend::Renderer& renderer, UIDisabled active);

    void onInput(const bool* keyboardState, EventType e,
                 const std::vector<uint32_t>& events) override;

    bool isEmpty() const;

    bool doneShopping() const;

  private:
    std::vector<std::reference_wrapper<const ModifierInfo>> m_modifierInfo;
    std::unordered_map<std::string, std::unique_ptr<Core::SDLBackend::SpriteSheet>>
        m_modifierSpriteSheets;
    ModifierManager* mrp_manager;

    bool m_render = false;
    bool m_doneShopping = false;
};
} // namespace Shop
} // namespace App
