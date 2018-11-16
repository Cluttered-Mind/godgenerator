#include <windows.h>
#include "GodGenerator.cpp"

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

// Generate and Print
void generate(HDC hDC) {
	// Declare Variables
	std::string godName;
	std::string godRole;
	std::string itemsRelics[2];
	std::string itemsStarter;
	std::string itemsBuild[6];
	
	// Generate Data
	randomGod(godName, godRole);
	randomRelics(itemsRelics);
	randomStarter(itemsStarter);
	randomItems(itemsBuild, godRole);
	
	// Output Variables
	TextOut(hDC, 10, 10, godName.c_str(), godName.length());
	TextOut(hDC, 10, 30, godRole.c_str(), godRole.length());
	TextOut(hDC, 10, 50, itemsRelics[0].c_str(), itemsRelics[0].length());
	TextOut(hDC, 10, 70, itemsRelics[1].c_str(), itemsRelics[1].length());
	TextOut(hDC, 10, 90, itemsStarter.c_str(), itemsStarter.length());
	TextOut(hDC, 10, 110, itemsBuild[0].c_str(), itemsBuild[0].length());
	TextOut(hDC, 10, 130, itemsBuild[1].c_str(), itemsBuild[1].length());
	TextOut(hDC, 10, 150, itemsBuild[2].c_str(), itemsBuild[2].length());
	TextOut(hDC, 10, 170, itemsBuild[3].c_str(), itemsBuild[3].length());
	TextOut(hDC, 10, 190, itemsBuild[4].c_str(), itemsBuild[4].length());
	TextOut(hDC, 10, 210, itemsBuild[5].c_str(), itemsBuild[5].length());
	
	return;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","God Generator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	
	// Declare Canvas
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint (hwnd, &ps);
	
	// Generate Initial Build
	generate(hDC);
	
	// Close Canvas
	EndPaint (hwnd, &ps);
	
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */	
	}
	
	return msg.wParam;
}
