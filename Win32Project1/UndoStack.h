#ifndef UNDOSTACK_H
#define UNDOSTACK_H
#include <iostream>
#include <stack>
#include "model\Command.h"
class UndoStack
{
private:
	static std::stack<shape_maker::CommandPtr> undostack;
public:
	static void push_command(shape_maker::CommandPtr);
	static shape_maker::CommandPtr pop_command();
	static int getSize();
};
#endif