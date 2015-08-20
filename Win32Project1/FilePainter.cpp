#include "FilePainter.h"
#include "stdafx.h"

HWND FilePainter::hWnd;
HDC FilePainter::hdc;
FilePainter::FilePainter(HWND hwnd, HDC hDc)
{
	FilePainter::hWnd = hwnd;
	FilePainter::hdc = hDc;
}
void FilePainter::draw_rectangle(int tl_x, int tl_y, int br_x, int br_y, COLORREF c)
{
	::Rectangle(hdc, tl_x, tl_y, br_x, br_y);
	//code for drawing a rectangle
}

void FilePainter::draw_ellipse(int tl_x, int tl_y, int br_x, int br_y, COLORREF c)
{
	::Ellipse(hdc, tl_x, tl_y, br_x, br_y);
	//code for drawing an ellipse
}

void FilePainter::draw_triangle(int tl_x, int tl_y, int br_x, int br_y, COLORREF c)
{
	POINT P1, P2, P3;
	P1.x = tl_x + br_x / 2;
	P1.y = tl_y;
	P2.x = tl_x;
	P2.y = tl_y + br_y;
	P3.x = tl_x + br_x;
	P3.y = tl_y + br_y;
	POINT vertices[] = { P1, P2, P3 };
	::Polygon(hdc, vertices, 3);
	//code for drawing a triangle
}

void FilePainter::show_bounding_box(int selected_shape_id)
{
	file_maker::File temp_file;
	shared_ptr<Shape> temp_shape = temp_file.get_shape(selected_shape_id);
	if (temp_shape != NULL)
	{
		HPEN dashed_pen = CreatePen(PS_DASH, 10 , RGB(0,0,0));
		SelectObject(hdc, dashed_pen);
		SelectObject(hdc, ::GetStockObject(NULL_BRUSH));
		::Rectangle(hdc, temp_shape->get_topleft_x(), temp_shape->get_topleft_y(), temp_shape->get_bottomright_x(), temp_shape->get_bottomright_y());
	}
}