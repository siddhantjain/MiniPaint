#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include <memory>
#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
namespace shape_maker
{
	class ShapeFactory
	{
	public:
		std::shared_ptr<Shape> getShapeObject(int shape_type_id, int shape_id, int tp_left_x, int tp_left_y, int bm_right_x, int bm_right_y, int color)
		{
			if (shape_type_id == 1)
				return std::shared_ptr<Shape>(new Rectangle(shape_id, tp_left_x, tp_left_y, bm_right_x, bm_right_y, color));
			else if (shape_type_id == 2)
				return std::shared_ptr<Shape>(new Triangle(shape_id, tp_left_x, tp_left_y, bm_right_x, bm_right_y, color));
			else if (shape_type_id == 3)
				return std::shared_ptr<Shape>(new Circle(shape_id, tp_left_x, tp_left_y, bm_right_x, bm_right_y, color));
		}
	};
	using ShapeFactoryPtr = std::shared_ptr<ShapeFactory>;
}
#endif