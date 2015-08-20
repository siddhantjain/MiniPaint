// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "Resource.h"
#include "Commdlg.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace shape_maker;
using namespace file_maker;

using namespace std;
using namespace rapidxml;
#define MAX_LOADSTRING 100
#define BUFFER_SIZE 32

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
int shapeValue = -1;										//SJ: remove this global variable
int commandValue = -1;									//SJ: remove these global variables
int numOfShapes = 0;									//SJ:This limits the number of total number of shapes to range of int.
int cur_color = 0;
int current_selected_shape_id = 0;
POINT startPt;
POINT currentPt;
bool lButtonPress = false;
bool insert_shape = false;
bool show_bounding_box = false;
ShapeFactoryPtr shapeFactoryPtr(new ShapeFactory);
CommandFactoryPtr commandFactoryPtr(new CommandFactory);
void doFileSave(HWND);
void doFileOpen(HWND);

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void draw(HWND hWnd);
void paint(HWND hWnd);
void onLButtonDown(HWND hWnd, UINT wParam, UINT x, UINT y);
void onLButtonUp(HWND hWnd, UINT wParam, UINT x, UINT y);
void onMouseMove(HWND hWnd, UINT wParam, UINT x, UINT y);
void setShape(int);
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, 900, 600, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	int shape = 0;
	int command;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{

	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_SHAPE_RECTANGLE:
			setShape(1);
			break;
		case ID_SHAPE_ELLIPSE:
			setShape(3);
			break;
		case ID_SHAPE_TRIANGLE:
			setShape(2);
			break;
		case ID_FILE_SAVE:
			doFileSave(hWnd);
			break;
		case ID_FILE_OPEN:
			doFileOpen(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	}
	break;
	case WM_LBUTTONDOWN:
	{
		onLButtonDown(hWnd, (UINT)wParam, LOWORD(lParam), HIWORD(lParam));
	}
	break;
	case WM_LBUTTONUP:
	{
		onLButtonUp(hWnd, (UINT)wParam, LOWORD(lParam), HIWORD(lParam));
	}
	break;
	case WM_MOUSEMOVE:
	{
		onMouseMove(hWnd, (UINT)wParam, LOWORD(lParam), HIWORD(lParam));
	}
	break;
	case WM_PAINT:
	{
		paint(hWnd);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void setShape(int shapeID)
{
	shapeValue = shapeID;
}

void setCommand(int commandID)
{
	commandValue = commandID;
}

void onLButtonDown(HWND hWnd, UINT wParam, UINT x, UINT y)
{
	startPt.x = x;
	startPt.y = y;
	currentPt.x = x;
	currentPt.y = y;
	if (shapeValue != -1)
		insert_shape = true;
	else
	{
		//Code to decide on which shape is selected
		shape_select shape_selector;
		current_selected_shape_id = shape_selector.which_shape(x, y);
		InvalidateRect(hWnd, NULL, true);
		show_bounding_box = true;
	}
	return;
}

void onMouseMove(HWND hWndm, UINT wParam, UINT x, UINT y)
{
	if (insert_shape)
	{
		RECT rect = { x, y, currentPt.x, currentPt.y };
		InvalidateRect(hWndm, &rect, true); //Invalidate the last drawn shape
		currentPt.x = x;
		currentPt.y = y;
	}
	else if (1/*condition for moving shape*/)
	{
		//code for moving shape
	}
	return;
}

void onLButtonUp(HWND hWnd, UINT wParam, UINT x, UINT y)
{
	if (shapeValue != -1)
	{
		file_maker::File cur_file;
		switch (shapeValue)
		{
		case 1:
		{
			numOfShapes++;
			std::shared_ptr<Shape> shape_rect(shapeFactoryPtr->getShapeObject(shapeValue, numOfShapes, startPt.x, startPt.y, currentPt.x, currentPt.y, cur_color));
			CommandPtr command_draw(commandFactoryPtr->getCommandObject(1));
			command_draw->execute(shape_rect);
		}
		break;
		case 3:
		{
			numOfShapes++;
			std::shared_ptr<Shape> shape_ellipse(shapeFactoryPtr->getShapeObject(shapeValue, numOfShapes, startPt.x, startPt.y, currentPt.x, currentPt.y, cur_color));
			CommandPtr command_draw(commandFactoryPtr->getCommandObject(1));
			command_draw->execute(shape_ellipse);
		}
		break;
		case 2:
		{
			numOfShapes++;
			std::shared_ptr<Shape> shape_triangle(shapeFactoryPtr->getShapeObject(shapeValue, numOfShapes, startPt.x, startPt.y, currentPt.x, currentPt.y, cur_color));
			CommandPtr command_draw(commandFactoryPtr->getCommandObject(1));
			command_draw->execute(shape_triangle);
		}
		break;
		}
		insert_shape = false;
		shapeValue = -1;
		InvalidateRect(hWnd, NULL, true);
	}

	if (1/*condition to test for move and implement code*/)
	{
		//code for implementing move
	}
	return;
}


//SJ: Paint is what persists the shape on the screen
//TODO: We need to store everything we paint in a structure. So, everytime we paint, we display every shape that's on the structure.
//If we do that, the problem of the previous shape disappearing will be gone. 
//I am leaving that now, because I think this will be related to the way we design our shape class
void paint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC			hdc;
	hdc = BeginPaint(hWnd, &ps);
	FilePainter painter(hWnd, hdc);
	File cur_file;
	for (int runner = 0; runner < cur_file.get_shape_list().size(); runner++)
	{
		std::shared_ptr<Shape> temp = cur_file.get_shape_list()[runner];
		POINT TopLeft = { temp.get()->get_topleft_x(), temp.get()->get_topleft_y() };
		POINT BottomRight = { temp.get()->get_bottomright_x(), temp.get()->get_bottomright_y() };
		//alert(sizeof((*temp)));
		switch (temp.get()->get_type_id())
		{
		case 1:
			painter.draw_rectangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y, 0);
			break;
		case 3:
			painter.draw_ellipse(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y, 0);
			break;
		case 2:
		{
			painter.draw_triangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y, 0);
		}
		break;
		}
	}
	if (show_bounding_box)
	{
		painter.show_bounding_box(current_selected_shape_id);
	}
	::EndPaint(hWnd, &ps);
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void doFileSave(HWND hDlg)
{
	TCHAR   szFile[MAX_PATH] = TEXT("\0");
	OPENFILENAME   ofn;

	memset(&(ofn), 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);

	ofn.hwndOwner = hDlg;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = TEXT("ShapeMaker (*.sm)\0*.xml\0");
	ofn.lpstrTitle = TEXT("Save File As");
	ofn.Flags = OFN_HIDEREADONLY;
	ofn.lpstrDefExt = TEXT("xml");

	if (GetSaveFileName(&ofn))
	{
		xml_document<> doc;
		xml_node<>* decl = doc.allocate_node(node_declaration);
		decl->append_attribute(doc.allocate_attribute("version", "1.0"));
		decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
		doc.append_node(decl);

		xml_node<>* root = doc.allocate_node(node_element, "Shapes");
		root->append_attribute(doc.allocate_attribute("version", "1.0"));
		root->append_attribute(doc.allocate_attribute("type", "records"));
		doc.append_node(root);

		File currFile;
		//char id[33], topleftX[33], topLeftY[33], bottomRightX[33], bottomRightY[33];
		char *attr_value;
		int number_of_items = currFile.get_shape_list().size();
		for (int runner = 0; runner < number_of_items; runner++)
		{
			std::shared_ptr<Shape> shapeObject = currFile.get_shape_list()[runner];
			POINT TopLeft = { shapeObject.get()->get_topleft_x(), shapeObject.get()->get_topleft_y() };
			POINT BottomRight = { shapeObject.get()->get_bottomright_x(), shapeObject.get()->get_bottomright_y() };
			int shapeID = shapeObject->get_shape_id();
			int shape_type_id = shapeObject->get_type_id();
			int color = shapeObject->get_color();
			xml_node<> *child = doc.allocate_node(node_element, "Shape");

			attr_value = new char[BUFFER_SIZE];
			sprintf_s(attr_value, BUFFER_SIZE, "%d", shapeID);
			child->append_attribute(doc.allocate_attribute("id", attr_value));

			attr_value = new char[BUFFER_SIZE];
			sprintf_s(attr_value, BUFFER_SIZE, "%d", shape_type_id);
			child->append_attribute(doc.allocate_attribute("type", attr_value));

			attr_value = new char[BUFFER_SIZE];
			sprintf_s(attr_value, BUFFER_SIZE, "%d", TopLeft.x);
			child->append_attribute(doc.allocate_attribute("topLeftX", attr_value));

			attr_value = new char[BUFFER_SIZE];
			sprintf_s(attr_value, BUFFER_SIZE, "%d", TopLeft.y);
			child->append_attribute(doc.allocate_attribute("topLeftY", attr_value));

			attr_value = new char[BUFFER_SIZE];
			sprintf_s(attr_value, BUFFER_SIZE, "%d", BottomRight.x);
			child->append_attribute(doc.allocate_attribute("bottomRightX", attr_value));

			attr_value = new char[BUFFER_SIZE];
			sprintf_s(attr_value, BUFFER_SIZE, "%d", BottomRight.y);
			child->append_attribute(doc.allocate_attribute("bottomRightY", attr_value));

			attr_value = new char[BUFFER_SIZE];
			sprintf_s(attr_value, BUFFER_SIZE, "%d", color);
			child->append_attribute(doc.allocate_attribute("color", attr_value));

			root->append_node(child);
		}

		//storing the filename
		char *fileName;
		size_t outputSize = wcslen(ofn.lpstrFile) + 1;
		fileName = new char[outputSize];
		size_t charsConverted = 0;
		wcstombs_s(&charsConverted, fileName, outputSize, ofn.lpstrFile, outputSize);

		//save the file
		std::ofstream file_stored(fileName);
		file_stored << doc;
		file_stored.close();
		doc.clear();

	}
}

