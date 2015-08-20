#ifndef COMMAND_H
#define COMMAND_H
#include <memory>
namespace shape_maker {
	class Shape;
	class Command
	{
	private:
		std::shared_ptr<Shape> currShape;
		std::shared_ptr<Shape> oldShape;
	public:
		virtual void execute(std::shared_ptr<Shape> shape) = 0;
		virtual void undo() = 0;
	};

	using CommandPtr = std::shared_ptr<Command>;
}
#endif
