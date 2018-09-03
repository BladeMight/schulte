#include <Windows.h> 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// #include <algorithm>

const int rect_size = 96;
const int font_h    = 58;
int tablex          = 5;
int max             = tablex*tablex;
int p        	     = 2;
int rawhw		    = tablex*rect_size;
int hw              = rawhw + p*tablex;
wchar_t name[]      = L"Таблица Шульте (BladeMight)";

BOOL Have(int* ints, int needle, int len) {
	for (int i = 0; i!= len; i++) {
		if (ints[i] == needle) {
			return TRUE;
		}
	}
	return FALSE;
}
int getRandom(int* known, int i) {
	int que = 0;
	BOOL have = TRUE;
	do {
		srand(time(NULL)* rand());
		que = rand() % max+1;
		have = Have(known, que, i);
		if (i == 0)
			have = FALSE;
	} while (have);
	return que;
}

void drawrects(HDC screen, HWND hwnd) {
	HFONT hFont = (HFONT)CreateFont(font_h, 0, 0, 0, 0, 0, 0, 0,
		ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY,
		VARIABLE_PITCH, L"Segoe UI");
	SelectObject(screen, hFont);
	int x = 0;
	int y = 0;
	int known[tablex*tablex+5];
	int leg = 0;
	// int nums[36] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	// random_shuffle(&nums[0],&nums[36]);
	// for (int i = 0; i!= 36; i++) {
		// Rectangle(screen, x, y, x+rect_size, y+rect_size);
		// char buf[25];
		// sprintf(buf, "%i", nums[i]);
		// int left = 0;
		// if (nums[i] >= 10)
			// left = 12;
		// TextOut(screen, x+((rect_size)/2)-10-left,
						// y+(font_h/2)-8, buf, strlen(buf));
		// x += rect_size+1;
		// if (x >= hw) {
			// x = 0;
			// y += rect_size+1;
		// }
		
	// }
	int tablx = 0;
	for (int i = 1; i!=max+1; i++) {
		tablx++;
		Rectangle(screen, x, y, x+rect_size, y+rect_size);
		int que = getRandom(known, leg);
		wchar_t buf[25];
		wsprintf(buf, L"%i",que);
		known[leg] = que;
		// int right = 0;
		// if (que >= 1 && que < 10)
			// right = 12;
		int left = 0;
		if (que >= 10)
			left = 12;
		TextOut(screen, x+((rect_size)/2)-10-left,
						y+(font_h/2)-8, buf, wcslen(buf));
		x += rect_size+p;
		if (tablx >= tablex) {
			tablx = 0;
			x = 0;
			y += rect_size+p;
		}
		leg++;
		// printf("All known:\n");
		// for (int g = 0; g!= leg; g++) {
			// printf("{%i} ", known[g]);
		// }
		// printf("\nleg: %i\n", leg);
	}
}
LRESULT CALLBACK wndProc(HWND wnd, UINT msg, WPARAM w, LPARAM l) {
	switch(msg) {
		case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC screen = BeginPaint(wnd, &ps);   // Get the screen DC
				drawrects(screen, wnd);
				EndPaint(wnd, &ps);                  // clean up
			} break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
    }
    return DefWindowProc(wnd,msg,w,l);
}

HWND createWindow(HINSTANCE inst) {
    WNDCLASSEX wc = {0};
    wc.cbSize =         sizeof(WNDCLASSEX); 
	wc.hCursor =        LoadCursor(NULL, IDC_ARROW);
    wc.hInstance =      inst;
    wc.lpfnWndProc =    wndProc;
	wc.lpszClassName =  name;
    RegisterClassEx(&wc);
    int style = WS_CAPTION | WS_SYSMENU;
	RECT rc = {0, 0, hw, hw};
	AdjustWindowRect(&rc, style, FALSE);
    return CreateWindow(name, name, style | WS_VISIBLE, 0, 0,
		rc.right - rc.left, rc.bottom - rc.top,	NULL, NULL, inst, NULL);
}

bool isint(wchar_t* str) {
    while (*str)
		if (!iswdigit(*str++))
			return false;
    return true;
}
long int ConvertToInt(wchar_t* integer) {
	long int x;
    swscanf(integer, L"%d", &x);
	return x;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show) {
	LPWSTR* argv;
    int argc;
    argv = CommandLineToArgvW(GetCommandLine(), &argc);
	if (argv != NULL) {
		if (argc >= 2)
			if (isint(argv[1]))
				tablex = ConvertToInt(argv[1]);
		if (argc >= 3) {
			if (isint(argv[2]))
				p = ConvertToInt(argv[2]);
			if (wcscmp(argv[2], L"-1") == 0)
				p = -1;
		}
		max             = tablex*tablex;
		rawhw		    = tablex*rect_size;
		hw              = rawhw + p*tablex;
		if (p < 0) 
			hw += 2;
	}
	LocalFree(argv);
    HWND wnd = createWindow(inst);
    MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	return 0;
}