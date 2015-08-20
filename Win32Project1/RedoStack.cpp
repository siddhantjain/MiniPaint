#include "RedoStack.h"
void RedoStack::push_command(shape_maker::CommandPtr commandObject)
{
	redostack.push(commandObject);
}
shape_maker::CommandPtr RedoStack::pop_command()
{
	if (!redostack.empty())
	{
		shape_maker::CommandPtr commandObject = redostack.top();
		redostack.pop();
		return commandObject;
	}
	else
		return NULL;
}
std::stack<shape_maker::CommandPtr> RedoStack::redostack;