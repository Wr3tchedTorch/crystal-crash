#pragma once
#include "ProjectileAttributes.h"
#include <memory>

class ProjectileData
{
private:
	static std::shared_ptr<ProjectileAttributes> m_Diamond;
	static std::shared_ptr<ProjectileAttributes> m_RegularGem;

public:
	static std::shared_ptr<ProjectileAttributes> getDiamondAttributes();
	static std::shared_ptr<ProjectileAttributes> getRegularGemAttributes();
};