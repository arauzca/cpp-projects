/*/////////////////////////////////////////////////////////////////////////////
module:  implementation of FLTK utility class
purpose: implements general utilities for FLTK/GLUT/OS support

written: U.Kuenzler
history: 1.00 - initial version of FLTK system nativ common dialog boxes
/////////////////////////////////////////////////////////////////////////////*/




// system includes ////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
using namespace std;




// OpenGL helper includes /////////////////////////////////////////////////////////////////////////
#include <FL/glut.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/fl_ask.H>
#include "../inc/UtilFLTK.h"



bool UtilFLTK::getFilePath(string& filepath, 
	const string& filter, const string& initial, bool open)
///////////////////////////////////////////////////////////////////////////////
{
	bool result = false;

	// Create the local native file chooser

	Fl_Native_File_Chooser fltk_filechooser;
	if (open)
	{
		fltk_filechooser.title("Open GLDraw2D Drawing File");
		fltk_filechooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
	}
	else
	{
		fltk_filechooser.title("Save GLDraw2D Drawing File");
		fltk_filechooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	}
	fltk_filechooser.filter(filter.c_str());
	fltk_filechooser.directory(initial.c_str());  // default directory to use
										  
	switch (fltk_filechooser.show()) // Show native chooser
	{
	    case -1: cout << "ERROR" << fltk_filechooser.errmsg() << endl; break;  // ERROR
		case  1: cout << "CANCEL" << endl;  break;  // CANCEL
		default: 
			filepath = string(fltk_filechooser.filename()); 
			result = true;
			break;  // FILE CHOSEN
	}


	return result;
}
// UtilFLTK::getFilePath() ////////////////////////////////////////////////////



void UtilFLTK::showMessageBox(const string& msg, const string& title)
///////////////////////////////////////////////////////////////////////////////
{
	fl_message_title(title.c_str());
	fl_message(msg.c_str());
}
// end: UtilFLTK::showMessageBox() ////////////////////////////////////////////