#pragma once
#include <expected>
#include <memory>
#include <string>
#include <unordered_map>

#include <sol/sol.hpp>

#include "../LuaScripting/Script.hpp"

namespace App
{
namespace Shop
{
struct Context
{
    const char* event;
    std::vector<std::string> words;
    int points;
    char ch;
    const int numRemainingTiles;
};

struct PointsReturn
{
    int addScore = 0;
    float addMult = 0;
    float mulMult = 0;
};

class Modifier
{
  public:
    enum class StaticModifierType
    {
        globalPriceReduction,
        pointsScoredMultiplier
    };

  public:
    Modifier(const std::unordered_map<StaticModifierType, float>& staticModifiers, bool stackable,
             std::unique_ptr<LuaScripting::Script> script = nullptr);

    PointsReturn getBonusRoundPoints(const Context& context);

    float getStaticPriceReduction() const;

    static auto stringToStaticModifier(const std::string& str)
        -> std::expected<StaticModifierType, std::string>;

  private:
    std::unique_ptr<LuaScripting::Script> m_script;
    mutable size_t m_numPreviousWords = 0;
    // config items
    std::unordered_map<StaticModifierType, float> m_staticModifiers;
    bool m_stackable = false;
};
} // namespace Shop
} // namespace App
