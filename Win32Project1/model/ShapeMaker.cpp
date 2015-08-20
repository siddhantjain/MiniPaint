#include "Shape.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "ShapeFactory.h"
#include "Delete.h"
#include "Draw.h"
#include "Resize.h"
#include "Move.h"
#include "FillColor.h"
#include "CommandFactory.h"
#include "..\stdafx.h"
using namespace shape_maker;
/*void main()
{
	ShapeFactoryPtr shapeFactoryPtr(new ShapeFactory);
	CommandFactoryPtr commandFactoryPtr(new CommandFactory);

	std::shared_ptr<Shape> obj1(shapeFactoryPtr->getShapeObject(1));
	CommandPtr cobj1(commandFactoryPtr->getCommandObject(1));
	
	cobj1->execute(obj1);

	std::shared_ptr<Shape> obj2(shapeFactoryPtr->getShapeObject(2));
	CommandPtr cobj2(commandFactoryPtr->getCommandObject(2));
	cobj2->execute(obj2);
	std::shared_ptr<Shape> obj3(shapeFactoryPtr->getShapeObject(3));
	CommandPtr cobj3(commandFactoryPtr->getCommandObject(3));
	cobj3->execute(obj3);

	std::shared_ptr<Shape> obj4(shapeFactoryPtr->getShapeObject(3));
	CommandPtr cobj4(commandFactoryPtr->getCommandObject(4));
	cobj4->execute(obj3);
}*/