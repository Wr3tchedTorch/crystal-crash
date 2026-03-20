#include "StateSlingshotAiming.h"
#include <memory>
#include "ISlingshotState.h"
#include "Slingshot.h"
#include "DragSystem.h"
#include "StateSlingshotShooting.h"

void StateSlingshotAiming::enter(Slingshot& slingshot)
{
}

void StateSlingshotAiming::exit(Slingshot& slingshot)
{
	slingshot.reset();
}

std::unique_ptr<ISlingshotState> StateSlingshotAiming::update(Slingshot& slingshot, float delta)
{
	slingshot.updateChainLength();
	slingshot.updateChainRotation();
	slingshot.updateBeakPosition();

	if (!DragSystem::get().isDragging())
	{
		return std::make_unique<StateSlingshotShooting>();
	}

    return nullptr;
}
