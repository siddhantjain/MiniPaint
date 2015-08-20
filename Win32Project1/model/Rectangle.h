#include <iostream>
#include "Shape.h"
#include "Command.h"
#ifndef RECTANGLE_H
#define RECTANGLE_H
namespace shape_maker
{
	class Rectangle :public Shape
	{
	private:
		
	public:
		Rectangle() :Shape(1,1,1,1,1,1,1)
		{
		}
		Rectangle(int shape_id,int tp_left_x, int tp_left_y, int bm_right_x, int bm_right_y, int color) :Shape(1,shape_id,tp_left_x,tp_left_y,bm_right_x, bm_right_y,color)
		{

		}
		~Rectangle()
		{

		}
	};

}
#endif