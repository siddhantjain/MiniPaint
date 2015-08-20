#include "Command.h"
#include "Shape.h"
#ifndef MOVE_H
#define MOVE_H
namespace shape_maker
{
	class Move : public Command
	{
	public:
		Move();
		//~Move();
		void execute(std::shared_ptr<Shape> shape);
		void undo(std::shared_ptr<Shape> shape);
		void redo(std::shared_ptr<Shape> shape);
	};
}
#endif