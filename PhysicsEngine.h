#pragma once
#include <id.h>

class PhysicsEngine
{
private:
	const float GRAVITY = 9.8f;
	const float TIME_STEP = 1.0f / 60.0f;
	const int   SUB_STEP_COUNT = 4;

	b2WorldId m_WorldId;

	bool m_IsSimulating = true;
	static bool Instantiated;

public:
	PhysicsEngine();

	void switchSimulationState();

	void update(float delta);

	bool isSimulating() const;
	b2WorldId getWorldId() const;
};
