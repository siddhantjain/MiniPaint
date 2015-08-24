// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "Resource.h"
#include "Commdlg.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "UndoStack.h"
#include "RedoStack.h"
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
COLORREF selected_color;
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
void setCommand(int);
void doFileSave(HWND);
void doFileOpen(HWND);
void doUndo(HWND);
void doRedo(HWND);
void preview_shape(HWND, POINT starting_pt, POINT ending_pt);
void get_shifted_corners(int* tl_x_new, int* tl_y_new, int* br_x_new, int* br_y_new, int change_in_x, int change_in_y, int mode);
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
			setCommand(0);
			break;
		case ID_SHAPE_ELLIPSE:
			setShape(3);
			setCommand(0);
			break;
		case ID_SHAPE_TRIANGLE:
			setShape(2);
			setCommand(0);
			break;
		case ID_OPTIONS_DELETE:
			setCommand(1);
			break;
		case ID_OPTIONS_FILL:
			static COLORREF arr_colors[16];
			CHOOSECOLOR lpcc;
			ZeroMemory(&lpcc, sizeof(lpcc));
			lpcc.lStructSize = sizeof(CHOOSECOLOR);
			lpcc.hwndOwner = NULL;
			lpcc.lpCustColors = arr_colors;
			lpcc.Flags = CC_FULLOPEN;
			if (ChooseColor(&lpcc))
			{
				selected_color = lpcc.rgbResult;
			}
			setCommand(2);
			break;
		case ID_OPTIONS_MOVE:
			setCommand(3);
			break;
		case ID_OPTIONS_RESIZE:
			setCommand(4);
			break;
		case ID_OPTIONS_REDO:
			doRedo(hWnd);
			break;
		case ID_OPTIONS_UNDO:
			doUndo(hWnd);
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
	case WM_CHAR: //Keyboard Shortcuts
	{
		char c = (TCHAR)wParam;
		if (c == 'D')
		{
			setCommand(1);
		}
		else if (c == 'Z')
		{
			doUndo(hWnd);
		}
		else if (c == 'X')
		{
			doRedo(hWnd);
		}
		else if (c == 'M')
		{
			setCommand(3);
		}
		else if (c == 'R')
		{
			setCommand(4);
		}
		else if (c == 'S')
		{
			doFileSave(hWnd);
		}
		else if (c == 'O')
		{
			doFileOpen(hWnd);
		}
		else if (c == 'F')
		{
			static COLORREF arr_colors[16];
			CHOOSECOLOR lpcc;
			ZeroMemory(&lpcc, sizeof(lpcc));
			lpcc.lStructSize = sizeof(CHOOSECOLOR);
			lpcc.hwndOwner = NULL;
			lpcc.lpCustColors = arr_colors;
			lpcc.Flags = CC_FULLOPEN;
			if (ChooseColor(&lpcc))
			{
				selected_color = lpcc.rgbResult;
			}
			setCommand(2);
		}

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
	lButtonPress = true;
	File lButtonFile;
	vector<shared_ptr<Shape>> list_of_shapes = lButtonFile.get_shape_list();
	if (shapeValue != -1)
	{
		insert_shape = true;
		//preview_shape(hWnd);
	}
	else
	{
		//Code to decide on which shape is selected
		shape_select shape_selector;
		current_selected_shape_id = shape_selector.which_shape(x, y);
		//InvalidateRect(hWnd, NULL, true);
		show_bounding_box = true;
		InvalidateRect(hWnd, NULL, true);
		if (current_selected_shape_id > 0)
		{
			switch (commandValue)
			{
				case 1:
				{	//Delete Command
					CommandPtr command_remove(commandFactoryPtr->getCommandObject(4));
					command_remove->execute(lButtonFile.get_shape(current_selected_shape_id));
					UndoStack::push_command(command_remove);
					current_selected_shape_id = 0;
				}
				break;
				case 2:
				{
					shared_ptr<Shape> new_shape(new Shape());
					shared_ptr<Shape> old_shape = lButtonFile.get_shape(current_selected_shape_id);
					CommandPtr command_fill(commandFactoryPtr->getCommandObject(2));
					command_fill->setoldShape(old_shape);
					new_shape->set_shape_id(old_shape->get_shape_id());
					new_shape->set_shape_type_id(old_shape->get_type_id());
					int lefttopx = old_shape->get_topleft_x();
					int lefttopy = old_shape->get_topleft_y();
					int bottomrightx = old_shape->get_bottomright_x();
					int bottomrighty = old_shape->get_bottomright_y();
					new_shape->set_properties(lefttopx, lefttopy, bottomrightx, bottomrighty, selected_color);

					command_fill->execute(new_shape);
					UndoStack::push_command(command_fill);
				}
			}
		}
	}
	return;
}

