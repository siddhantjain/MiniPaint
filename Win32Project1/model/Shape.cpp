#include "Shape.h"

using namespace shape_maker;

int Shape::get_type_id()
{
	return shape_type_id;
}

int Shape::get_shape_id()
{
	return shape_id;
}

int Shape::get_topleft_x()
{
	return topleft_x;
}

int Shape::get_topleft_y()
{
	return topleft_y;
}
int Shape::get_bottomright_x()
{
	return bottomright_x;
}
int Shape::get_bottomright_y()
{
	return bottomright_y;
}
int Shape::get_color()
{
	return color;
}
void Shape::set_shape_id(int id)
{
	shape_id = id;
}
void Shape::set_color(COLORREF in_color)
{
	color = in_color;
}
void Shape::set_shape_type_id(int id)
{
	shape_type_id = id;
}
void Shape::set_properties(int &in_topleft_x, int &in_topleft_y, int &in_bottomright_x, int &in_bottomright_y, int const &in_color)
{
	topleft_x = in_topleft_x;
	topleft_y = in_topleft_y;
	bottomright_x = in_bottomright_x;
	bottomright_y = in_bottomright_y;
	color = in_color;
}