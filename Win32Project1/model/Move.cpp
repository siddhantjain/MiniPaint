#include "Move.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
Move::Move()
{

}
void Move::execute(std::shared_ptr<Shape> shape)
{
	cout << "Move executed" << endl;
}
void Move::undo(std::shared_ptr<Shape> shape)
{
	cout << "Move undo" << endl;
}
void Move::redo(std::shared_ptr<Shape> shape)
{

}
void Move::setoldShape(std::shared_ptr<Shape> old_shape)
{
	oldShape = old_shape;
}
std::shared_ptr<Shape> Move::getoldShape()
{
	return oldShape;
}