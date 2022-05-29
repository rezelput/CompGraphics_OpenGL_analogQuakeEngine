#define WIN32_MEAN_AND_LEAN
#define WIN32_EXTRA_LEAN



#include <windows.h>

#include "oglwindow.h"		// OpenGL
#include "vector.h"
#include "engine.h"			// engine
#include "simpengine.h"


int WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	int loopRet;
	bool fscreen;
	CSimpEngine *engine = NULL;

	try
	{	
		fscreen = (MessageBox(NULL, "Fullscreen?", "Fullscreen?", MB_YESNO) == IDYES);
	
		engine = new CSimpEngine("test_engine", fscreen,  800, 600, 32);

		loopRet = engine->EnterMessageLoop();

		delete engine;

		return loopRet;
	}
	catch(char *sz)
	{	
		MessageBox(NULL, sz, 0, 0);
		delete engine;
	}

	return -1;
}