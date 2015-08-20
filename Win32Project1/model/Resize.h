#include "Command.h"
#ifndef RESIZE_H
#define RESIZE_H
namespace shape_maker
{
	class Resize :public Command
	{
	public:
		Resize();
		//~Resize();
		void execute(std::shared_ptr<Shape> s);
		void undo();
	};
}
#endif