#include "ShopLayer.hpp"
#include "Core/SDLBackend/Renderer.hpp"

namespace App
{
namespace LayerSystem
{
ShopLayer::ShopLayer(EventSystem::EventDispatcher& eventDispatcher,
                     Shop::ModifierManager* modifierManager, Core::SDLBackend::Renderer& renderer)
    : m_shop(std::make_unique<Shop::Shop>(renderer, modifierManager)),
      mr_eventDispatcher(eventDispatcher)
{
}

void ShopLayer::render(const Core::SDLBackend::Renderer& renderer)
{
    (void)renderer;
    if (m_shop->isEmpty())
        m_shop->populateShop();

    if (m_shop->doneShopping())
        mr_eventDispatcher.queueEvent(EventType::shopPhaseEnd);

    m_shop->render(renderer,
                   m_active ? Shop::Shop::UIDisabled::false_ : Shop::Shop::UIDisabled::true_);
}

ShopLayer::~ShopLayer()
{
}
} // namespace LayerSystem
} // namespace App
