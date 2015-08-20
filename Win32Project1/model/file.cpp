#include "file.h"

using namespace std;
using namespace shape_maker;
using namespace file_maker;
void File::add_shape(std::shared_ptr<Shape> new_shape)
{
	if (new_shape != NULL)
	{
		File::shape_list.push_back(new_shape);
		//alert();
	}
	else
		alert ("ERROR: Pushing a null shape in to the list");
	return;
}

void File::remove_shape(int shape_id)
{
	vector<std::shared_ptr<Shape>>::iterator it = shape_list.begin();
	vector<std::shared_ptr<Shape>>::iterator endIt = shape_list.end();
	
	for (; it != endIt; ++it)
	{
		if (it->get()->get_shape_id() == shape_id)
			break;
	}
	
	if (it==endIt)
	{
		cout << "ERROR: shape to be removed doesn't exist";
		return;
	}
	it = shape_list.erase(it);
}

void File::replace_shape(int shape_id, std::shared_ptr<Shape> new_shape)
{
	vector<std::shared_ptr<Shape>>::iterator it = shape_list.begin();
	vector<std::shared_ptr<Shape>>::iterator endIt = shape_list.end();

	for (; it != endIt; ++it)
	{
		if ((*it).get()->get_shape_id() == shape_id)
			shape_list.insert(it, new_shape);
	}

	if (it == endIt)
	{
		cout << "ERROR: shape to be replaced doesn't exist";
		return;
	}
}
std::shared_ptr<Shape> File::get_shape(int shape_id)
{
	vector<std::shared_ptr<Shape>>::iterator it = shape_list.begin();
	vector<std::shared_ptr<Shape>>::iterator endIt = shape_list.end();

	for (; it != endIt; ++it)
	{
		if (it->get()->get_shape_id() == shape_id)
			return *(it);
	}
	if (it == endIt)
	{
		//alert( "ERROR: shape to be returned doesn't exist");
		return NULL;
	}
	else
		return *(it);
}
void File::remove_all()
{
	shape_list.clear();
}
vector<std::shared_ptr<Shape>> File::get_shape_list()
{
	return shape_list;
}
std::vector<std::shared_ptr<Shape>> File::shape_list;