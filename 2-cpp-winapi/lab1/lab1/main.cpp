#undef UNICODE

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "Lab 1";

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
  MSG msg;
  /*���� �������� hPrevInstance � Win32 ������ ����� NULL���������� ��������� ��� �������� */
  if (!hPrevInstance) 
  {  /* �������������� ���������� -  �������������� ������ ������ ���� � ������������ ��� */
    if (!InitApplication(hInstance)) 
      return (FALSE);
  }
   /* ��������� �������� ����� ���������� -     ������� ������� ���� ���������� */
  if (!InitInstance(hInstance, nCmdShow)) 
    return (FALSE);  
  
  /* ���� ��������� ��������� */
  while (GetMessage(&msg, NULL, 0, 0)) 
  {   	TranslateMessage(&msg);
    		DispatchMessage(&msg);
  }
  return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
  // ��������� ��������� ������ ���� WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_CROSS);
  wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE-1);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;
  // ������������ ����� ����
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  hWnd = CreateWindow(
    szClassName,         // ��������� �� ������ ������������������� ����� ������
    szTitle,             // ��������� �� ������ ��������� ����
    WS_OVERLAPPEDWINDOW, // ����� ����
    CW_USEDEFAULT,       // �������������� ���������� ����
    CW_USEDEFAULT,       // ������������ ���������� ����
    CW_USEDEFAULT,       // ������ ����
    CW_USEDEFAULT,       // ������ ����
    NULL,                // ���������� ������������� ����
    NULL,                // ���������� ���� ����
    hInstance,           // ���������� ���������� ����������
    NULL);               // ��������� �� �������������� ������ ����

  if (!hWnd)    return (FALSE); 
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{  HDC hDC;
  PAINTSTRUCT ps;
  static int x,y;
  switch(message)
  {
	  RECT r;
  case WM_SIZE:
	  x=LOWORD(lParam);
	  y=HIWORD(lParam);
	  break;
    case WM_PAINT:
      hDC = BeginPaint(hwnd, &ps);
	  Rectangle(hDC,10,10,x-10,y-10);
	  Ellipse(hDC,0,0,x,y);  
	  r.bottom=y; r.left=0; r.right=x; r.top=0;
	  DrawText(hDC,"TEXT 1",-1,&r,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	  SetBkMode(hDC,TRANSPARENT);
      DrawText(hDC,"TEXT 2",-1,&r,DT_SINGLELINE | DT_LEFT | DT_TOP);
	  DrawText(hDC,"TEXT 3",-1,&r,DT_SINGLELINE | DT_RIGHT | DT_TOP);
	  DrawText(hDC,"TEXT 4",-1,&r,DT_SINGLELINE | DT_LEFT | DT_BOTTOM);
	  DrawText(hDC,"TEXT 5",-1,&r,DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);
	  EndPaint(hwnd, &ps);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
  return 0;
}
