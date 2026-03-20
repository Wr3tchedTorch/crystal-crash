#include "StateSlingshotShooting.h"
#include <memory>
#include "ISlingshotState.h"
#include "Slingshot.h"
#include <algorithm>
#include <utility>
#include "DragSystem.h"
#include "SlingshotConstants.h"
#include <cmath>
#include "StateSlingshotLoading.h"

void StateSlingshotShooting::enter(Slingshot& slingshot)
{
	float length	   = std::min(DragSystem::get().getDragDistance(), SlingshotConstants::MaxDragDistance);
	float impulseRatio = std::sqrt(length / SlingshotConstants::MaxDragDistance);

	slingshot.m_LoadedProjectiles.front()->launch(impulseRatio, DragSystem::get().getDragDirection());

	slingshot.m_LaunchedProjectiles.push_back(std::move(slingshot.m_LoadedProjectiles.front()));
	slingshot.m_LoadedProjectiles.pop_front();
}

void StateSlingshotShooting::exit(Slingshot& slingshot)
{
}

std::unique_ptr<ISlingshotState> StateSlingshotShooting::update(Slingshot& slingshot, float delta)
{
    return std::make_unique<StateSlingshotLoading>();
}
