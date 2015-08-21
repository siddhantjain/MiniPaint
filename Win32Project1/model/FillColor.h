#include "Command.h"
#include "file.h"
#ifndef FILLCOLOR_H
#define FILLCOLOR_H
namespace shape_maker
{
	class FillColor : public Command
	{
	public:
		FillColor();
		//~FillColor();
		void execute(std::shared_ptr<Shape> shape);
		void undo(std::shared_ptr<Shape> shape);
		void redo(std::shared_ptr<Shape> shape);
		void setoldShape(std::shared_ptr<Shape> oldShape);
		std::shared_ptr<Shape> getoldShape();
	};

}
#endif