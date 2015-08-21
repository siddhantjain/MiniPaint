#include "Resize.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
using namespace file_maker;
Resize::Resize()
{

}
void Resize::execute(std::shared_ptr<Shape> shape)
{
	File cur_file;
	cur_file.replace_shape(shape->get_shape_id(), shape);
}
void Resize::undo(std::shared_ptr<Shape> shape)
{
	cout << "Resize undo" << endl;
	file_maker::File::replace_shape(shape->get_shape_id(), oldShape);
	setoldShape(shape);
}
void Resize::redo(std::shared_ptr<Shape> shape)
{
	file_maker::File::replace_shape(shape->get_shape_id(), oldShape);
	setoldShape(shape);
}
void Resize::setoldShape(std::shared_ptr<Shape> old_shape)
{
	oldShape = old_shape;
}
std::shared_ptr<Shape> Resize::getoldShape()
{
	return oldShape;
}