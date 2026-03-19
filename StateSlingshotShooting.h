#pragma once
#include "Slingshot.h"
#include <memory>
#include "ISlingshotState.h"

class StateSlingshotShooting : public ISlingshotState
{
	void enter(Slingshot& slingshot) override;
	void exit(Slingshot& slingshot) override;
	std::unique_ptr<ISlingshotState> update(Slingshot& slingshot, float delta) override;
};

