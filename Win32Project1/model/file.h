#include "Shape.h"
#include "ShapeFactory.h"
#include "..\stdafx.h"
#include <vector>
#ifndef FILE_H
#define FILE_H
using namespace shape_maker;
using namespace std;
namespace file_maker
{
	class File
	{
	private:
		static std::vector<std::shared_ptr<Shape>> shape_list;
	public:
		File()
		{}
		~File()
		{}
		//static std::vector<std::shared_ptr<Shape>*> shape_list;
		static void add_shape(std::shared_ptr<Shape> new_shape);
		static void remove_shape(int shape_id);
		static void replace_shape(int shape_id, std::shared_ptr<Shape> new_shape);
		std::shared_ptr<Shape> get_shape(int shape_id);
		static vector<std::shared_ptr<Shape>> get_shape_list();
		static void remove_all();
	};
}
#endif