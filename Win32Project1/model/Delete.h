#include "Command.h"
#include "Shape.h"
#include "file.h"
#ifndef DELETE_H
#define DELETE_H
namespace shape_maker
{
	class Delete : public Command
	{
	public:
		Delete();
		//~Delete();
		void execute(std::shared_ptr<Shape> shape);
		void undo(std::shared_ptr<Shape> shape);
		void redo(std::shared_ptr<Shape> shape);
	};
}
#endif