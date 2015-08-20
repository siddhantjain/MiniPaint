#include "Shape.h"
#include "Command.h"
#include "../stdafx.h"
#ifndef TRIANGLE_H
#define TRIANGLE_H
namespace shape_maker
{
	class Triangle :public Shape
	{
	private:
	public:
		Triangle() :Shape(1,1,1,1,1,1,1)
		{

		}
		Triangle(int shape_id, int tp_left_x, int tp_left_y, int bm_right_x, int bm_right_y, int color) : Shape(2, shape_id, tp_left_x, tp_left_y, bm_right_x, bm_right_y, color)
		{
			
		}
	};
}
#endif