void onMouseMove(HWND hWndm, UINT wParam, UINT x, UINT y)
{
	File cur_file;
	if (insert_shape)
	{ 
		preview_shape(hWndm,startPt,currentPt);
		currentPt.x = x;
		currentPt.y = y;
		preview_shape(hWndm,startPt,currentPt);
	}
	else if (lButtonPress==true && (commandValue==3 || commandValue == 4))
	{
		if (commandValue == 4)
		{
			POINT shape_start_pt = POINT{ cur_file.get_shape(current_selected_shape_id)->get_topleft_x(),
				cur_file.get_shape(current_selected_shape_id)->get_topleft_y() };
			preview_shape(hWndm, shape_start_pt, currentPt);
			currentPt.x = x;
			currentPt.y = y;
			preview_shape(hWndm, shape_start_pt, currentPt);
		}
		else
		{
			currentPt.x = x;
			currentPt.y = y;
		}
		//InvalidateRect(hWndm, NULL, true);
	}
	return;
}

void onLButtonUp(HWND hWnd, UINT wParam, UINT x, UINT y)
{
	lButtonPress = false;
	file_maker::File cur_file;
	if (shapeValue != -1)
	{
		numOfShapes++;
		CommandPtr command_draw(commandFactoryPtr->getCommandObject(1));
		switch (shapeValue)
		{
			
			case 1:
			{
				std::shared_ptr<Shape> shape_rect(shapeFactoryPtr->getShapeObject(shapeValue, numOfShapes, startPt.x, startPt.y, currentPt.x, currentPt.y, cur_color));
				command_draw->execute(shape_rect);
			}
			break;
			case 3:
			{
				std::shared_ptr<Shape> shape_ellipse(shapeFactoryPtr->getShapeObject(shapeValue, numOfShapes, startPt.x, startPt.y, currentPt.x, currentPt.y, cur_color));
				command_draw->execute(shape_ellipse);
			}
			break;
			case 2:
			{
				std::shared_ptr<Shape> shape_triangle(shapeFactoryPtr->getShapeObject(shapeValue, numOfShapes, startPt.x, startPt.y, currentPt.x, currentPt.y, cur_color));
				command_draw->execute(shape_triangle);
			}
			break;
		}
		UndoStack::push_command(command_draw);
		insert_shape = false;
		shapeValue = -1;
		InvalidateRect(hWnd, NULL, true);
	}

	if (commandValue==3)
	{ //move
		commandValue = -1;
		if (current_selected_shape_id == -1)
		{
			alert("No shape selected to move");
			return;
		}
		std::shared_ptr<Shape> new_shape(new Shape());
		std::shared_ptr<Shape> old_shape= cur_file.get_shape(current_selected_shape_id);
		CommandPtr command_move(commandFactoryPtr->getCommandObject(5));
		command_move->setoldShape(old_shape);

		int change_in_x = currentPt.x - startPt.x;
		int change_in_y = currentPt.y - startPt.y;
		int tl_x_new = old_shape->get_topleft_x();
		int tl_y_new = old_shape->get_topleft_y();
		int br_x_new = old_shape->get_bottomright_x();
		int br_y_new = old_shape->get_bottomright_y();
		get_shifted_corners(&tl_x_new, &tl_y_new, &br_x_new, &br_y_new, change_in_x, change_in_y, 1);

		new_shape->set_shape_id(old_shape->get_shape_id());
		new_shape->set_shape_type_id(old_shape->get_type_id());
		new_shape->set_properties(tl_x_new, tl_y_new, br_x_new, br_y_new, old_shape->get_color());

		command_move->execute(new_shape);
		UndoStack::push_command(command_move);

		InvalidateRect(hWnd, NULL, true);
	}
	if (commandValue == 4)
	{
		commandValue = -1;
		if (current_selected_shape_id == -1)
	{
			alert("No shape selected to resize");
			return;
		}
		std::shared_ptr<Shape> new_shape(new Shape());
		std::shared_ptr<Shape> old_shape = cur_file.get_shape(current_selected_shape_id);
		CommandPtr command_move(commandFactoryPtr->getCommandObject(3));

		command_move->setoldShape(old_shape);

		int change_in_x = currentPt.x - startPt.x;
		int change_in_y = currentPt.y - startPt.y;
		int tl_x_new = old_shape->get_topleft_x();
		int tl_y_new = old_shape->get_topleft_y();
		int br_x_new = old_shape->get_bottomright_x();
		int br_y_new = old_shape->get_bottomright_y();
		get_shifted_corners(&tl_x_new, &tl_y_new, &br_x_new, &br_y_new, change_in_x, change_in_y, 2);

		new_shape->set_shape_id(old_shape->get_shape_id());
		new_shape->set_shape_type_id(old_shape->get_type_id());
		new_shape->set_properties(tl_x_new, tl_y_new, br_x_new, br_y_new, old_shape->get_color());
		
		command_move->execute(new_shape);

		UndoStack::push_command(command_move);
		InvalidateRect(hWnd, NULL, true);
	}
	return;
}

