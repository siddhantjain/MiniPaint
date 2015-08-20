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
	
}
void Draw::undo()
{
	//enter code to undo the operation
	cout << "Draw undo" << endl;
}