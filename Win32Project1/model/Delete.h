#include "Command.h"

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
		void setoldShape(std::shared_ptr<Shape> oldShape);
		std::shared_ptr<Shape> getoldShape();
	};
}
#endif