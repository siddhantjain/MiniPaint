#ifndef COMMAND_H
#define COMMAND_H
#include <memory>
#include "Shape.h"
namespace shape_maker {
	//class Shape;
	class Command
	{
	protected:
		std::shared_ptr<Shape> oldShape;
	public:
		virtual void execute(std::shared_ptr<Shape> shape) = 0;
		virtual void undo(std::shared_ptr<Shape> shape) = 0;
		virtual void redo(std::shared_ptr<Shape> shape) = 0;
		virtual void setoldShape(std::shared_ptr<Shape> oldShape) = 0;
		virtual std::shared_ptr<Shape> getoldShape() = 0;
	};

	using CommandPtr = std::shared_ptr<Command>;
}
#endif
