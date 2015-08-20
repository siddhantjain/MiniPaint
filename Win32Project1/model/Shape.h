#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <memory>
#include "Command.h"
#include "../stdafx.h"
namespace shape_maker
{
	class Shape
	{
	private:
		int shape_type_id;
		int shape_id;
		int topleft_x;
		int topleft_y;
		int bottomright_x;
		int bottomright_y;
		int color;
	public:
		Shape() :shape_id(-1), shape_type_id(-1)
		{

		}
		Shape(int shape_type_id, int shape_id, int topleft_x, int topleft_y, int bottomright_x, int bottomright_y, int color) :shape_type_id(shape_type_id), shape_id(shape_id), topleft_x(topleft_x), topleft_y(topleft_y), bottomright_x(bottomright_x), bottomright_y(bottomright_y), color(color)
		{
			//alert("Constructor called")
		}
		int get_type_id();
		int get_shape_id();
		int get_topleft_x();
		int get_topleft_y();
		int get_bottomright_x();
		int get_bottomright_y();
		int get_color();
		void set_color();

		void set_shape_id(int id);
		void set_color(COLORREF in_color);
		void set_properties(int &topleft_x, int &topleft_y, int &bottomright_x, int &bottomright_y, int const &color);
	};
}
#endif