#pragma once
#include <imgui.h>
#include <memory>

#include "BasicLayer.hpp"

#include "../Shop/ModifierManager.hpp"
#include "../Shop/Shop.hpp"

#include "../../Core/SDLBackend/Renderer.hpp"

namespace App
{
namespace LayerSystem
{
class ShopLayer : public BasicLayer
{
  public:
    ShopLayer(EventSystem::EventDispatcher& eventDispatcher, Shop::ModifierManager* modifierManager,
              Core::SDLBackend::Renderer& renderer);

    void render(const Core::SDLBackend::Renderer& renderer) override;

    ~ShopLayer() override;

  private:
    std::unique_ptr<Shop::Shop> m_shop;
    EventSystem::EventDispatcher& mr_eventDispatcher;
};
} // namespace LayerSystem
} // namespace App
