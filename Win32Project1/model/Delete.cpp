#include "Delete.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
Delete::Delete()
{

}

void Delete::execute(std::shared_ptr<Shape> shape)
{
	cout << "Delete executed" << endl;
}
void Delete::undo(std::shared_ptr<Shape> shape)
{
	cout << "Delete undo" << endl;
}
void Delete::redo(std::shared_ptr<Shape> shape)
{

}