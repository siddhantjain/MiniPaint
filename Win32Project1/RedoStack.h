#ifndef REDOSTACK_H
#define REDOSTACK_H
#include <iostream>
#include <stack>
#include "model\Command.h"
class RedoStack
{
private:
	static std::stack<shape_maker::CommandPtr> redostack;
public:
	static void push_command(shape_maker::CommandPtr);
	static shape_maker::CommandPtr pop_command();//pop
	static int getSize();
};
#endif