#include "Command.h"
#include "Draw.h"
#include "FillColor.h"
#include "Resize.h"
#include "Delete.h"
#include "Move.h"
#include <memory>
#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
namespace shape_maker
{
	class CommandFactory
	{
	public:
		CommandPtr getCommandObject(int id)
		{
			if (id == 1)
				return CommandPtr(new Draw());
			else if (id == 2)
				return CommandPtr(new FillColor());
			else if (id == 3)
				return CommandPtr(new Resize());
			else if (id == 4)
				return CommandPtr(new Delete());
			else if (id == 5)
				return CommandPtr(new Move());
		}
	};
	using CommandFactoryPtr = std::shared_ptr<CommandFactory>;
}
#endif