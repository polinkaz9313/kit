// KiTPO_laba1.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "KiTPO_laba1.h"

#define MAX_LOADSTRING		100
#define BUF_SIZE			65536			// Максимальный размер буфера
//#define UINT_MAX			4294967296		// Максимальный квадрат числа
#define SQRT_UINT_MAX		65536			// Максимальное число 
#define LEN_UINT_MAX		11				// Максимальная длина числа

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HWND hWndTextBox;
HWND hWndTextBox2;
WNDPROC WndProcEditBox;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT APIENTRY	NewWndProcEditBox(HWND, UINT, WPARAM, LPARAM);
int					Start();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KITPO_LABA1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KITPO_LABA1));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KITPO_LABA1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_KITPO_LABA1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      10, 10, 440, 250, NULL, NULL, hInstance, NULL);

   hWndTextBox = CreateWindow(_T("EDIT"), 0, 
	   WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE,
	   10, 10, 400, 100, hWnd, (HMENU)ID_TEXTBOX, NULL, NULL);

/*   hWndTextBox2 = CreateWindow(_T("EDIT"), 0,
	   WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL,
	   410, 10, 400, 500, hWnd, (HMENU)ID_TEXTBOX2, NULL, NULL);
*/
   CreateWindow(_T("BUTTON"), _T("Старт"), WS_BORDER | WS_VISIBLE | WS_CHILD,
	   165, 120, 80, 30, hWnd, (HMENU)ID_BUTTON, NULL, NULL);

   WndProcEditBox = (WNDPROC)SetWindowLong(hWndTextBox, GWL_WNDPROC, (LONG)NewWndProcEditBox);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON:
			switch (Start())
			{
			case 1:
				MessageBox(hWnd, _T("Максимальное число = 65535"), _T("Ошибка 1"), MB_OK);
				break;
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
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

LRESULT APIENTRY	NewWndProcEditBox(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
/*	TCHAR buf[65536];
	TCHAR buf_mess[256];

	buf[Edit_GetText(hWndTextBox2, buf, 65536)] = 0;
	_itot_s(message, buf_mess, 16);
	_tcscat_s(buf, buf_mess);
	_tcscat_s(buf, _T(" ||| "));
	_itot_s(wParam, buf_mess, 16);
	_tcscat_s(buf, buf_mess);
	_tcscat_s(buf, _T(" ||| "));
	_itot_s(lParam, buf_mess, 16);
	_tcscat_s(buf, buf_mess);
	_tcscat_s(buf, _T("\r\n"));
	Edit_SetText(hWndTextBox2, buf);*/

	switch (message)
	{
	case WM_CHAR:
		if (wParam >= '0' && wParam <= '9' || wParam == 8 || wParam == ' ')
			return CallWindowProc(WndProcEditBox, hWnd, message, wParam, lParam);
		else
			return 0;
	default:
		return CallWindowProc(WndProcEditBox, hWnd, message, wParam, lParam);
	}	
}

int Start()
{
	TCHAR buf[BUF_SIZE];
	TCHAR bufWord[LEN_UINT_MAX];
	int len;
	UINT x[BUF_SIZE/2];
	bool *local_min;
	int xCnt = 0;
	int i, j;

	buf[len = Edit_GetText(hWndTextBox, buf, 65536)] = 0;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (buf[i] == ' ' && i < len) i++;
		while (buf[i] == '0' && i < len)
		{
			i++;
			bufWord[0] = '0';
			bufWord[1] = 0;
			j = 1;
		}
		while (buf[i] >= '0' && buf[i] <= '9' && i < len)
		{
			if (j == LEN_UINT_MAX - 1)	return 1;
			bufWord[j] = buf[i];
			bufWord[j + 1] = 0;
			i++;
			j++;
		}
		if (j)
		{
			x[xCnt] = _ttol(bufWord);
			if (x[xCnt] >= SQRT_UINT_MAX) return 1;
			xCnt++;
		}
	}

	if (xCnt == 0) return 0;

	local_min = new bool[xCnt];

	if (xCnt > 1)	// Проверка первого и последнего
	{
		if (x[0] < x[1]) local_min[0] = 1;
		else local_min[0] = 0;
		if (x[xCnt - 1] < x[xCnt - 2]) local_min[xCnt - 1] = 1;
		else local_min[xCnt - 1] = 0;
	}

	for (i = 1; i < xCnt - 1; i++)
	{
		if (x[i] < x[i - 1] && x[i] < x[i + 1]) local_min[i] = 1;
		else local_min[i] = 0;
	}

	buf[0] = 0;
	for (i = 0; i < xCnt; i++)
	{
		if (local_min[i]) x[i] = x[i] * x[i];
		_ltot_s(x[i], bufWord, 10);
		_tcscat_s(buf, bufWord);
		_tcscat_s(buf, _T(" "));
	}

	Edit_SetText(hWndTextBox, buf);

	delete[]local_min;

	return 0;
}