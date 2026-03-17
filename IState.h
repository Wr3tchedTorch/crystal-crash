#pragma once

class IState
{
public:
	virtual void enter() = 0;
	virtual void exit()  = 0;

	virtual void update(float delta) = 0;
};
