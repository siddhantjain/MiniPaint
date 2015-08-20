#include <iostream>
#include <stack>
#include "model\Command.h"
class RedoStack
{
private:
	std::stack<shape_maker::CommandPtr> redostack;
public:
	void push_command(shape_maker::CommandPtr);
	shape_maker::CommandPtr pop_command();//pop
};