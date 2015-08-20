#include "stdafx.h"
#include "Resource.h"
#include "model\file.h"
#include <windows.h>
class FilePainter
{
	static HWND hWnd;
	static HDC hdc;
public:
	FilePainter(HWND hwnd, HDC hDc);
	~FilePainter(){};
	static void draw_rectangle(int l, int t, int width, int height, COLORREF c);
	static void draw_ellipse(int l, int t, int width, int height, COLORREF c);
	static void draw_triangle(int l, int t, int width, int height, COLORREF c);
	static void show_bounding_box(int selected_shape_id);
};