#include "Move.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
using namespace file_maker;
Move::Move()
{

}
void Move::execute(std::shared_ptr<Shape> shape)
{
	File cur_file;
	cur_file.replace_shape(shape->get_shape_id(), shape);
}
void Move::undo(std::shared_ptr<Shape> shape)
{
	cout << "Move undo" << endl;
}
void Move::redo(std::shared_ptr<Shape> shape)
{

}