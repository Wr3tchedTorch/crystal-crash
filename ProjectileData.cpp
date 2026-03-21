#include "ProjectileData.h"
#include <memory>
#include "ProjectileAttributes.h"
#include "PolygonShapeAttributes.h"
#include <math_functions.h>
#include "Converter.h"

std::shared_ptr<ProjectileAttributes> ProjectileData::m_Diamond = nullptr;
std::shared_ptr<ProjectileAttributes> ProjectileData::m_RegularGem = nullptr;

std::shared_ptr<ProjectileAttributes> ProjectileData::getDiamondAttributes()
{
    if (m_Diamond != nullptr)
    {
        return m_Diamond;
    }

    m_Diamond = std::make_shared<ProjectileAttributes>();

    m_Diamond->Name = "Diamante";
    m_Diamond->MaxSpeed = 40;
    m_Diamond->Damage   = 100;

    m_Diamond->getGraphics()->GraphicsId = "GEM 3 - DARK BLUE.png";
    m_Diamond->getGraphics()->TextureRect = { {0, 0}, {28, 28} };

    m_Diamond->getGraphics()->Animation.FrameCount = 11;
    m_Diamond->getGraphics()->Animation.AnimationCount = 1;
    m_Diamond->getGraphics()->Animation.DelayBeforeAnimationStart = 1;
    m_Diamond->getGraphics()->Animation.DelayBetweenFrames = 0.100f;
    m_Diamond->getGraphics()->Animation.Loop = true;

    std::shared_ptr<PolygonShapeAttributes> polygon = std::make_shared<PolygonShapeAttributes>();
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 12, 0 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 15, 0 })));

    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 27, 12 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 27, 15 })));

    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 15, 27 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 12, 27 })));

    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 0, 15 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 0, 12 })));

    const b2Vec2 center = converter::pixelsToMeters({ 14, 13 });

    for (auto& p : polygon->Points)
        p = b2Vec2(p.x - center.x, p.y - center.y);

    m_Diamond->setShape(polygon);

    return m_Diamond;
}

std::shared_ptr<ProjectileAttributes> ProjectileData::getRegularGemAttributes()
{
    if (m_RegularGem != nullptr)
    {
        return m_RegularGem;
    }

    m_RegularGem = std::make_shared<ProjectileAttributes>();

    m_RegularGem->Name = "Gema Padrão";
    m_RegularGem->MaxSpeed = 100;
    m_RegularGem->Damage = 35;

    m_RegularGem->getGraphics()->GraphicsId = "GEM 2 - LIGHT GREEN.png";
    m_RegularGem->getGraphics()->TextureRect = { {0, 0}, {23, 27} };

    m_RegularGem->getGraphics()->Animation.FrameCount = 10;
    m_RegularGem->getGraphics()->Animation.AnimationCount = 1;
    m_RegularGem->getGraphics()->Animation.DelayBeforeAnimationStart = 1;
    m_RegularGem->getGraphics()->Animation.DelayBetweenFrames = 0.100f;
    m_RegularGem->getGraphics()->Animation.Loop = true;

    std::shared_ptr<PolygonShapeAttributes> polygon = std::make_shared<PolygonShapeAttributes>();
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 0, 12 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 12, 0 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 13, 0 })));

    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 22, 9 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 22, 20 })));

    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 16, 26 })));
    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 6,  26 })));

    polygon->Points.push_back(b2Vec2(converter::pixelsToMeters({ 0, 20 })));

    const b2Vec2 center = converter::pixelsToMeters({ 13, 11 });

    for (auto& p : polygon->Points)
        p = b2Vec2(p.x - center.x, p.y - center.y);

    m_RegularGem->setShape(polygon);

    return m_RegularGem;
}
