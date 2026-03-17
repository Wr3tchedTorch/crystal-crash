#pragma once
#include "MouseDragHandler.h"
#include "IDragState.h"
class DragSystem
{
private:
	static MouseDragHandler* m_Instance;

public:
	static void initialize(MouseDragHandler& handler);

	static IDragState& get();
};

