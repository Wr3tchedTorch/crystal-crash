#pragma once
#include "Slingshot.h"
class ISlingshotState
{
public:
	virtual void enter(Slingshot& slingshot) = 0;
	virtual void exit(Slingshot& slingshot) = 0;

	virtual void update(Slingshot& slingshot, float delta) = 0;
};

