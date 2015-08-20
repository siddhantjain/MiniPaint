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
		void undo();
	};

}
#endif