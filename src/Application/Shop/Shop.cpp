#include "Shop.hpp"
#include "Core/SDLBackend/Renderer.hpp"
#include "Core/SDLBackend/SpriteSheet.hpp"
#include <imgui.h>
#include <nlohmann/detail/input/parser.hpp>

namespace App
{
namespace Shop
{
Shop::Shop(Core::SDLBackend::Renderer& renderer, ModifierManager* manager)
    : m_modifierSpriteSheets(), mrp_manager(manager)
{
    m_modifierSpriteSheets.emplace(std::pair{
        "<DEFAULT>", std::make_unique<Core::SDLBackend::SpriteSheet>(
                         renderer.getRendHand(), "assets/Textures/BaseModifiers/BaseModifiers.png",
                         32, 32, 2, 1)});
}

void Shop::populateShop()
{
    m_modifierInfo = mrp_manager->getShopOptions(3);
}

void Shop::render(const Core::SDLBackend::Renderer& renderer, UIDisabled active)
{
    /*if (active == UIDisabled::false_)
        ImGui::Begin("SHOP");
    else
        ImGui::Begin("SHOP", nullptr, ImGuiWindowFlags_NoInputs);
    ImGui::BeginDisabled(active == UIDisabled::true_);*/

    SDL_FRect rect = {.x = 100.0f, .y = 100.0f, .w = 32.0f, .h = 32.0f};

    for (size_t i = 0; i < m_modifierInfo.size(); i++)
    {
        auto& modr = m_modifierInfo[i].get();

        glm::vec2 itemPos;
        if (!m_modifierSpriteSheets.contains(modr.spriteSheetFPath))
        {
            std::cout << "WARNING: Custom modifier sprite sheet support has NOT been added yet, "
                         "Modifier SKIPPED\n";
            // m_modifierSpriteSheet.emplace(std::pair{
            //		modr.spriteSheetFPath,
            //		std::make_unique<Core::SDLBackend::SpriteSheet>(renderer, mrp_manager)
            //		});
        }
        else
        {
            auto& spriteSheet = m_modifierSpriteSheets.at(std::string{"<DEFAULT>"});
            spriteSheet->setFrame(modr.spriteSheetFrame);
            spriteSheet->render(renderer);
            switch (i)
            {
            case 0:
                itemPos = glm::vec2(111, 251);
                break;
            case 1:
                itemPos = glm::vec2(349, 251);
                break;
            case 2:
                itemPos = glm::vec2(572, 251);
                break;
            default:
                std::cout << "WARNING: More than 3 shop items is not currently supported. Nax "
                             "number is 3.\n";
                break;
            }

            spriteSheet->pos = itemPos;
        }

        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::SetNextWindowSize(ImVec2(32.0f, 0.0f), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(itemPos.x, itemPos.y));
        ImGui::Begin(std::string(std::string("## Shop Item ") + std::to_string(i)).c_str(), nullptr,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove);

        if (ImGui::InvisibleButton(modr.id.c_str(), ImVec2(32, 32)))
        {
            mrp_manager->selectOption(modr.id);
            m_modifierInfo.clear();
            m_doneShopping = true;
            ImGui::End();
            break;
        }

        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 400.0f);

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 255.0f, 255.0f));
            ImGui::TextWrapped("Name: ");
            ImGui::PopStyleColor();
            ImGui::TextWrapped("%s\n\n", modr.id.c_str());

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 255.0f, 255.0f));
            ImGui::TextWrapped("Description: ");
            ImGui::PopStyleColor();
            ImGui::TextWrapped("%s\n\n", modr.description.c_str());

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 255.0f, 255.0f));
            ImGui::TextWrapped("Price: ");
            ImGui::PopStyleColor();
            ImGui::TextWrapped("%d\n\n", modr.cost);

            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
        ImGui::End();
    }
    if (false || ImGui::Button("Done Shopping"))
    {
        m_modifierInfo.clear();
        m_doneShopping = true;
    }

    // ImGui::EndDisabled();
    // ImGui::End();
}

void Shop::onInput(const bool* keyboardState, EventType e, const std::vector<uint32_t>& events)
{
    (void)events;
    (void)keyboardState;
    switch (e)
    {
    case EventType::roundStart:
        break;
    case EventType::roundEnd:
        break;
    case EventType::wordConfirmed:
        break;
    case EventType::screenShake:
        break;
    case EventType::enterDevMode:
        break;
    case EventType::gameEnd:
        break;
    default:
        break;
    }
}

bool Shop::isEmpty() const
{
    return !m_doneShopping ? m_modifierInfo.empty() : false;
}

bool Shop::doneShopping() const
{
    return m_doneShopping;
}
} // namespace Shop
} // namespace App
