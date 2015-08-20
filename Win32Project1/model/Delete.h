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
		void undo();
	};
}
#endif