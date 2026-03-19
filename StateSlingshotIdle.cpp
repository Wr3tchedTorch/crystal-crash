#include "StateSlingshotIdle.h"
#include "Slingshot.h"
#include "DragSystem.h"
#include <memory>
#include "ISlingshotState.h"
#include "StateSlingshotAiming.h"
#include <iostream>

void StateSlingshotIdle::enter(Slingshot& slingshot)
{
	std::cout << std::format("\nSlingshot idle");

	slingshot.reset();
}

void StateSlingshotIdle::exit(Slingshot& slingshot)
{
}

std::unique_ptr<ISlingshotState> StateSlingshotIdle::update(Slingshot& slingshot, float delta)
{
	if (DragSystem::get().isDragging() && slingshot.isCurrentDragValid())
	{
		return std::make_unique<StateSlingshotAiming>();
	}
	return nullptr;
}
