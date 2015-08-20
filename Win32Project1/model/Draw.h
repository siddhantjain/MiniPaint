#include "Command.h"
#include "Shape.h"
#ifndef DRAW_H
#define DRAW_H
namespace shape_maker
{
	class Draw : public Command
	{
	public:
		Draw();
		//~Draw();
		void execute(std::shared_ptr<Shape> shape);
		void undo(std::shared_ptr<Shape> shape);
		void redo(std::shared_ptr<Shape> shape);
	};
}

#endif