void doFileOpen(HWND hDlg)
{
	TCHAR   szFile[MAX_PATH] = TEXT("\0");
	OPENFILENAME   ofn1;

	memset(&(ofn1), 0, sizeof(ofn1));
	ofn1.lStructSize = sizeof(ofn1);

	ofn1.hwndOwner = hDlg;
	ofn1.lpstrFile = szFile;
	ofn1.nMaxFile = MAX_PATH;
	ofn1.lpstrFilter = TEXT("ShapeMaker (*.sm)\0*.xml\0");
	ofn1.lpstrTitle = TEXT("Save File As");
	ofn1.Flags = OFN_HIDEREADONLY;
	ofn1.lpstrDefExt = TEXT("xml");

	if (GetOpenFileName(&ofn1))
	{
		//renoving all the present objects from shapeList
		File::remove_all();

		//storing the filename
		char *fileName;
		size_t outputSize = wcslen(ofn1.lpstrFile) + 1;
		fileName = new char[outputSize];
		size_t charsConverted = 0;
		wcstombs_s(&charsConverted, fileName, outputSize, ofn1.lpstrFile, outputSize);

		// Read xml file =================================
		xml_document<> doc;
		std::ifstream file(fileName);

		std::stringstream buff;
		buff << file.rdbuf();
		std::string content(buff.str());
		doc.parse<0>(&content[0]);

		xml_node<>*root_node = doc.first_node("Shapes");
		numOfShapes = 0;
		for (xml_node<>* shapeNode = root_node->first_node("Shape"); shapeNode; shapeNode = shapeNode->next_sibling())
		{
			int shape_id = atoi(shapeNode->first_attribute("id")->value());
			int shape_type_id = atoi(shapeNode->first_attribute("type")->value());
			int topleft_x = atoi(shapeNode->first_attribute("topLeftX")->value());
			int topleft_y = atoi(shapeNode->first_attribute("topLeftY")->value());
			int bottomright_x = atoi(shapeNode->first_attribute("bottomRightX")->value());
			int bottomright_y = atoi(shapeNode->first_attribute("bottomRightY")->value());
			int color = atoi(shapeNode->first_attribute("color")->value());
			std::shared_ptr<Shape> shape(shapeFactoryPtr->getShapeObject(shape_type_id, numOfShapes, topleft_x, topleft_y, bottomright_x, bottomright_y, color));
			CommandPtr command_draw(commandFactoryPtr->getCommandObject(1));
			command_draw->execute(shape);
			numOfShapes++;
		}
		InvalidateRect(hDlg, NULL, TRUE);
		UpdateWindow(hDlg);
	}
}