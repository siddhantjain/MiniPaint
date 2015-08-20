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
void Move::undo()
{
	cout << "Move undo" << endl;
}