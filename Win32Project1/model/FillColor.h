#include "Command.h"
#include "file.h"
#ifndef FILLCOLOR_H
#define FILLCOLOR_H
namespace shape_maker
{
	class FillColor : public Command
	{
	private:
		int oldColor;
	public:
		FillColor();
		//~FillColor();
		void execute(std::shared_ptr<Shape> shape);
		void undo(std::shared_ptr<Shape> shape);
		void redo(std::shared_ptr<Shape> shape);
		void setOldColor(int);
	};

}
#endif