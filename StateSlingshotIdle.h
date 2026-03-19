#pragma once
#include "ISlingshotState.h"
#include <memory>
#include "Slingshot.h"

class StateSlingshotIdle : public ISlingshotState
{
	void enter(Slingshot& slingshot) override;
	void exit(Slingshot& slingshot) override;
	std::unique_ptr<ISlingshotState> update(Slingshot& slingshot, float delta) override;
};

