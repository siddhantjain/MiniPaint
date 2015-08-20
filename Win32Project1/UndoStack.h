#include <iostream>
#include <stack>
#include "model\Command.h"
class UndoStack
{
private:
	std::stack<shape_maker::CommandPtr> undostack;
public:
	void push_command(shape_maker::CommandPtr);
	shape_maker::CommandPtr pop_command();
};