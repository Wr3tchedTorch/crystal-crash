#pragma once

#include <memory>

#include "WorldData.h"
#include "DataHandler.h"
#include "ProjectileAttributes.h"
#include "GraphicsAttributes.h"
#include "ShapeAttributes.h"
#include "PolygonShapeAttributes.h"

struct DataHandlerManager
{
	DataHandlerManager();

	std::shared_ptr<DataHandler<WorldData>>			     WorldDataHandler;
	std::shared_ptr<DataHandler<ProjectileAttributes>>   ProjectileDataHandler;
	std::shared_ptr<DataHandler<GraphicsAttributes>>     GraphicsDataHandler;
	std::shared_ptr<DataHandler<PolygonShapeAttributes>> PolygonShapeDataHandler;
};

