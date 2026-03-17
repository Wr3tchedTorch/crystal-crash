#include "PhysicsEngine.h"
#include <box2d.h>
#include <types.h>
#include <cassert>
#include <id.h>

bool PhysicsEngine::Instantiated = false;

PhysicsEngine::PhysicsEngine()
{
	assert(!Instantiated);
	Instantiated = true;

	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0, GRAVITY };

	m_WorldId = b2CreateWorld(&worldDef);
}

void PhysicsEngine::switchSimulationState()
{
	m_IsSimulating = !m_IsSimulating;
}

void PhysicsEngine::update(float delta)
{
	if (m_IsSimulating)
	{
		b2World_Step(m_WorldId, TIME_STEP, SUB_STEP_COUNT);
	}
}

bool PhysicsEngine::isSimulating() const
{
	return m_IsSimulating;
}

b2WorldId PhysicsEngine::getWorldId() const
{
	return m_WorldId;
}
