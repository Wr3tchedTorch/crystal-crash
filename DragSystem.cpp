#include "DragSystem.h"
#include "MouseDragHandler.h"
#include "IDragState.h"

MouseDragHandler* DragSystem::m_Instance = nullptr;

void DragSystem::initialize(MouseDragHandler& handler)
{
	m_Instance = &handler;
}

IDragState& DragSystem::get()
{
	return *m_Instance;
}
