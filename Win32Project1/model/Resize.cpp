#include "Resize.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
Resize::Resize()
{

}
void Resize::execute(std::shared_ptr<Shape> shape)
{
	cout << "Resize executed" << endl;
}
void Resize::undo(std::shared_ptr<Shape> shape)
{
	cout << "Resize undo" << endl;
}
void Resize::redo(std::shared_ptr<Shape> shape)
{

}