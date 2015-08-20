#include "UndoStack.h"
void UndoStack::push_command(shape_maker::CommandPtr commandObject)
{
	undostack.push(commandObject);
}
shape_maker::CommandPtr UndoStack:: pop_command()
{
	if (!undostack.empty())
	{
		shape_maker::CommandPtr commandObject = undostack.top();
		undostack.pop();
		return commandObject;
	}
	else
		return NULL;
}
std::stack<shape_maker::CommandPtr> UndoStack::undostack;