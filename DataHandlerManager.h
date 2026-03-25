#pragma once

#include <memory>
#include <string>

#include "WorldData.h"
#include "DataHandler.h"
#include "ProjectileAttributes.h"
#include "GraphicsAttributes.h"
#include "PolygonShapeAttributes.h"
#include "ShapeAttributes.h"

struct DataHandlerManager
{
	DataHandlerManager();

	std::shared_ptr<DataHandler<WorldData>>			     WorldDataHandler;
	std::shared_ptr<DataHandler<ProjectileAttributes>>   ProjectileDataHandler;
	std::shared_ptr<DataHandler<GraphicsAttributes>>     GraphicsDataHandler;

	std::shared_ptr<DataHandler<ShapeAttributes>> ShapeDataHandler;
	std::shared_ptr<DataHandler<PolygonShapeAttributes>> PolygonShapeDataHandler;

	std::shared_ptr<ShapeAttributes> getShapeAttributes(std::string type, int id) const
	{
		if (type == "Polygon")
		{
			return PolygonShapeDataHandler->getById(id);
		}

		return nullptr;
	}
};

