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
		void undo(std::shared_ptr<Shape> shape);
		void redo(std::shared_ptr<Shape> shape);
		void setoldShape(std::shared_ptr<Shape> oldShape);
		std::shared_ptr<Shape> getoldShape();
	};
}
#endif