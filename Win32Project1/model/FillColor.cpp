#include "FillColor.h"
#include "..\stdafx.h"
using namespace std;
using namespace shape_maker;
FillColor::FillColor()
{

}
void FillColor::execute(std::shared_ptr<Shape> shape)
{
	cout << "FillColor executed" << endl;
}
void FillColor::undo()
{
	cout << "FillColor undo" << endl;
}