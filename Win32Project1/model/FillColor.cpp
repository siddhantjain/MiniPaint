#include "FillColor.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
using namespace file_maker;
FillColor::FillColor()
{

}
void FillColor::execute(std::shared_ptr<Shape> shape)
{
	file_maker::File file_instance;
	file_instance.replace_shape(shape->get_shape_id(),shape);
}
void FillColor::undo(std::shared_ptr<Shape> shape)
{
	cout << "FillColor undo" << endl;
	file_maker::File::replace_shape(shape->get_shape_id(), oldShape);
	setoldShape(shape);
}
void FillColor::redo(std::shared_ptr<Shape> shape)
{
	file_maker::File::replace_shape(shape->get_shape_id(), oldShape);
	setoldShape(shape);
}
void FillColor::setoldShape(std::shared_ptr<Shape> old_shape)
{
	oldShape =old_shape;
}
std::shared_ptr<Shape> FillColor::getoldShape()
{
	return oldShape;
}