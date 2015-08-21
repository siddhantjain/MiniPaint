#include "Delete.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
using namespace file_maker;
Delete::Delete()
{

}

void Delete::execute(std::shared_ptr<Shape> shape)
{
	File cur_file;
	cur_file.remove_shape(shape->get_shape_id());
}
void Delete::undo(std::shared_ptr<Shape> shape)
{
	
}
void Delete::redo(std::shared_ptr<Shape> shape)
{

}
void Delete::setoldShape(std::shared_ptr<Shape> old_shape)
{
	oldShape = old_shape;
}
std::shared_ptr<Shape> Delete::getoldShape()
{
	return oldShape;
}