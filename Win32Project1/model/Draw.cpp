#include "Draw.h"
#include "file.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
using namespace file_maker;
Draw::Draw()
{

}
void Draw::execute(std::shared_ptr<Shape> shape)
{
	//SJ: Do a null check here
	file_maker::File file_instance;
	file_instance.add_shape(shape);
	setoldShape(NULL);
}
void Draw::undo(std::shared_ptr<Shape> shape)
{
	//enter code to undo the operation
	cout << "Draw undo" << endl;
	file_maker::File::remove_shape(shape->get_shape_id());
	setoldShape(shape);
}
void Draw::redo(std::shared_ptr<Shape> shape)
{
	file_maker::File::add_shape(oldShape);
	setoldShape(shape);
}
void Draw::setoldShape(std::shared_ptr<Shape> old_shape)
{
	oldShape = old_shape;
}
std::shared_ptr<Shape> Draw::getoldShape()
{
	return oldShape;
}