void get_shifted_corners(int* tl_x_new, int* tl_y_new, int* br_x_new, int* br_y_new, int change_in_x, int change_in_y, int mode)
{
	//move mode
	if (mode == 1)
	{
		*tl_x_new = *tl_x_new + change_in_x;
		*tl_y_new = *tl_y_new + change_in_y;
		*br_x_new = *br_x_new + change_in_x;
		*br_y_new = *br_y_new + change_in_y;
	}
	//resize mode
	else  if (mode == 2)
	{
		if ((change_in_x * change_in_y) > 0)
		{
			*br_x_new += change_in_x;
			*br_y_new += change_in_y;
		}
		else 
		{
			alert("Resize only from bottom right point");
		}
	}

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
	vector<shared_ptr<Shape>> shapeList = cur_file.get_shape_list();
	for (int runner = 0; runner < shapeList.size(); runner++)
	{
		std::shared_ptr<Shape> temp = cur_file.get_shape_list()[runner];
		POINT TopLeft = { temp.get()->get_topleft_x(), temp.get()->get_topleft_y() };
		POINT BottomRight = { temp.get()->get_bottomright_x(), temp.get()->get_bottomright_y() };
		COLORREF shape_color = temp.get()->get_color();
		//alert(sizeof((*temp)));
		switch (temp.get()->get_type_id())
		{
		case 1:
			painter.draw_rectangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y, shape_color);
			break;
		case 3:
			painter.draw_ellipse(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y, shape_color);
			break;
		case 2:
		{
			painter.draw_triangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y, shape_color);
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

void preview_shape(HWND hWnd, POINT prev_start_pt, POINT prev_curr_pt)
{
	HDC hdc;
	hdc = ::GetDC(hWnd);
	::SetROP2(hdc, R2_NOT);
	::SelectObject(hdc, ::GetStockObject(NULL_BRUSH));
	File cur_file;
	//alert(current_selected_shape_id);
	int current_shape_type_id = insert_shape ? shapeValue : current_selected_shape_id ? cur_file.get_shape(current_selected_shape_id)->get_type_id():0;
	//alert(sizeof((*temp)));
	//InvalidateRect(hWnd, NULL, true);

	switch (current_shape_type_id)
	{
	case 0:
		return;
		break;
	case 1:
		::Rectangle(hdc, prev_start_pt.x, prev_start_pt.y, prev_curr_pt.x, prev_curr_pt.y);
		break;
	case 3:
		::Ellipse(hdc, prev_start_pt.x, prev_start_pt.y, prev_curr_pt.x, prev_curr_pt.y);
		break;
	case 2:
	{
		POINT P1, P2, P3;
		P1.x = (prev_curr_pt.x + prev_start_pt.x) / 2;
		P1.y = prev_start_pt.y;
		P2.x = prev_start_pt.x;
		P2.y = prev_curr_pt.y;
		P3.x = prev_curr_pt.x;
		P3.y = prev_curr_pt.y;
		POINT vertices[] = { P1, P2, P3 };
		::Polygon(hdc, vertices, 3);
	}
	break;
	}
	::ReleaseDC(hWnd, hdc);
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
void doUndo(HWND hWnd)
{
	CommandPtr commandObject = UndoStack::pop_command();
	shared_ptr<Shape> shapeObject = commandObject->getoldShape();
	File cur_file;
	if (shapeObject!=NULL)
	{
		int index = shapeObject->get_shape_id();
		shared_ptr<Shape> newShape = cur_file.get_shape(index);
		commandObject->undo(newShape);
	}
	else
	{
		int index = File::get_shape_list().size() - 1;
		commandObject->undo(File::get_shape_list()[index]);
	}
	RedoStack::push_command(commandObject);

	InvalidateRect(hWnd,NULL,TRUE);
	UpdateWindow(hWnd);
}
void doRedo(HWND hWnd)
{
	CommandPtr commandObject = RedoStack::pop_command();
	/*vector<shared_ptr<Shape>> shapeList = File::get_shape_list();
	int index = File::get_shape_list().size() - 1;
	shared_ptr<Shape> shapeObject;
	if (index > -1)
		shapeObject= shapeList[index];
	else
		shapeObject = NULL;
	commandObject->redo(shapeObject);*/
	shared_ptr<Shape> shapeObject = commandObject->getoldShape();
	File cur_file;
	if (shapeObject != NULL)
	{
		int index = shapeObject->get_shape_id();
		shared_ptr<Shape> newShape = cur_file.get_shape(index);
		commandObject->redo(newShape);
	}
	else
	{
		int index = File::get_shape_list().size() - 1;
		commandObject->redo(File::get_shape_list()[index]);
	}
	UndoStack::push_command(commandObject);
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}