#include "Shape.h"
#include "Command.h"
#ifndef CIRCLE_H
#define CIRCLE_H
namespace shape_maker
{
	class Circle :public Shape
	{
	private:
	public:
		Circle() : Shape(1,1,1,1,1,1,1)
		{

		}
		Circle(int shape_id, int tp_left_x, int tp_left_y, int bm_right_x, int bm_right_y, int color) : Shape(3, shape_id, tp_left_x, tp_left_y, bm_right_x, bm_right_y, color)
		{

		}
		~Circle()
		{

		}
	};
}
#endif