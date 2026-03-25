#pragma once
#include "DataHandlerManager.h"
#include <memory>
#include "PolygonShapeAttributes.h"

class ShapeFactory
{
private:
	DataHandlerManager& m_Handler;

public:
	ShapeFactory(DataHandlerManager& handler);
	
	std::shared_ptr<PolygonShapeAttributes> getPolygonAttributes();
};

