#pragma once
#include <memory>

class Slingshot;

class ISlingshotState
{
public:
	virtual void enter(Slingshot& slingshot) = 0;
	virtual void exit(Slingshot& slingshot) = 0;

	virtual std::unique_ptr<ISlingshotState> update(Slingshot& slingshot, float delta) = 0;
};

