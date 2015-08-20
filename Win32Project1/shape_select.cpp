#include "shape_select.h"

int shape_select::which_shape(int x, int y)
{
	file_maker::File temp_file;
	vector<shared_ptr<Shape>> shape_list = temp_file.get_shape_list();
	shape_select::selected_shape_id = -1;
	for (int runner = 0; runner < shape_list.size(); runner++)
	{
		int temp_shape_tl_x = shape_list[runner]->get_topleft_x();
		int temp_shape_tl_y = shape_list[runner]->get_topleft_y();
		int temp_shape_br_x = shape_list[runner]->get_bottomright_x();
		int temp_shape_br_y = shape_list[runner]->get_bottomright_y();
		if ((x >= temp_shape_tl_x) && (x <= temp_shape_br_x) && (y >= temp_shape_tl_y) && (y <= temp_shape_br_y))
		{
			//alert("Hey");
			//hit shape object found //choose the latest drawn shape
			shape_select::selected_shape_id = shape_list[runner]->get_shape_id();
		}
	}
	return selected_shape_id;
}