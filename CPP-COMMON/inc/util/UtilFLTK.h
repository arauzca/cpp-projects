/*/////////////////////////////////////////////////////////////////////////////
module:  implementation of FLTK utility class
purpose: implements general utilities for FLTK/GLUT/OS support

written: U.Kuenzler
history: 1.00 - initial version of FLTK system nativ common dialog boxes
/////////////////////////////////////////////////////////////////////////////*/



// system includes ////////////////////////////////////////////////////////////
#include <string>



class UtilFLTK
///////////////////////////////////////////////////////////////////////////////
{
public:
	static bool getFilePath(std::string& filepath,
		const std::string& filter = "All Files (*.*)\n*.*\n\0",
		const std::string& startdir = "" , bool open = true);

	static void showMessageBox(
		const std::string& msg,
		const std::string& title = "Error Message");
};
// class UtilFLTK ////////////////////////////////////////////////////////////
